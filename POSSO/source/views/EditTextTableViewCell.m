/*
 Copyright (c) 2009, Rohan Pinto. All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 Neither the name of the author nor the names of its contributors may be used
 to endorse or promote products derived from this software without specific
 prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 EditTextTableViewCell.m
 POssO is a portable administration console for OpenSSO.
 
 POssO adds the much desired remote management feature to your corporate identity 
 management infrastructure, enabling you to achieve better efficiency and 
 accessibility in your organization. 
 Learn more about POssO on the http://posso.mobi site.
 */


#import "EditTextTableViewCell.h"
#import "EditUserViewController.h"
#import "PossoAppDelegate.h"
#import "LogsViewController.h"

// https://developer.apple.com/webapps/docs/documentation/AppleApplications/Reference/SafariWebContent/DesigningForms/DesigningForms.html
const int kPortraitKeyboardOffset = 216 - 49; 

@implementation EditTextTableViewCell

@synthesize label;
@synthesize editable;
@synthesize previousText;

#pragma mark -
#pragma mark Life cycle

- (id)initWithFrame:(CGRect)frame reuseIdentifier:(NSString *)reuseIdentifier
{
    if ( (self = [super initWithFrame:frame reuseIdentifier:reuseIdentifier]) )
    {
       //self.selectionStyle = UITableViewCellSelectionStyleNone;

       self.label = [[[UITextField alloc] initWithFrame:CGRectMake(5, 7, 290, 28)] autorelease];
       self.label.font = [UIFont boldSystemFontOfSize:20];
       self.label.backgroundColor = [UIColor clearColor];
       self.label.textColor = [UIColor cyanColor];
       self.label.adjustsFontSizeToFitWidth = YES; 
       self.label.minimumFontSize = 8;
       self.label.clearButtonMode = UITextFieldViewModeWhileEditing;
       self.label.keyboardType = UIKeyboardTypeASCIICapable;
       self.label.returnKeyType = UIReturnKeyDone;
       self.label.delegate = self;

       [self.contentView addSubview:self.label];
   }
   return self;
}

- (void)dealloc
{
	self.label = nil;
	self.previousText = nil;
   [super dealloc];
}
   
#pragma mark -
#pragma mark Editability management
   
- (void)setEditable:(BOOL)isEditable
{
   editable = isEditable;
   if (isEditable)
   {
   // editable color borrowed from nottoobadsoftware's mySettings project
      self.label.textColor = [UIColor colorWithRed:0.192157 green:0.309804 blue:0.521569 alpha:1.0];
   }
   else
   {
      self.label.textColor = [UIColor blackColor];
   }
}
   
#pragma mark -
#pragma mark Text field support

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField
{
   (void)textField;
   return self.editable;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
   [textField resignFirstResponder];
   return YES;
}

- (void)textFieldDidBeginEditing:(UITextField *)textField
{
   self.previousText = textField.text;

   // we'll always scroll to editing cell at top of keyboard
   // by moving cell to table bottom and table to top of keyboard
   UITableView *owner = (UITableView *)self.superview;
   CGRect smallFrame = owner.frame;
   smallFrame.size.height -= kPortraitKeyboardOffset;
   [UIView beginAnimations:nil context:NULL];
   [UIView setAnimationDuration:0.3];
   [owner setFrame:smallFrame];
   [UIView commitAnimations];

   NSIndexPath *ourPath = [owner indexPathForCell:self];
	[owner scrollToRowAtIndexPath:ourPath atScrollPosition:UITableViewScrollPositionBottom animated:NO];
}

- (void)textFieldDidEndEditing:(UITextField *)textField
{
   // reset table size, which will scroll or not as needed
   UITableView *owner = (UITableView *)self.superview;
   CGRect normalFrame = owner.frame;
   normalFrame.size.height += kPortraitKeyboardOffset;
   [UIView beginAnimations:nil context:NULL];
   [UIView setAnimationDuration:0.3];
   [owner setFrame:normalFrame];
   [UIView commitAnimations];

   if ([textField.text isEqual:self.previousText])
      return;

   // we'll treat empty as cancel for now
   if (!textField.text.length)
   {
      textField.text = self.previousText;
      return;
   }
   
   // sort out what was changed
   
   EditUserViewController *ourController = (EditUserViewController *)owner.delegate;
   twcheck([ourController isKindOfClass:[EditUserViewController class]]);
   NSIndexPath *ourPath = [owner indexPathForCell:self];
   NSString *userID = ourController.navigationItem.title;
   NSDictionary *sectionInfo = [ourController.lastRetrievedInfo objectAtIndex:ourPath.section];
   NSString *sectionTitle = [sectionInfo objectForKey:kEditUserSectionName];
   NSString *newValue = textField.text;

   // account for comma separated fields displayed on separate rows
   NSArray *sectionValues = [sectionInfo objectForKey:kEditUserSectionValue];
   if (1 < sectionValues.count)
   {
      NSString *oldValue = [sectionValues componentsJoinedByString:@","];
      // note assumption that the old value of this field will be a unique string
      // should that be false, ourPath.row tells us the exact array index to substitute
      newValue = [oldValue stringByReplacingOccurrencesOfString:self.previousText withString:textField.text];
   }
   
   twlog("for user %@", userID);
   twlog("in section %@", sectionTitle);
   twlog("edit to new value %@!", newValue);
     
   // save edits to server

   BOOL validConfiguration = YES;
   NSString *serverBase = [PossoAppDelegate appDelegate].baseURL;
   validConfiguration &= 0 < serverBase.length;
   NSString *userToken = [PossoAppDelegate appDelegate].token;
   validConfiguration &= 0 < userToken.length;
   twcheck(validConfiguration);
   
   NSString *editURLString = [NSString
      stringWithFormat:@"%@/update?identity_name=%@&identity_attribute_names=%@&identity_attribute_values_%@=%@&admin=%@",
      serverBase,
      userID,
      sectionTitle, 
      sectionTitle,
      [newValue stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding],
      userToken
   ];
   twlog("editing: %@", editURLString);

   [LogsViewController logWithFormat:@"edited user %@ field %@ to %@", userID, sectionTitle, newValue];

	NSError* editError = nil;
	NSString *editResult = [NSString
      stringWithContentsOfURL:[NSURL URLWithString:editURLString]
      encoding:NSNonLossyASCIIStringEncoding
      error:&editError
   ];
   twlogif(nil != editError, "editing FAIL: %@", editError);
  
   twlog("edit result: %@", editResult);

   // make owner reload so we can see if edit took...
   
   [ourController retrieveInfo];
}

@end

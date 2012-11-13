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
 EditRangeTableViewCell.h
 POssO is a portable administration console for OpenSSO.
 
 POssO adds the much desired remote management feature to your corporate identity 
 management infrastructure, enabling you to achieve better efficiency and 
 accessibility in your organization. 
 Learn more about POssO on the http://posso.mobi site.
 */



#import <UIKit/UIKit.h>

extern NSString* kRangeItemText;
extern NSString* kDefaultItemMinimum;
extern NSString* kDefaultItemMaximum;
extern NSString* kSettingsItemMinimum;
extern NSString* kSettingsItemMaximum;

@interface EditRangeTableViewCell : UITableViewCell <UITextFieldDelegate, UIActionSheetDelegate, UIPickerViewDataSource, UIPickerViewDelegate>
{
	UILabel *label;

   UITextField *minimumValue;
	UILabel *toLabel;
	UITextField *maximumValue;
   
   UISwitch *valueSwitch;

   NSDictionary *itemInfo;
   
   BOOL editingMinimum;
   NSInteger editScrollOffset;
}

@property (nonatomic, retain) UILabel *label;
@property (nonatomic, retain) UITextField *minimumValue;
@property (nonatomic, retain) UILabel *toLabel;
@property (nonatomic, retain) UITextField *maximumValue;
@property (nonatomic, retain) UISwitch *valueSwitch;
@property (nonatomic, retain) NSDictionary *itemInfo;

// Life cycle

- (id)initWithFrame:(CGRect)frame reuseIdentifier:(NSString *)reuseIdentifier;
- (void)dealloc;

// Editability management

- (void)setItemInfo:(NSDictionary *)newInfo;

- (IBAction)switchChanged:(id)sender;

// Picking support

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField;

- (void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex;

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView;
- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component;

- (NSString *)pickerView:(UIPickerView *)pickerView titleForRow:(NSInteger)row forComponent:(NSInteger)component;
- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component;

@end

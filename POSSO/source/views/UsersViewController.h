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
 UsersViewController.h
 POssO is a portable administration console for OpenSSO.
 
 POssO adds the much desired remote management feature to your corporate identity 
 management infrastructure, enabling you to achieve better efficiency and 
 accessibility in your organization. 
 Learn more about POssO on the http://posso.mobi site.
 */


#import <UIKit/UIKit.h>

@interface UsersViewController : UIViewController <UITableViewDataSource, UITableViewDelegate>
{
   IBOutlet UILabel *enterLoginLabel;
   IBOutlet UIActivityIndicatorView *loadingIndicator;
   IBOutlet UILabel *errorLabel;
   IBOutlet UITableView *usersTable;
   
   NSString *lastRetrievedToken;
   NSMutableArray *lastRetrievedUsers;
 
}

@property (nonatomic, retain) IBOutlet UILabel *enterLoginLabel;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *loadingIndicator;
@property (nonatomic, retain) IBOutlet UILabel *errorLabel;
@property (nonatomic, retain) IBOutlet UITableView *usersTable;
@property (nonatomic, copy) NSString *lastRetrievedToken;
@property (nonatomic, retain) NSMutableArray *lastRetrievedUsers;

// Life cycle

- (void)viewDidLoad;
- (void)viewWillAppear:(BOOL)animated;
- (void)didReceiveMemoryWarning;
#if __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
- (void)viewDidUnload;
- (void)setView:(UIView*)toView;
#endif __IPHONE_OS_VERSION_MIN_REQUIRED >= 30000
- (void)clearOutlets;
- (void)dealloc;

// Users management

- (void)fixDisplay;
- (void)loadUsersFromServer;
- (BOOL)parseUsers:(NSString *)users;

// Table support

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView;
- (NSInteger)tableView:(UITableView *)table numberOfRowsInSection:(NSInteger)section;
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath;
- (void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath;

@end

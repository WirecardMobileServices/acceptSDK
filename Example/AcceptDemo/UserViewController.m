//
//  UserViewController.m
//  Accept Demo
//
//  Created by Fortes, Francisco on 10/27/14.
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import "UserViewController.h"
#import "Utils.h"

@interface UserViewController ()
{
    NSString *backendURL, *clientID, *clientSecret;
}
@property (nonatomic, weak) IBOutlet UITextField *emailTf;
@property (nonatomic, weak) IBOutlet UITextField *passwordTf;
@property (nonatomic, weak) IBOutlet UITextField *forgotTf;
@property (nonatomic, weak) IBOutlet UIButton *loginBtn;
@property (nonatomic, weak) IBOutlet UILabel *tokenLb;
@property (nonatomic, weak) IBOutlet UISegmentedControl *segmentC;
@property (nonatomic, weak) Accept *accept;
@property (nonatomic,strong) __block NSError *error;
@property (nonatomic,strong)  NSValue *errorObject;
@property (nonatomic,strong) AcceptUserResponse *userResponse;
typedef enum {
                EnumLogin = 0, EnumForgotUserID, EnumForgotPW, EnumChangePW
             } EnumUserActions;
@end

@implementation UserViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.passwordTf.delegate = self;
    self.forgotTf.delegate = self;
    self.accept = [[Utils sharedInstance] accept];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(tokenDidExpire)
                                                 name:kTokenTimerNotificationName
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(applicationEnteredForeground:)
                                                 name:UIApplicationWillEnterForegroundNotification
                                               object:nil];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

-(void)viewWillAppear:(BOOL)animated
{
    [self setDefaultValues];
}


#pragma mark - Setup and Others Methods

-(void)setDefaultValues
{
    NSLog(@">>> UserViewController - setDefaultValues");
    self.emailTf.text = [[NSUserDefaults standardUserDefaults] valueForKey:@"username"];
    self.passwordTf.text = [[NSUserDefaults standardUserDefaults] valueForKey:@"password"];
    [self.forgotTf setEnabled:NO];
    [self.tokenLb setTextColor:([[Utils sharedInstance] tokenIsValid])? [UIColor greenColor] : [UIColor redColor]];
    [self.tokenLb setText:([[Utils sharedInstance] tokenIsValid])? @"Valid token" : @"Token expired or empty, please login"];
}

- (void)applicationEnteredForeground:(NSNotification *)notification
{
    NSLog(@">>> UserViewController - Application Entered Foreground");
    [self.tokenLb setTextColor:([[Utils sharedInstance] tokenIsValid])? [UIColor greenColor] : [UIColor redColor]];
    [self.tokenLb setText:([[Utils sharedInstance] tokenIsValid])? @"Valid token" : @"Token expired or empty, please login"];
}

-(void)tokenDidExpire
{
    NSLog(@">>> UserViewController - tokenDidExpire");
    [self.tokenLb setTextColor:[UIColor redColor]];
    [self.tokenLb setText:@"Token expired"];
}

-(IBAction)segmentChanged:(id)sender
{
    NSLog(@">>> UserViewController - segmentChanged");
    switch (self.segmentC.selectedSegmentIndex)
    {
        case EnumLogin:
            [self.emailTf setSecureTextEntry:NO];
            [self setDefaultValues];
            self.emailTf.placeholder = @"username/email";
            self.passwordTf.placeholder = @"password";
            [self.passwordTf setEnabled:YES];
            [self.forgotTf setEnabled:NO];
            self.forgotTf.text = @"";
            self.forgotTf.placeholder = @"";
            break;
        case EnumForgotUserID:
            [self.emailTf setSecureTextEntry:NO];
            self.emailTf.text = @"";
            self.passwordTf.text = @"";
            self.emailTf.placeholder = @"Email address for recovery";
            self.passwordTf.placeholder = @"";
            [self.passwordTf setEnabled:NO];
            [self.forgotTf setEnabled:NO];
            self.forgotTf.text = @"";
            self.forgotTf.placeholder = @"";
            break;
        case EnumForgotPW:
            [self.emailTf setSecureTextEntry:NO];
            self.emailTf.text = @"";
            self.passwordTf.text = @"";
            self.emailTf.placeholder = @"Enter External ID";
            [self.passwordTf setEnabled:NO];
            [self.forgotTf setEnabled:NO];
            self.passwordTf.placeholder = @"";
            self.forgotTf.text = @"";
            self.forgotTf.placeholder = @"";
            break;
        case EnumChangePW:
        default:
            [self.emailTf setSecureTextEntry:YES];
            self.emailTf.text = @"";
            self.passwordTf.text = @"";
            self.emailTf.placeholder = @"Current password";
            self.passwordTf.placeholder = @"Reenter new password";
            self.forgotTf.text = @"";
            self.forgotTf.placeholder = @"New password";
            [self.passwordTf setEnabled:YES];
            [self.forgotTf setEnabled:YES];
            break;
    }
}


#pragma mark - Login Methods

-(void)loginSuccess
{
    NSLog(@">>> UserViewController - loginSuccess");
    [Utils showAlertWithTitle:@"Success" andMessage:@"Login successful"];
    self.tokenLb.text = @"Valid token";
    self.tokenLb.textColor = [UIColor greenColor];
    [[Utils sharedInstance] setTokenIsValid:YES];
    [[Utils sharedInstance] startTokenTimer];
    
    [self.loginBtn setTitle:@"Enter" forState:UIControlStateNormal];
}

-(void)loginFailure:(NSError *)error
{
    NSLog(@">>> UserViewController - loginFailure");
   [Utils showAlertWithTitle:@"Error" andMessage:[NSString stringWithFormat:@"Login did fail with error %@", (error.code == 0)? @"0 - Invalid password or user" : @"Check your connection or backend status"]];
    self.tokenLb.text = @"No token";
    self.tokenLb.textColor = [UIColor grayColor];
    [self.loginBtn setTitle:@"Enter" forState:UIControlStateNormal];
}

-(void)doLogin
{
    NSLog(@">>> UserViewController - doLogin");
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
    __weak UserViewController *weakSelf = self;
    void (^completionBlock)(NSString*, NSError*) = ^(NSString *accessToken, NSError *error)
    {
        [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
        if (accessToken) {
            [weakSelf loginSuccess];
        }
        else{
            [weakSelf loginFailure:error];
        }
    };
    [[NSUserDefaults standardUserDefaults] setObject:self.emailTf.text forKey:@"username"];
    [[NSUserDefaults standardUserDefaults] setObject:self.passwordTf.text forKey:@"password"];
    [self loginWithUsername:self.emailTf.text andPassword:self.passwordTf.text completionBlock:completionBlock];
}

-(void)loginWithUsername:(NSString *)username andPassword:(NSString *)password completionBlock:(void (^)(NSString*, NSError*))completionBlock
{
    NSLog(@">>> UserViewController - loginWithUsername");
    [Utils checkConnectivity];
    [self.accept requestAccessToken:username password:password config:[[Utils sharedInstance] backendConfig] completion:^(AcceptAccessToken *accessToken, NSError *error){
        [[Utils sharedInstance] setAccessToken:(accessToken.accessToken)? : @""];
        self.error = error;
        self.errorObject = nil;
        
        [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
        
        if (error)
        {
            AcceptRequestTokenErrorCode errCode = ((AcceptRequestTokenErrorCode)self.error.code);
            self.errorObject = [NSValue value:&errCode withObjCType:@encode(AcceptRequestTokenErrorCode)];
            completionBlock(accessToken.accessToken, error);
        }
        else
        {
            void(^completionConfig)(AcceptTerminalConfigFiles*, NSError*)   =  ^(AcceptTerminalConfigFiles* configFiles, NSError* error)
            {
                if (configFiles && !error)
                {
                    NSMutableDictionary *terminalVersionDict = [[NSMutableDictionary alloc] init];
                    [terminalVersionDict setObject:[configFiles getVersion] forKey:AcceptSpireVendorUUID]; //Spire PosMate for now only
                    [[Utils sharedInstance] setVendorConfigurationVersion:terminalVersionDict];
                }
            };
            
            [self.accept  queryConfigFile:[[Utils sharedInstance] accessToken]  config:[[Utils sharedInstance] backendConfig] andCurrentVersion:@"0" completion:completionConfig];
            
            [self.accept  requestMerchantInfo:[[Utils sharedInstance] accessToken]  config:[[Utils sharedInstance] backendConfig] completion:^(AcceptUserResponse *response, NSError *error)
            {
                //Response contains merchant data such as taxRates, currencies, locale, amount limits, etc
                self.userResponse = response;
                [[Utils sharedInstance] setCurrenciesForMerchant:response.merchant.currencies];
                [[Utils sharedInstance] setTaxAmountsForMerchant:response.merchant.taxRates];
                [[Utils sharedInstance] setCountryCurrencyDefaultValue:response.merchant.locale];
                
                if (response.merchant.currencies.count == 0)
                {
                    [[Utils sharedInstance] setCurrencyCodeDefaultValue:response.merchant.currency];
                }
                else
                {
                    NSString *defCurrency = [[Utils sharedInstance] getCurrencyCodeDefaultValue];

                    if (!defCurrency)
                    {
                        [[Utils sharedInstance] setCurrencyCodeDefaultValue:[response.merchant.currencies firstObject]];
                    }
                    else
                    {
                        NSPredicate *currencyPredicate = [NSPredicate predicateWithFormat:@"self == %@",defCurrency];
                        
                        if ([[response.merchant.currencies filteredArrayUsingPredicate:currencyPredicate] count] == 0)
                        {
                            [[Utils sharedInstance] setCurrencyCodeDefaultValue:[response.merchant.currencies firstObject]];
                        }
                    }
                }
                
                [[Utils sharedInstance] setLocaleDefaultValue:response.merchant.locale];
                
                /* Example:
                 AcceptUserResponseWhiteLabelApp *whitelabelApp = response.merchantResponse.whiteLabelApp;
                 NSInteger amountLowerLimit  = whitelabelApp.amountLowerLimit;
                 NSInteger amountUpperLimit  = whitelabelApp.amountUpperLimit;
                 NSInteger amountDailyLimit  = whitelabelApp.amountDailyLimit;
                 NSString *serviceChargeAmount = whitelabelApp.serviceChargeAmount;*/
                
                completionBlock(accessToken.accessToken, error);
                
            }];
        }
    }];
}

#pragma mark - Forgot Methods

-(void)remindSuccess
{
    NSLog(@">>> UserViewController - remindSuccess");
    [Utils showAlertWithTitle:@"Success" andMessage:@"External Id reminder sent to your email"];    
}

-(void)remindFailure:(NSError *)error
{
    NSLog(@">>> UserViewController - remindFailure");
    [Utils showAlertWithTitle:@"Login Error" andMessage:@"Could not send External Id"];
}


-(void)doForgotUserID
{
    NSLog(@">>> UserViewController - doForgotUserID");
    if (!self.emailTf.text || [self.emailTf.text isEqualToString:@""])
    {
        [Utils showAlertWithTitle:@"Login Error" andMessage:@"Email Address is required!"];
        return;
    }
    
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
    __weak UserViewController *weakSelf = self;
    
    void (^completion)(BOOL, NSError*) = ^(BOOL success, NSError *error)
    {
       [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
        if (success)
        {
            [weakSelf remindSuccess];
        }
        else{
            [weakSelf remindFailure:error];
        }
    };
    
    [self.accept forgotUserId:self.emailTf.text config:[[Utils sharedInstance] backendConfig] completion:completion];
}

-(void)doForgotPW
{
    NSLog(@">>> UserViewController - doForgotPW");
    if (!self.emailTf.text || [self.emailTf.text isEqualToString:@""])
    {
        [Utils showAlertWithTitle:@"Login Error" andMessage:@"External ID is required!"];
        return;
    }
    
    [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
    __weak UserViewController *weakSelf = self;
    
    void (^completion)(BOOL, NSError*) = ^(BOOL success, NSError *error)
    {
        [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
        if (success)
        {
            [weakSelf resetSuccess];
        }
        else{
            [weakSelf resetFailure:error];
        }
    };
    
    [self.accept resetPassword:self.emailTf.text config:[[Utils sharedInstance] backendConfig] completion:completion];
}

#pragma mark - Change Methods

-(void)resetSuccess
{
    NSLog(@">>> UserViewController - resetSuccess");
   [Utils showAlertWithTitle:@"Success" andMessage:@"Password Reset instructions sent to your email"];
}

-(void)resetFailure:(NSError *)error
{
    NSLog(@">>> UserViewController - resetFailure");
    [Utils showAlertWithTitle:@"Error" andMessage:@"Password could not be reset"];
}

-(void)doChangePW
{
    NSLog(@">>> UserViewController - doChangePW");
    [self.view endEditing:YES];
    
    if(![Utils checkConnectivity]) return;
    
    if (self.emailTf.text.length == 0 ||
        self.passwordTf.text.length == 0 ||
        self.forgotTf.text.length == 0)
    {
        //Some of the fields is empty
        [Utils showAlertWithTitle:@"Login Error" andMessage:@"No field can be left empty"];
    }
    else if (![self.passwordTf.text isEqualToString:self.forgotTf.text])
    {
        //Passwords do not match
        [Utils showAlertWithTitle:@"Login Error" andMessage:@"Password confirmation does not match"];
    }
    else //strings seems fine, try to change the password
    {
        [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:YES];
        
        __weak UserViewController *weakSelf = self;
        
        void (^completionBlock)(NSString*, NSError*) = ^(NSString *accessToken, NSError *error)
        {
            if (accessToken) {
                [weakSelf loginChangePassSuccess:error];
            }
            else{
                [weakSelf loginChangePassFailure:error];
            }
            
        };
        
        [self.accept requestAccessToken:[[NSUserDefaults standardUserDefaults] objectForKey:@"username"] password:self.passwordTf.text config:[[Utils sharedInstance] backendConfig] completion:^(AcceptAccessToken *accessToken, NSError *error)
        {
            [[Utils sharedInstance] setAccessToken: (accessToken.accessToken)? : @""];
            self.error = error;
            self.errorObject = nil;
            
            if (error)
            {
                AcceptRequestTokenErrorCode errCode = ((AcceptRequestTokenErrorCode)self.error.code);
                self.errorObject = [NSValue value:&errCode withObjCType:@encode(AcceptRequestTokenErrorCode)];
                completionBlock(accessToken.accessToken, error);
            }
            else
            {
                void(^completionConfig)(AcceptTerminalConfigFiles*, NSError*)   =  ^(AcceptTerminalConfigFiles* configFiles, NSError* error){
                    if (configFiles && !error)
                    {
                        NSMutableDictionary *terminalVersionDict = [[NSMutableDictionary alloc] init];
                        [terminalVersionDict setObject:[configFiles getVersion] forKey:AcceptSpireVendorUUID];
                        [[Utils sharedInstance] setVendorConfigurationVersion:terminalVersionDict];
                    }
                };
                
                [self.accept queryConfigFile:[[Utils sharedInstance] accessToken] config:[[Utils sharedInstance] backendConfig] andCurrentVersion:@"0" completion:completionConfig];

                [self.accept requestMerchantInfo:[[Utils sharedInstance] accessToken]  config:[[Utils sharedInstance] backendConfig] completion:^(AcceptUserResponse *response, NSError *error)
                {
                    self.userResponse = response;
                    completionBlock(accessToken.accessToken, error);
                }];
            }
        }];
    }
}

-(void)loginChangePassFailure:(NSError *)error
{
    NSLog(@">>> UserViewController - loginChangePassFailure");
    [[NSOperationQueue mainQueue] addOperationWithBlock:
     ^{
         [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
         [Utils showAlertWithTitle:@"Login Error" andMessage:@"Password could not be changed, please check that your old password is correct"];
     }];
}

-(void)loginChangePassSuccess:(NSError *)error
{
    NSLog(@">>> UserViewController - loginChangePassSuccess");
    __weak UserViewController *weakSelf = self;
    
    void (^completionBlock)(BOOL, NSError*) = ^(BOOL success, NSError *error)
    {
        if ((success && !error) || (success && error && error.code == 200))
        {
            [weakSelf passwordChanged:error];
        }
        else{
            [weakSelf passwordFailure:error];
        }
    };
    
    [self.accept changePasswordForToken:[[Utils sharedInstance] accessToken]  newPassword:self.passwordTf.text reNewPassword:self.forgotTf.text config:[[Utils sharedInstance] backendConfig]  completion:completionBlock];
}

-(void) passwordChanged:(NSError *)error
{
    NSLog(@">>> UserViewController - passwordChanged");
    [[NSOperationQueue mainQueue] addOperationWithBlock:
     ^{
         [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
         [Utils showAlertWithTitle:@"Password changed" andMessage:@"Your password was changed successfully"];
     }];
}

-(void)passwordFailure:(NSError *)error
{
    NSLog(@">>> UserViewController - passwordFailure");
    [[NSOperationQueue mainQueue] addOperationWithBlock:
     ^{
         [[UIApplication sharedApplication] setNetworkActivityIndicatorVisible:NO];
         NSString *title, *message;
         
         if (error && error.code == 1)
         {
             title = NSLocalizedString(@"Password changed", @"Password changed");
             message = NSLocalizedString(@"Your new password does not meet the requirements", @"Your new password does not meet the requirements");
         }
         else
         {
             title = NSLocalizedString(@"Connection Error", @"Connection Error");
             message = NSLocalizedString(@"Server error trying to change the password, please try again later", @"Server error trying to change the password, please try again later");
         }
         
         [Utils showAlertWithTitle:title andMessage:message];
     }];
}

#pragma mark - Main Action On Tap Method

- (IBAction)onTapLogin:(id)sender
{
    NSLog(@">>> UserViewController - onTapLogin");
    [self onTapBackground:nil];
    
    if ([[[self.loginBtn titleLabel] text] isEqualToString:@"Please wait ..."]) {
        return;
    }
    
    if ([[Utils sharedInstance] tokenExpired] && self.segmentC.selectedSegmentIndex != EnumLogin)
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"The token expired, please login again"];
        return;
    }
    
    switch (self.segmentC.selectedSegmentIndex)
    {
        case EnumLogin:
            [self.loginBtn setTitle:@"Please wait ..." forState:UIControlStateNormal];
            [self doLogin];
            break;
        case EnumForgotUserID:
            [self doForgotUserID];
            break;
        case EnumForgotPW:
            [self doForgotPW];
            break;
        case EnumChangePW:
        default:
            [self doChangePW];
            break;
    }
}

#pragma mark - TextField Delegate Methods

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    NSLog(@">>> UserViewController - textFieldShouldReturn");
    [self onTapBackground:nil];
    return YES;
}

-(IBAction)onTapBackground:(id)sender
{
    NSLog(@">>> UserViewController - onTapBackground");
    [self.passwordTf resignFirstResponder];
    [self.emailTf resignFirstResponder];
    [self.forgotTf resignFirstResponder];
}

@end

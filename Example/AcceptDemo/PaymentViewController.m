//
//  PaymentViewController.m
//  Accept Demo
//
//  Created by Fortes, Francisco on 10/27/14.
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import "PaymentViewController.h"
#import "Accept.h"
#import "Utils.h"
#import "BarCodeScannerIOS.h"

typedef NS_ENUM(NSInteger, ActionSheetType) {
    ACTION_SHEET_TRANSACTION     =0,
    ACTION_SHEET_FIRMWARE     =1,
    ACTION_SHEET_ERROR = 2
};

typedef NS_ENUM(NSInteger, TransactionMode) {
    TRANSACTION_MODE_CARD     =0,
    TRANSACTION_MODE_CASH     =1,
    TRANSACTION_MODE_ALIPAY   =2
};

@interface PaymentViewController ()

@property(nonatomic, weak) IBOutlet UITextField *amountTf;
@property(nonatomic, weak) IBOutlet UITextField *terminalTf;
@property(nonatomic, weak) IBOutlet UITextField *currencyTf;
@property(nonatomic, weak) IBOutlet UITextField *printerTf;
@property(nonatomic, weak) IBOutlet UIButton *payB;
@property (weak, nonatomic) IBOutlet UIButton *captureB;
@property(nonatomic, weak) IBOutlet UIButton *revertB;
@property(nonatomic, weak) IBOutlet UIButton *printB;
@property(nonatomic, weak) IBOutlet UITextView *infolbl;
@property(nonatomic, weak) IBOutlet UILabel *tokenlbl;
@property (nonatomic,strong) NSArray *arrVendors;
@property (nonatomic,strong) NSArray *arrCurrency;
@property (nonatomic,strong) NSArray *arrVendorTerminals;
@property (nonatomic,strong) NSArray *arrPrinterVendors;
@property (nonatomic,strong) NSArray *arrPrinters;
@property (nonatomic,weak) IBOutlet UIPickerView *pickerVendors;
@property (weak, nonatomic) IBOutlet UIPickerView *pickerCurrency;
@property (weak, nonatomic) IBOutlet UIPickerView *pickerPrinters;
@property (weak, nonatomic) IBOutlet UIToolbar *keyboardToolbar;
@property (nonatomic, weak) Accept *accept;
@property (nonatomic,strong) NSString *previouslySelectedVendor;
@property (strong, nonatomic) NSTimer *btTimer;
@property (strong,nonatomic) AcceptAppSelectionRequest *  appSelectionRequest;
@property (strong,nonatomic) AcceptSignatureRequest *  signatureRequest;
@property (strong,nonatomic) AcceptTransaction *transaction;
@end

@implementation PaymentViewController

-(void)dealloc
{
    [self.btTimer invalidate];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.amountTf.inputAccessoryView = self.keyboardToolbar;
    self.amountTf.keyboardType = UIKeyboardTypeNumberPad;
    self.printerTf.inputAccessoryView = self.keyboardToolbar;
    self.printerTf.inputView = self.pickerPrinters;
    self.terminalTf.inputAccessoryView = self.keyboardToolbar;
    self.terminalTf.inputView = self.pickerVendors;
    self.currencyTf.inputAccessoryView = self.keyboardToolbar;
    self.currencyTf.inputView = self.pickerCurrency;
    self.accept = [[Utils sharedInstance] accept];
    NSLog(@"version:%@",
          [self.accept version]);
    
    [self populateVendorsList];
    [self populatePrinterVendors];
    [self populateCurrencyList];
    
    [self.tokenlbl setText:@"No Token"];
    [self.tokenlbl setTextColor:[UIColor redColor]];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(tokenDidExpire)
                                                 name:kTokenTimerNotificationName
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(applicationEnteredForeground:)
                                                 name:UIApplicationWillEnterForegroundNotification
                                               object:nil];
    [self.revertB setEnabled:NO];
    [self.captureB setEnabled:NO];
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    self.btTimer = nil;
    self.btTimer = [NSTimer scheduledTimerWithTimeInterval:kRefreshBT target:self selector:@selector(updateBluetoothTerminalList) userInfo:nil repeats:YES];
    [self.btTimer fire];
    [self.tokenlbl setTextColor:([[Utils sharedInstance] tokenIsValid])? [UIColor greenColor] : [UIColor redColor]];
    [self.tokenlbl setText:([[Utils sharedInstance] tokenIsValid])? @"Valid token" : @"Token expired or empty, please login"];
    [self.revertB setEnabled:(self.transaction != nil)];
    [self.captureB setEnabled:(self.transaction != nil)];
    
}

- (void)applicationEnteredForeground:(NSNotification *)notification
{
    NSLog(@">>> PaymentViewController - Application Entered Foreground");
    [self.tokenlbl setTextColor:([[Utils sharedInstance] tokenIsValid])? [UIColor greenColor] : [UIColor redColor]];
    [self.tokenlbl setText:([[Utils sharedInstance] tokenIsValid])? @"Valid token" : @"Token expired or empty, please login"];
}

-(void)viewWillDisappear:(BOOL)animated
{
    [self.btTimer invalidate];
    [super viewWillDisappear:animated];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - Populate Methods

-(void)populatePrinterVendors
{
    NSLog(@">>> PaymentViewController - populatePrinterVendors");
    __weak PaymentViewController *weakSelf = self;
    [self.accept discoverSupportedPrinterVendors:^(NSArray *vendors) {
        weakSelf.arrPrinterVendors = vendors;
        [weakSelf.pickerPrinters reloadAllComponents];
        [weakSelf showSelectedPrinterVendor];
        [weakSelf populatePrintersList];
    }];
}

-(void)populateVendorsList
{
    NSLog(@">>> PaymentViewController - populateVendorsList");
    __weak PaymentViewController *weakSelf = self;
    [self.accept discoverSupportedVendors:^(NSArray *vendors) {
        weakSelf.arrVendors = vendors;
        [weakSelf.pickerVendors reloadAllComponents];
        [weakSelf showSelectedVendor];
        [weakSelf populateVendorTerminalList];
    }];
}

-(void)populateCurrencyList
{
    NSLog(@">>> PaymentViewController - populateCurrencyList");
    self.arrCurrency = [[Utils sharedInstance] currencies];
    self.currencyTf.enabled = self.arrCurrency.count > 0;
    [self showSelectedCurrency];
}

-(void)populateVendorTerminalList
{
    NSLog(@">>> PaymentViewController - populateVendorTerminalList");
    __weak PaymentViewController *weakSelf = self;
    
    NSString *iSelectedVendor = [[Utils sharedInstance] getSelectedVendor];
    
    self.arrVendorTerminals = [NSArray array];
    
    if (iSelectedVendor.length > 0)
    {
        [self.accept discoverTerminalsForVendor:iSelectedVendor completion:^(NSArray *discoveredTerminals, NSError *error)
         {
             weakSelf.arrVendorTerminals = discoveredTerminals;
             [weakSelf.pickerVendors reloadAllComponents];
             [weakSelf showSelectedVendorTerminal];
             
             if (error)
             {
                 [weakSelf handleError:error];
             }
             else if (discoveredTerminals.count > 0 && ([iSelectedVendor rangeOfString:AcceptSpireVendorUUID].location != NSNotFound || [iSelectedVendor rangeOfString:AcceptVeriFoneVendorUUID].location != NSNotFound) &&  ![iSelectedVendor isEqualToString: weakSelf.previouslySelectedVendor])
             {
                 [weakSelf checkForTerminalConfigurationChanges];
             }
         }];
    }
}

-(void)populatePrintersList
{
    NSLog(@">>> PaymentViewController - populatePrintersList");
    __weak PaymentViewController *weakSelf = self;
    
    NSString *iSelectedVendor = [[Utils sharedInstance] getSelectedPrinterVendor];
    
    if (iSelectedVendor.length > 0)
    {
        [self.accept discoverPrintersForVendor:iSelectedVendor completion:^(NSArray *discoveredPrinters, NSError *error)
         {
             weakSelf.arrPrinters = discoveredPrinters;
             [weakSelf.pickerPrinters reloadAllComponents];
             [weakSelf showSelectedPrinter];
             
             if (error)
             {
                 NSString *message = [NSString stringWithFormat:@"%@ %@", @"Configuration Error", error.localizedDescription];
                 [Utils showAlertWithTitle:@"Error" andMessage:message];
             }
         }];
    }
}

# pragma mark - Setup, Error Handling and Other Methods

-(void)handleError:(NSError*) error
{
    NSLog(@">>> PaymentViewController - handleError: %ld", (long)((error)? error.code : -12345));
    NSString *message;
    switch (error.code)
    {
        case AcceptConfigFilesInfoNoConnectionErrorCode:
            message = [NSString stringWithFormat:@"%@ %@", @"Please check your internet connection", error.localizedDescription];
            break;
        case AcceptConfigFilesInfoTimeoutErrorCode:
            message = [NSString stringWithFormat:@"%@ %@", @"The server is taking too long to respond", error.localizedDescription];
            break;
        case AcceptConfigFilesInfoNoProperResponseErrorCode:
            message = [NSString stringWithFormat:@"%@ %@", @"Unable to get configuration data from server, please contact your technical support", error.localizedDescription];
            break;
        default:
            message = [NSString stringWithFormat:@"%@ %@", @"Unknown Error", error.localizedDescription];
            break;
    }
    
    [Utils showAlertWithTitle:@"Error" andMessage:message];
}

-(void)tokenDidExpire
{
    NSLog(@">>> PaymentViewController - tokenDidExpire");
    [self.tokenlbl setTextColor:[UIColor redColor]];
    [self.tokenlbl setText:@"Token expired"];
    [self.revertB setEnabled:NO];
    [self.captureB setEnabled:NO];
}

-(void)getMerchantInfoSuccess:(AcceptUserResponse *)response
{
    NSLog(@">>> PaymentViewController - getMerchantInfoSuccess");
    NSLog(@"%@",response);
}

-(void)updateBluetoothTerminalList
{
    NSLog(@">>> PaymentViewController - updateBluetoothTerminalList");
    if ([[AcceptUtils sharedInstance] isVendorHavingBluetoothTerminals:[[Utils sharedInstance] getSelectedVendor]])
    {
        [self populateVendorTerminalList];
    }
}

-(void)done //tap was done somewhere, so close keyboard
{
    NSLog(@">>> PaymentViewController - done");
    [self.terminalTf resignFirstResponder];
    [self.printerTf resignFirstResponder];
    [self.currencyTf resignFirstResponder];
    [self.amountTf resignFirstResponder];
}

- (IBAction)onTapDone:(id)sender
{
    NSLog(@">>> PaymentViewController - onTapDone");
    [self done];
}

-(void)checkForTerminalConfigurationChanges
{
    NSLog(@">>> PaymentViewController - checkForTerminalConfigurationChanges");
    NSString *iSelectedVendor = [[Utils sharedInstance] getSelectedVendor];
    NSString *iSelectedTerminal = [[Utils sharedInstance] getSelectedTerminal];
    
    if ([iSelectedVendor rangeOfString:AcceptSpireVendorUUID].location == NSNotFound && [iSelectedVendor rangeOfString:AcceptVeriFoneVendorUUID].location == NSNotFound)
    {
        return ;
    }
    else
    {
        NSString *version = [[Utils sharedInstance] getVendorTerminalConfigurationVersion:iSelectedVendor terminalUUID:iSelectedTerminal];
        NSString *latestVersionOnServer = [[Utils sharedInstance] getVendorConfigurationVersion:iSelectedVendor];
        if ([version isEqualToString:latestVersionOnServer]) {
            return;
        }
    }
    
    //only get the config info if we're using blue tooth terminal (in our case, PosMate)
    
    void(^completionConfig)(AcceptTerminalConfigFiles*, NSError*)   =  ^(AcceptTerminalConfigFiles* configFiles, NSError* error){
        if (configFiles && !error)
        {
            NSMutableDictionary *terminalVersionDict = [[NSMutableDictionary alloc] init];
            
            [terminalVersionDict setObject:[configFiles getVersion] forKey:iSelectedTerminal];
            
            NSDictionary *dictTerminal = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObject:terminalVersionDict] forKeys:[NSArray arrayWithObject:iSelectedVendor]];
            
            NSString *version = [[Utils sharedInstance] getVendorTerminalConfigurationVersion:iSelectedVendor terminalUUID:iSelectedTerminal];
            
            if (!version || ![version isEqualToString:[configFiles getVersion]]) {
                //initiate the config file upload
                [self.accept discoverTerminalsForVendor:iSelectedVendor completion:^(NSArray *discoveredTerminals, NSError *error)
                 {
                     if (error)
                     {
                         [Utils showAlertWithTitle:@"Error" andMessage:[NSString stringWithFormat: @"Error discovering terminals %@", error.description]];
                     }
                     else if (discoveredTerminals.count > 0 && ([iSelectedVendor rangeOfString:AcceptSpireVendorUUID].location != NSNotFound || [iSelectedVendor rangeOfString:AcceptVeriFoneVendorUUID].location != NSNotFound) )
                     {
                         void (^completionAlertUI)(NSInteger, NSError*) = ^(NSInteger alertCode, NSError *error)
                         {
                             if (alertCode > 0)
                             {
                                 if (alertCode == AcceptConfigFilesSuccess || (!version && alertCode == AcceptConfigFilesUnnecessary))
                                 {
                                     //For keeping track of what version of config files was installed on what device, we set it up on user preferences with the function below. You are free to do it differently, but consider that regular checkings for config files are mandatory to avoid issues with your payments.
                                     [[Utils sharedInstance] setTerminalConfigurationUploads:dictTerminal];
                                 }
                             }
                             
                         };
                         
                         void (^progress)(AcceptConfigFilesProgress) = ^(AcceptConfigFilesProgress progress)
                         {
                             [self updateInfoLabel:[NSString stringWithFormat:@"Progress updating terminal, code: %ld", (long)progress]];
                         };
                         
                         AcceptTerminalVendor *currentVendor;
                         for(AcceptTerminalVendor *vendor in self.arrVendors)
                         {
                             if ([vendor.uuid isEqualToString:iSelectedVendor])
                             {
                                 currentVendor = vendor;
                             }
                         }
                         
                         [[[Utils sharedInstance] accept] updateTerminal:discoveredTerminals.firstObject
                                                                  vendor:currentVendor
                                                                   token:[[Utils sharedInstance] accessTokenObject].accessToken
                                                                  config:[[Utils sharedInstance] backendConfig]
                                                                progress:progress completion:completionAlertUI];
                     }
                 }];
            }
            else
            {
                [Utils showAlertWithTitle:@"Error" andMessage:[NSString stringWithFormat: @"Requesting config files there was an error %@", error.description]];
            }
        }
    };
    
    NSString * version = @"0";
    
    [[[Utils sharedInstance] accept]  queryConfigFile:[[Utils sharedInstance] accessTokenObject].accessToken config:[[Utils sharedInstance] backendConfig]  andCurrentVersion:version completion:completionConfig];
}

#pragma mark - PickerViewDelegate methods

- (NSInteger)numberOfComponentsInPickerView:(UIPickerView *)pickerView
{
    NSLog(@">>> PaymentViewController - numberOfComponentsInPickerView");
    if (pickerView.tag == 10 || pickerView.tag == 30) //vendor && printer
    {
        return 2;
    }
    else
    {
        return 1; //currency
    }
}

- (NSInteger)pickerView:(UIPickerView *)pickerView numberOfRowsInComponent:(NSInteger)component
{
    NSLog(@">>> PaymentViewController - pickerView:numberOfRowsInComponent");
    if (pickerView.tag == 10) //vendor
    {
        if (component == 0)
        {
            return self.arrVendors.count;
        }
        else{
            return self.arrVendorTerminals.count;
        }
    }
    else if (pickerView.tag == 30) //printer
    {
        if (component == 0)
        {
            return self.arrPrinterVendors.count;
        }
        else
        {
            return self.arrPrinters.count;
        }
    }
    else //currency
    {
        return self.arrCurrency.count;
    }
}

-(UIView *)pickerView:(UIPickerView *)pickerView viewForRow:(NSInteger)row forComponent:(NSInteger)component reusingView:(UIView *)view
{
    NSLog(@">>> PaymentViewController - pickerView:viewForRow");
    UILabel *lbl = (UILabel*)view;
    
    if (!lbl)
    {
        lbl = [[UILabel alloc] initWithFrame:CGRectMake(0.0, 0.0, 135, 32.0)];
        lbl.textAlignment = NSTextAlignmentLeft;
        lbl.backgroundColor = [UIColor clearColor];
        lbl.minimumScaleFactor = 0.5;
    }
    
    if (pickerView.tag == 10)
    {
        if (component == 0)
        {
            lbl.frame = CGRectMake(0.0, 0.0, 110, 32.0);
            AcceptTerminalVendor *vendor = [self.arrVendors objectAtIndex:row];
            lbl.text = vendor.alternativeDisplayName;
            
        }
        else
        {
            lbl.frame = CGRectMake(0.0, 0.0, 160, 32.0);
            if (self.arrVendorTerminals.count > 0)
            {
                AcceptTerminal *terminal = [self.arrVendorTerminals objectAtIndex:row];
                lbl.text = terminal.alternativeDisplayName;
            }
            else
            {
                lbl.text = NSLocalizedString(@"Please wait", @"Please wait");
            }
        }
    }
    else if (pickerView.tag == 30)
    {
        if (component == 0)
        {
            lbl.frame = CGRectMake(0.0, 0.0, 110, 32.0);
            AcceptPrinterVendor *vendor = [self.arrPrinterVendors objectAtIndex:row];
            lbl.text = vendor.alternativeDisplayName;
        }
        else
        {
            lbl.frame = CGRectMake(0.0, 0.0, 160, 32.0);
            AcceptPrinter *printer = [self.arrPrinters objectAtIndex:row];
            lbl.text = printer.alternativeDisplayName;
        }
    }
    else{
        lbl.frame = CGRectMake(0.0, 0.0, 270, 32.0);
        NSString *currencyCode = [self.arrCurrency objectAtIndex:row];
        lbl.textAlignment = NSTextAlignmentCenter;
        lbl.text = currencyCode;
    }
    
    return lbl;
}

- (void)pickerView:(UIPickerView *)pickerView didSelectRow:(NSInteger)row inComponent:(NSInteger)component
{
    NSLog(@">>> PaymentViewController - pickerView:didSelectRow");
    if (pickerView.tag == 10)
    {
        if (component == 0)
        {
            [self.pickerVendors reloadAllComponents];
            AcceptTerminalVendor *vendor = [self.arrVendors objectAtIndex:row];
            [[Utils sharedInstance] setSelectedVendor:[[AcceptUtils sharedInstance] vendorIDForName:vendor.displayName andUUID:vendor.uuid]];
            [self showSelectedVendor];
            [[Utils sharedInstance] setSelectedTerminal:@""];
            [self populateVendorTerminalList];
        }
        else
        {
            if ([self.arrVendorTerminals count] > 0)
            {
                AcceptTerminal *terminal = [self.arrVendorTerminals objectAtIndex:row];
                [[Utils sharedInstance] setSelectedTerminal:terminal.displayName];
                [self showSelectedVendorTerminal];
            }
            else
            {
                [[Utils sharedInstance] setSelectedTerminal:@""];
            }
        }
    }
    else if (pickerView.tag == 30)
    {
        if (component == 0)
        {
            AcceptPrinterVendor *vendor = [self.arrPrinterVendors objectAtIndex:row];
            [[Utils sharedInstance] setPrinterVendorDefaultValue:vendor.uuid];
            [self showSelectedPrinterVendor];
            [self populatePrintersList];
            
        }
        else
        {
            if ([self.arrPrinters count] > 0)
            {
                AcceptPrinter *printer = [self.arrPrinters objectAtIndex:row];
                [[Utils sharedInstance] setPrinterDefaultValue:printer.displayName];
                [self showSelectedPrinter];
            }
            else
            {
                [[Utils sharedInstance] setPrinterDefaultValue:@""];
            }
        }
    }
    else
    {
        [[Utils sharedInstance] setCurrencyCodeDefaultValue:[self.arrCurrency objectAtIndex:row]];
        [self showSelectedCurrency];
    }
    
    if (pickerView.tag == 10)
    {
        self.previouslySelectedVendor = [[Utils sharedInstance] getSelectedVendor];
    }
    
}

#pragma mark - Showing Methods

-(void)showSelectedVendor
{
    NSLog(@">>> PaymentViewController - showSelectedVendor");
    NSString *iSelectedVendor = [[Utils sharedInstance] getSelectedVendor];
    NSUInteger index = NSNotFound;
    if (iSelectedVendor.length > 0)
    {
        index = [self.arrVendors indexOfObjectPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
            AcceptTerminalVendor *vendor = (AcceptTerminalVendor *) obj;
            if ([vendor.uuid isEqualToString:iSelectedVendor]) {
                *stop = YES;
                return YES;
            }
            return NO;
        }];
    }
    
    if (index == NSNotFound)
    {
        if (self.arrVendors.count == 0) return;
        index = 0;
    }
    
    [self.pickerVendors selectRow:index inComponent:0 animated:NO];
    AcceptTerminalVendor *vendor = [self.arrVendors objectAtIndex:index];
    
    [[NSUserDefaults standardUserDefaults] setObject:[[AcceptUtils sharedInstance] vendorIDForName:vendor.displayName andUUID:vendor.uuid] forKey:@"selectedVendor"];
    
    self.terminalTf.text = [NSString stringWithFormat:@"%@ | %@",vendor.alternativeDisplayName,@"-"];
}

-(void)showSelectedPrinterVendor
{
    NSLog(@">>> PaymentViewController - showSelectedPrinterVendor");
    NSString *iSelectedVendor = [[Utils sharedInstance] getSelectedPrinterVendor];
    NSUInteger index = NSNotFound;
    if (iSelectedVendor.length > 0)
    {
        index = [self.arrPrinterVendors indexOfObjectPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
            AcceptPrinterVendor *vendor = (AcceptPrinterVendor *) obj;
            if ([vendor.uuid isEqualToString:iSelectedVendor]) {
                *stop = YES;
                return YES;
            }
            return NO;
        }];
    }
    
    if (index == NSNotFound)
    {
        if (self.arrPrinterVendors.count == 0) return;
        index = 0;
    }
    
    [self.pickerPrinters selectRow:index inComponent:0 animated:NO];
    AcceptPrinterVendor *vendor = [self.arrPrinterVendors objectAtIndex:index];
    
    [[Utils sharedInstance] setPrinterVendorDefaultValue:vendor.uuid];
    
    self.printerTf.text = [NSString stringWithFormat:@"%@ | %@",vendor.alternativeDisplayName,@"-"];
    
}

-(void)showSelectedCurrency
{
    NSLog(@">>> PaymentViewController - showSelectedCurrency");
    NSString *iSelectedCurrency= [[Utils sharedInstance] getCurrencyCodeDefaultValue];
    
    NSUInteger index = [self.arrCurrency indexOfObjectPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
        NSString *currencyCode = (NSString *) obj;
        if ([currencyCode isEqualToString:iSelectedCurrency])
        {
            *stop = YES;
            return YES;
        }
        return NO;
    }];
    
    if (index != NSNotFound)
    {
        [self.pickerCurrency selectRow:index inComponent:0 animated:NO];
        [[Utils sharedInstance] setCurrencyCodeDefaultValue:iSelectedCurrency];
        self.currencyTf.text = [NSString stringWithFormat:@"%@ - %@" , iSelectedCurrency, [[Utils sharedInstance] getCurrencySymbolDefaultValue]];
        
    }
}


-(void)showSelectedVendorTerminal
{
    NSLog(@">>> PaymentViewController - showSelectedVendorTerminal");
    NSString *iSelectedVendorTerminal = [[Utils sharedInstance] getSelectedTerminal];
    NSUInteger index = NSNotFound;
    if (iSelectedVendorTerminal.length > 0)
    {
        index = [self.arrVendorTerminals indexOfObjectPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
            AcceptTerminal *terminal = (AcceptTerminal *) obj;
            if ([terminal.displayName isEqualToString:iSelectedVendorTerminal]) {
                *stop = YES;
                return YES;
            }
            return NO;
        }];
    }
    
    if (index == NSNotFound)
    {
        if (self.arrVendorTerminals.count == 0) return;
        //default to first terminal in the list
        index = 0;
    }
    
    [self.pickerVendors selectRow:index inComponent:1 animated:NO];
    AcceptTerminal *terminal = [self.arrVendorTerminals objectAtIndex:index];
    
    NSArray *arr = [self.terminalTf.text componentsSeparatedByString:@"|"];
    
    self.terminalTf.text = [NSString stringWithFormat:@"%@ | %@",[[arr firstObject] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]],terminal.alternativeDisplayName];
    
    NSLog(@"%@",  self.terminalTf.text);
    
    [[Utils sharedInstance] setSelectedTerminal:terminal.displayName];
}

-(void)showSelectedPrinter
{
    NSLog(@">>> PaymentViewController - showSelectedPrinter");
    NSString *iSelectedVendorPrinter = [[Utils sharedInstance] getSelectedPrinter];
    NSUInteger index = NSNotFound;
    if (iSelectedVendorPrinter.length > 0)
    {
        
        index = [self.arrPrinters indexOfObjectPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
            AcceptPrinter *printer = (AcceptPrinter *) obj;
            if ([printer.displayName isEqualToString:iSelectedVendorPrinter]) {
                *stop = YES;
                return YES;
            }
            return NO;
        }];
    }
    
    if (index == NSNotFound)
    {
        if (self.arrPrinters.count == 0) return;
        //default to first terminal in the list if only one terminal is there
        if (self.arrPrinters.count == 1)
        {
            index = 0;
        }
    }
    
    [self.pickerPrinters selectRow:index inComponent:1 animated:NO];
    AcceptPrinter *printer = [self.arrPrinters objectAtIndex:index];
    
    NSArray *arr = [self.printerTf.text componentsSeparatedByString:@"|"];
    
    self.printerTf.text = [NSString stringWithFormat:@"%@ | %@",[[arr firstObject] stringByTrimmingCharactersInSet:[NSCharacterSet whitespaceCharacterSet]],printer.alternativeDisplayName];
    
    [[Utils sharedInstance] setPrinterDefaultValue:printer.displayName];
}



#pragma mark - Payment Methods

- (IBAction)opTapAutorize:(id)sender {
    [self payWithCard:AcceptTransactionTypeAuthorize];
}
- (IBAction)opTapCapture:(id)sender {
    NSLog(@">>> PaymentViewController - onTapCapture");
    __weak PaymentViewController *weakSelf = self;
    void (^completionBlock)(AcceptTransaction*, NSError*) = ^(AcceptTransaction *transaction, NSError *error)
    {
        NSString *message, *title;
        if (transaction && transaction.uniqueId.length > 0)
        {
            if (!transaction.capturable)
            {
                title = @"Success";
                message = NSLocalizedString(@"Transaction captured successfully", "Transaction captured successfully");
                weakSelf.transaction = nil;
                [weakSelf.captureB setEnabled:NO];
            }
            else
            {
                title = @"Error";
                message = @"Online data processing error";
            }
        }
        else
        {
            title = @"Error";
            message = @"Online data processing error";
        }
        
        [Utils showAlertWithTitle:title andMessage:message];
    };
    
    if (self.transaction && self.transaction.uniqueId.length >0 && self.transaction.reversible)
    {
        [self.accept requestOperationOnPaymentWithID:self.transaction.uniqueId
                                      andAccessToken:[[Utils sharedInstance] accessTokenObject].accessToken
                                              config:[[Utils sharedInstance] backendConfig]
                                           operation:AcceptOperationOnPaymentCapture
                             paymentUpdateParameters:nil //this is used for sending receipt through email, phone number, etc.
                                          completion:completionBlock];
    }
    else
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"No transaction to reverse"];
    }
    
}

-(IBAction)opTapPay:(id)sender
{
    NSLog(@">>> PaymentViewController - opTapPay");
    [self done];
    
    if ([[Utils sharedInstance] tokenExpired])
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"The token expired, please login again"];
        return;
    }
    
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"What type of payment you want?"
                                                             delegate:self
                                                    cancelButtonTitle:@"Cancel"
                                               destructiveButtonTitle:nil
                                                    otherButtonTitles:@"Card - Using reader", @"Cash Only",@"Alipay", nil];
    actionSheet.tag = ACTION_SHEET_TRANSACTION;
    [actionSheet showInView:self.view];
}

-(void)actionSheet:(UIActionSheet *)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    if (actionSheet.tag == ACTION_SHEET_TRANSACTION) //Payment
    {
        if (buttonIndex < 3)
        {
            [self startPaymentMode:buttonIndex];
        }
    }
    else if (actionSheet.tag == ACTION_SHEET_FIRMWARE) //firmware update
    {
        if (buttonIndex == 0)
        {
            [self updateTerminalFirmware];
        }
    }
}

-(void)payWithCard:(AcceptTransactionType) transactionType
{
    
    NSLog(@">>> PaymentViewController - startPayment");
    if ([[Utils sharedInstance] isPaymentTimerOngoing]) //There was a swipe timeout, device will need some time before being able to retry the payment.
    {
        self.infolbl.text = @"Waiting for device...";
        return; //we reject the payment here. There will be a notification calling startPayment after timer is done.
    }
    else if ([Utils sharedInstance].accessTokenObject.accessToken.length == 0)
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"Not token found, please login"];
        return;
    }
    else if (self.amountTf.text.length == 0)
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"Please write some amount"];
        return;
    }
    else
    {
        self.infolbl.text = @"Payment started";
    }
    
    NSString *iSelectedVendorTerminalDisplayName = [[Utils sharedInstance] getSelectedTerminal];
    id iSelectedVendorUUID = [[AcceptUtils sharedInstance] vendorIDForName:iSelectedVendorTerminalDisplayName andUUID:[[Utils sharedInstance] getSelectedVendor]];
    id iSelectedCurrency = [[Utils sharedInstance] getCurrencyCodeDefaultValue];
    
    __weak PaymentViewController *weakSelf = self;
    
    void (^completion)(AcceptTransaction*, NSError*) = ^(AcceptTransaction *transaction, NSError *error)
    {
        NSLog(@"%@",[[transaction getAcceptReceiptData] receiptDescription]);
        if (error || !transaction)
        {
            [weakSelf paymentFailure:error transaction:transaction];
        }
        else
        {
            [weakSelf performSelectorOnMainThread:@selector(paymentDone:) withObject:transaction waitUntilDone:NO];
        }
    };
    
    void(^progress)(AcceptStateUpdate) = ^(AcceptStateUpdate update)
    {
        [weakSelf paymentProgress:update];
    };
    
    
    void(^signature)(AcceptSignatureRequest * ) = ^(AcceptSignatureRequest *  signatureRequest)
    {
        [weakSelf requestSignature:signatureRequest];
    };
    
    void (^signatureVerification)(AcceptTransaction*, AcceptSignatureVerificationResultCallback,NSError*) = ^(AcceptTransaction *transaction,AcceptSignatureVerificationResultCallback signatureVerificationCallbackMerchantResponse, NSError *error)
    {
        
        if (signatureVerificationCallbackMerchantResponse) {
            //implement the confirmation for the signature Approval/Rejection and call signatureVerificationCallbackMerchantResponse with Approved or Rejected accordingly
            signatureVerificationCallbackMerchantResponse(AcceptSignatureVerificationResultApproved);
        }
        else{
            if (error || !transaction) {
                
                [weakSelf paymentFailure:error transaction:transaction];
            }
            else{
                
                [weakSelf performSelectorOnMainThread:@selector(confirmSignature) withObject:transaction waitUntilDone:NO];
                //            [weakSelf paymentSuccess:transaction];
            }
        }
        
    };
    
    void(^appSelection)(AcceptAppSelectionRequest * ) = ^(AcceptAppSelectionRequest * appSelectionRequest)
    {
        [weakSelf requestAppSelection:appSelectionRequest];
    };
    
    [self.accept discoverTerminalsForVendor:iSelectedVendorUUID completion:^(NSArray *discoveredTerminals, NSError *error)
     {
         AcceptTerminal *terminal = nil;
         
         
         for (AcceptTerminal *term in discoveredTerminals) {
             if ([term.displayName isEqualToString: iSelectedVendorTerminalDisplayName]) {
                 terminal = term;
                 break;
             }
         }
         
         if ([discoveredTerminals count] == 0 || !terminal)
         {
             [Utils showAlertWithTitle:@"Error" andMessage:@"No terminal was found"];
         }
         else if (terminal)
         {
             [self doPaymentThroughVendor:iSelectedVendorUUID
            vendorTerminalEAASerialNumber:terminal.eaaSerialNumber
                                 currency:iSelectedCurrency
                          transactionType:transactionType
                               completion:completion
                                 progress:progress
                                signature:signature
                    signatureVerification:signatureVerification
                             appSelection:appSelection];
         }
     }];
    
}

-(void)payWithCash
{
    __weak PaymentViewController *weakSelf = self;
    
    void(^progress)(AcceptStateUpdate) = ^(AcceptStateUpdate update)
    {
        [weakSelf paymentProgress:update];
    };
    
    void (^completion)(AcceptTransaction*, NSError*) = ^(AcceptTransaction *transaction, NSError *error)
    {
        if (error || !transaction)
        {
            [weakSelf paymentFailure:error transaction:transaction];
        }
        else
        {
            [weakSelf performSelectorOnMainThread:@selector(paymentDone:) withObject:transaction waitUntilDone:NO];
        }
    };
    
    //Preparing payment configuration
    AcceptPaymentConfig* paymentConfig = [[AcceptPaymentConfig alloc] init];
    paymentConfig.backendConfig = [Utils sharedInstance].backendConfig;
    paymentConfig.accessToken = [Utils sharedInstance].accessTokenObject.accessToken;
    paymentConfig.vendorUUID = [NSString string];
    paymentConfig.eaaSerialNumber = [NSString string];
    paymentConfig.allowGratuity = NO; //Gratuity is an optional feature for the payment
    
    //Initializing the basket
    AcceptBasket *basket = [[AcceptBasket alloc] init];
    basket.currencyAsISO4217Code = @"EUR";
    basket.netTaxation = [NSNumber numberWithInt:1] ; //Set to 0 for tax inclusive
    //Note: Basket has the option for setting latitude and longitude, in case the need the location in the payment info
    //basket.lat, basket.lng
    
    //Adding the payment item to the basket
    AcceptBasketItem *basketItem =
    [self addBasketItem:1 //This is the number of items. We could have more than one with the same price
                 amount:[NSDecimalNumber decimalNumberWithString:self.amountTf.text]
                   note:@"Here we can add some description of the payment"
                    tax:0 //value indicating the tax % (note: 7% is indicated by 700; 7 would be 0.07%)
             chargeType:@"NONE"/*there are 4 types of charge: NONE, NORMAL, TIP and SERVICE_CHARGE*/];
    
    [basket.items addObject:basketItem]; //Note that a basket could include many items on it repeating the precious lines for each payment item
    
    //add custom fields if required
    basket.customFields = @{@"myCustomOrderID":@"customOrderID"};
    
    //add sub merchant data if required
    AcceptSubMerchant *subMerchant = [AcceptSubMerchant new];
    subMerchant.subMerchantId = @"1234567889";
    subMerchant.name = @"MySubMerchant";
    subMerchant.country = @"Germany";
    subMerchant.state = @"";
    subMerchant.city =@"Munich";
    subMerchant.street = @"1 Circular";
    subMerchant.postalCode = @"12345";
    basket.subMerchant = subMerchant;
    
    //add Payment Engine details:
    basket.peFunctionID = @"MyPEFunctionID";
    basket.peJobID = @"MyPEJobID";
    
    //add Elasti Engine details:
    basket.eeDescriptor = @"MyEEDescriptor";
    basket.eeOrderNumber = @"MyEEOrderNumber";
    
    paymentConfig.basket = basket;
    
    [self.accept startCashPayment:paymentConfig completion:completion progress:progress];
    
}

-(void)payWithAlipay
{
    [self startAlipayScanner];
}

-(void)startPaymentMode:(TransactionMode)aMode
{
    if (self.amountTf.text.length == 0)
    {
        //Note that depending on your backend and merchant configuration there will be a smallest and bigger amount possible, and you should validate the amount before submitting. You can ask for defining those limits during merchant set up.
        double delayInSeconds = 0.1; //We delay a little bit so previous action dismisses
        dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
        dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
            UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"Error, amount field is empty"
                                                                     delegate:self
                                                            cancelButtonTitle:@"Cancel"
                                                       destructiveButtonTitle:nil
                                                            otherButtonTitles:nil];
            actionSheet.tag = ACTION_SHEET_ERROR;
            [actionSheet showInView:self.view];
        });
        return;
    }
    
    switch (aMode)
    {
        case TRANSACTION_MODE_CARD://A card payment uses EMV standars and requires a card, payment engine, etc
            [self payWithCard:AcceptTransactionTypePurchase];
            break;
        case TRANSACTION_MODE_CASH: //A cash payment just generates a log of a payment in backend
            [self payWithCash];
            break;
        case TRANSACTION_MODE_ALIPAY: //An Alipay payment just generates a log of a payment in backend
            [self payWithAlipay];
            break;
        default:
            break;
    }
}

-(void)doPaymentThroughVendor:(NSString *)vendorUUID
vendorTerminalEAASerialNumber:(NSString *)terminalEAASerialNumber
                     currency:(NSString *)currency
              transactionType:(AcceptTransactionType) transactionType
                   completion:(void (^)(AcceptTransaction *transaction, NSError *error))completion
                     progress:(void (^)(AcceptStateUpdate))progress
                    signature:(void (^)(AcceptSignatureRequest * ))signature
        signatureVerification:(void (^)(AcceptTransaction*,AcceptSignatureVerificationResultCallback, NSError*))signatureVerification
                 appSelection:(void (^)(AcceptAppSelectionRequest * ))appSelection
{
    NSLog(@">>> PaymentViewController - doPaymentThroughVendor");
    
    //Preparing payment configuration
    AcceptPaymentConfig* paymentConfig = [[AcceptPaymentConfig alloc] init];
    paymentConfig.backendConfig = [Utils sharedInstance].backendConfig;
    paymentConfig.accessToken = [Utils sharedInstance].accessTokenObject.accessToken;
    paymentConfig.vendorUUID = vendorUUID;
    paymentConfig.eaaSerialNumber = terminalEAASerialNumber;
    paymentConfig.allowGratuity = NO; //Gratuity is an optional feature for the payment
    paymentConfig.transactionType = transactionType;
    //Initializing the basket
    AcceptBasket *basket = [[AcceptBasket alloc] init];
    basket.currencyAsISO4217Code = currency;
    basket.netTaxation = [NSNumber numberWithInt:1] ; //Set to 0 for tax inclusive
    //Note: Basket has the option for setting latitude and longitude, in case the need the location in the payment info
    //basket.lat, basket.lng
    
    //Adding the payment item to the basket
    AcceptBasketItem *basketItem =
    [self addBasketItem:1 //This is the number of items. We could have more than one with the same price
                 amount:[NSDecimalNumber decimalNumberWithString:self.amountTf.text]
                   note:@"Here we can add some description of the payment"
                    tax:0 //value indicating the tax % (note: 7% is indicated by 700; 7 would be 0.07%)
             chargeType:@"NONE"/*there are 4 types of charge: NONE, NORMAL, TIP and SERVICE_CHARGE*/];
    
    [basket.items addObject:basketItem]; //Note that a basket could include many items on it repeating the precious lines for each payment item
    //add custom fields if required
    basket.customFields = @{@"myCustomOrderID":@"customOrderID"};
    
    //add sub merchant data if required
    AcceptSubMerchant *subMerchant = [AcceptSubMerchant new];
    subMerchant.subMerchantId = @"1234567889";
    subMerchant.name = @"MySubMerchant";
    subMerchant.country = @"Germany";
    subMerchant.state = @"";
    subMerchant.city =@"Munich";
    subMerchant.street = @"1 Circular";
    subMerchant.postalCode = @"12345";

    basket.subMerchant = subMerchant;
    
    //add Payment Engine details:
    basket.peFunctionID = @"MyPEFunctionID";
    basket.peJobID = @"MyPEJobID";
    
    //add Elasti Engine details:
    basket.eeDescriptor = @"MyEEDescriptor";
    basket.eeOrderNumber = @"MyEEOrderNumber";
    
    paymentConfig.basket = basket;
    
    //We execute the payment
    [self.accept startPay:paymentConfig completion:completion progress:progress signature:signature signatureVerification:signatureVerification appSelection:appSelection];
    
}

-(void)doAutorizeTransaction:(NSString *)vendorUUID
vendorTerminalEAASerialNumber:(NSString *)terminalEAASerialNumber
                    currency:(NSString *)currency
                  completion:(void (^)(AcceptTransaction *transaction, NSError *error))completion
                    progress:(void (^)(AcceptStateUpdate))progress
                   signature:(void (^)(AcceptSignatureRequest * ))signature
       signatureVerification:(void (^)(AcceptTransaction*,AcceptSignatureVerificationResultCallback, NSError*))signatureVerification
                appSelection:(void (^)(AcceptAppSelectionRequest * ))appSelection
{
    NSLog(@">>> PaymentViewController - doPaymentThroughVendor");
    
    //Preparing payment configuration
    AcceptPaymentConfig* paymentConfig = [[AcceptPaymentConfig alloc] init];
    paymentConfig.backendConfig = [Utils sharedInstance].backendConfig;
    paymentConfig.accessToken = [Utils sharedInstance].accessTokenObject.accessToken;
    paymentConfig.vendorUUID = vendorUUID;
    paymentConfig.eaaSerialNumber = terminalEAASerialNumber;
    paymentConfig.allowGratuity = NO; //Gratuity is an optional feature for the payment
    paymentConfig.transactionType = AcceptTransactionTypeAuthorize;
    //Initializing the basket
    AcceptBasket *basket = [[AcceptBasket alloc] init];
    basket.currencyAsISO4217Code = @"CZK";
    basket.netTaxation = [NSNumber numberWithInt:1] ; //Set to 0 for tax inclusive
    //Note: Basket has the option for setting latitude and longitude, in case the need the location in the payment info
    //basket.lat, basket.lng
    
    //Adding the payment item to the basket
    AcceptBasketItem *basketItem =
    [self addBasketItem:1 //This is the number of items. We could have more than one with the same price
                 amount:[NSDecimalNumber decimalNumberWithString:self.amountTf.text]
                   note:@"Here we can add some description of the payment"
                    tax:0 //value indicating the tax % (note: 7% is indicated by 700; 7 would be 0.07%)
             chargeType:@"NONE"/*there are 4 types of charge: NONE, NORMAL, TIP and SERVICE_CHARGE*/];
    
    [basket.items addObject:basketItem]; //Note that a basket could include many items on it repeating the precious lines for each payment item
    paymentConfig.basket = basket;
    
    //We execute the payment
    [self.accept startPay:paymentConfig completion:completion progress:progress signature:signature signatureVerification:signatureVerification appSelection:appSelection];
}


-(AcceptBasketItem *)addBasketItem:(NSInteger)quantity amount:(NSDecimalNumber *)amount note:(NSString *)note tax:(int)tax chargeType:(NSString*)chargeType
{
    NSLog(@">>> PaymentViewController - addBasketItem");
    
    AcceptBasketItem *basketItem= [[AcceptBasketItem alloc] init];
    basketItem.quantity = quantity;
    NSDecimalNumber *decAmount = amount;
    decAmount = [decAmount decimalNumberByDividingBy:[NSDecimalNumber decimalNumberWithString:@"100"]];
    basketItem.grossPrice =  decAmount;
    basketItem.note = note;
    NSDecimalNumber *decTax = [NSDecimalNumber decimalNumberWithString:[NSString stringWithFormat:@"%d",tax]];
    decTax = [decTax decimalNumberByDividingBy:[NSDecimalNumber decimalNumberWithString:@"10000"]];
    basketItem.taxRate = decTax ;
    if ([chargeType isEqualToString:CHARGE_TYPE_SERVICE])
    {
        basketItem.itemType = ACCEPT_ITEM_CHARGE_TYPE_SERVICE_CHARGE;
    }
    else if ([chargeType isEqualToString:CHARGE_TYPE_TIP])
    {
        basketItem.itemType = ACCEPT_ITEM_CHARGE_TYPE_TIP;
    }
    else
    {
        basketItem.itemType = ACCEPT_ITEM_CHARGE_TYPE_NORMAL;
    }
    return basketItem;
}

-(void)paymentFailure:(NSError *)error transaction:(AcceptTransaction *)transaction
{
    NSLog(@">>> PaymentViewController - paymentFailure");
    
    AcceptPayErrorCode errorCode =  (AcceptPayErrorCode) error.code;
    
    if (self.btTimer)
    {
        [self.btTimer invalidate];
        self.btTimer = nil;
    }
    
    if (error.userInfo)
    {
        NSString *underlyingErrorStr = [[error.userInfo objectForKey:NSUnderlyingErrorKey] localizedDescription] ;
        
        if (!underlyingErrorStr) {
            underlyingErrorStr = [error.userInfo objectForKey:NSLocalizedDescriptionKey];
        }
        NSLog(@"%s %@",__PRETTY_FUNCTION__,underlyingErrorStr);
        
        NSString *errorMessage = @"";
        
        switch (errorCode)
        {
            case AcceptPlugInTimeoutErrorCode:
                errorMessage = @"Device was not plugged-in";
                break;
            case AcceptInitializationErrorCode:
                errorMessage = @"Failed to initialise the device";
                break;
            case AcceptSignatureTimeoutErrorCode:
                errorMessage = @"Timeout: failed to get signature";
                break;
            case AcceptTransactionTerminatedErrorCode:
                errorMessage = @"Payment cancelled";
                break;
            case AcceptTransactionDeclinedErrorCode:
                errorMessage = @"Transaction declined by the terminal";
                break;
            case AcceptLowBatteryLevelErrorCode:
                errorMessage = @"Low battery in device";
                break;
            case AcceptSwipeTimeoutError:
                errorMessage = @"Card was not swiped";
                break;
            case AcceptBadSwipeError:
                errorMessage = @"Card was not swiped";
                break;
            case AcceptNotSupportedCardTypeErrorCode:
                errorMessage = @"The payment card is not supported";
                break;
            case AcceptBlockedCardTypeErrorCode:
                errorMessage = @"Card is blocked";
                break;
            case AcceptDataProcessingErrorCode:
            {
                if ([Utils contains:underlyingErrorStr substring:kTransactionReversalFailed])
                {
                    errorMessage = @"Please manually reverse this payment in History";
                }
                else if ([Utils contains:underlyingErrorStr substring:@"Transaction declined by the terminal"] || [Utils contains:underlyingErrorStr substring:kTransactionReversedByTerminal])
                {
                    errorMessage = @"Transaction declined by the terminal";
                }
                else if ([Utils contains:underlyingErrorStr substring:@"Terminal terminated transaction"])
                {
                    errorMessage = @"Terminal terminated transaction";
                }
                else if ([Utils contains:[underlyingErrorStr uppercaseString] substring:@"PIN entered incorrectly too often"])
                {
                    errorMessage = @"PIN blocked";
                }
                else if ([Utils contains:[underlyingErrorStr uppercaseString] substring:@"PIN"])
                {
                    errorMessage = @"Wrong PIN";
                }
                else if ([Utils contains:[underlyingErrorStr uppercaseString] substring:@"Can't process encrypted data because size is to small"])
                {
                    errorMessage = @"Bad Swipe";
                }
                else
                {
                    errorMessage = [NSString stringWithFormat:@"Data processing error:\n%@",underlyingErrorStr];
                }
            }
                break;
            case AcceptOnlineProcessingErrorCode:
                errorMessage = [NSString stringWithFormat:@"Online data processing error:\n%@",underlyingErrorStr];
                break;
            case AcceptHardwareAccessPermissionErrorCode:
                errorMessage = @"The microphone slot access is disabled";
                break;
            case AcceptTokenExpiredErrorCode:
                errorMessage = @"Session token expired out, login again";
                break;
            case AcceptPayConnectionErrorCode:
                errorMessage = @"Payment connection error";
                break;
            case AcceptTransactionNotApprovedErrorCode:
                if ([Utils contains:[underlyingErrorStr uppercaseString] substring:@"PIN entered incorrectly too often"])
                {
                    errorMessage = @"PIN blocked";
                }
                else if ([Utils contains:[underlyingErrorStr uppercaseString] substring:@"PIN"])
                {
                    errorMessage = @"Wrong PIN";
                }
                else
                {
                    errorMessage = [NSString stringWithFormat:@"Transaction Rejected:\n%@", underlyingErrorStr];
                }
                break;
            case AcceptSignatureRequestErrorCode:
                errorMessage = @"Signature required";
                break;
            case AcceptCantLoadTerminalConfiguration:
                errorMessage = [NSString stringWithFormat:@"Can't load terminal configuration:\n%@", underlyingErrorStr];
                break;
            case AcceptNoDUKPTError:
                errorMessage = @"No DUKPT keys loaded";
                break;
            case AcceptTerminalDamagedError:
                errorMessage = @"The terminal is tampered and cannot be used";
                break;
            case AcceptFailedToStartEMVError:
                errorMessage = @"Failed to send Start EMV Transaction command";
                break;
            case AcceptFailedToSendOfflineEMVError:
                errorMessage = @"Failed to send EMV Offline Transaction command";
                break;
            case AcceptFailedToSendOnlineEMVError:
                errorMessage = @"Failed to send EMV Online Transaction command";
                break;
            case AcceptTerminalNotSetInMerchantError:
                errorMessage = @"Server failed to provide configuration files. Please confirm that your terminal is assigned to your merchant account and/or try again later";
                break;
            case AcceptResponseLostErrorCode:
                errorMessage = @"WARNING: Connection lost, please check in History the transaction status";
                break;
            default:
            {
                if(error.code == AcceptGenericRequestTimeoutErrorCode)
                {
                    errorMessage = @"The server is taking too long to respond";
                }
                else
                {
                    errorMessage = [NSString stringWithFormat:@"Unknown Payment Error:%ld",(long)errorCode];
                }
            }
                break;
        }
        
        NSLog(@"Error message - %@", errorMessage);
        
        [Utils showAlertWithTitle:@"Error" andMessage:errorMessage];
        self.infolbl.text = errorMessage;
        
    }
    
}

-(void)paymentDone:(AcceptTransaction *)transaction
{
    NSLog(@">>> PaymentViewController - paymentDone");
    self.transaction = transaction;
    [self updateInfoLabel:[NSString stringWithFormat:@"Transaction:\n\tStatus:%@\n\tCustom Fields:%@\n\tPE:%@\n\tEE:%@\n\tSubMerchant:%@"
                           ,transaction.state
                           ,transaction.customFields
                           ,[NSString stringWithFormat:@"\n\tpe_job_id:%@\n\tpe_function_id%@",transaction.peJobID, transaction.peFunctionID]
                           ,[NSString stringWithFormat:@"\n\tee_descriptor:%@\n\tee_order_number%@",transaction.eeDescriptor, transaction.eeOrderNumber]
                           ,[NSString stringWithFormat:@"\n\tsubMerchantID:%@\n\tName:%@\n\tStreet:%@\n\tCity:%@\n\tPostal Code:%@\n\tCountry%@",transaction.subMerchant.subMerchantId, transaction.subMerchant.name, transaction.subMerchant.street, transaction.subMerchant.city,transaction.subMerchant.postalCode, transaction.subMerchant.country]]];

    
    if ([transaction.state isEqualToString:@"approved"]|| [transaction.state isEqualToString:@"authorized"]) {
        [Utils showAlertWithTitle:@"Success" andMessage:@"The payment was accepted"];
    }
    else{
        [Utils showAlertWithTitle:@"Failure" andMessage:[NSString stringWithFormat:@"%@:%@",@"The payment was declined",transaction.technicalMessage]];
    }
    
    [self.revertB setEnabled:YES];
    if(self.transaction.capturable){
        [self.captureB setEnabled:YES];
    }
}

-(void)confirmSignature
{
    NSLog(@">>> PaymentViewController - confirmSignature");
    [Utils showAlertWithTitle:@"Confirm" andMessage:@"Please confirm the signature on the terminal"];
    
    
}

-(void)paymentProgress:(AcceptStateUpdate)update
{
    NSLog(@">>> PaymentViewController - paymentProgress");
    //Any progress in the payment flow disable by default the timer
    if (self.btTimer)
    {
        [self.btTimer invalidate];
        self.btTimer = nil;
    }
    
    //But if the progress state goes to initialisation, terminalConfig or waiting for plugin we start the plugin
    if (update == AcceptStateInitialize || update == AcceptStateTerminalConfigOngoing)
    {
        self.btTimer = [NSTimer scheduledTimerWithTimeInterval:kPaymentTimeout target:self selector:@selector(initialisationProgressTimerEnded) userInfo:nil repeats:NO];
    }
    else if (update == AcceptStateWaitingForPlugIn)
    {
        self.btTimer = [NSTimer scheduledTimerWithTimeInterval:kPaymentTimeout target:self selector:@selector(devicePluginProgressTimerEnded) userInfo:nil repeats:NO];
    }
    
    NSString *progressMessage;
    
    switch (update)
    {
        case AcceptStateOnlineProcessingData:
            progressMessage = @"Please Wait - online data processing";
            break;
        case AcceptStateInitialize:
            progressMessage = @"Please Wait - initialisation";
            break;
        case AcceptStateFollowTerminalInstructions:
            progressMessage = @"Follow the instructions on the terminal";
            break;
        case AcceptStateTerminalRestarting:
            progressMessage = @"Terminal restarting, please wait";
            break;
        case AcceptStateTerminalConfigOngoing:
            progressMessage = @"Installing new configuration files";
            break;
        case AcceptStateProcessingData:
            progressMessage = @"Please Wait - data processing";
            break;
        case AcceptStateWaitingForPlugIn:
            progressMessage = @"Please plug-in the device";
            break;
        case AcceptStateWaitingForSwipe:
            progressMessage = @"Please swipe the card";
            break;
        case AcceptStateDamagedChipAndWaitingForSwipe:
            progressMessage = @"Chip is not readable, please swipe the card";
            break;
        case AcceptStateInsertOrSwipeCard:
            progressMessage = @"Please insert or swipe the card";
            break;
        case AcceptStateWaitingForInsertCard:
            progressMessage = @"Please insert the card";
            break;
        case AcceptStateCheckingCard:
            progressMessage = @"Card is being checked, please wait";
            break;
        case AcceptStateRemoveCard:
            progressMessage = @"Please remove the card";
            break;
        case AcceptStateCardRemoved:
        case AcceptStateAmountConfirmed:
            //Do nothing, these are states that updates too fast or do not provide useful information for the user, but are useful for timers udpdates
            break;
        case AcceptStatePINEntered:
            progressMessage = @"Follow the instructions on the terminal";
            break;
        case AcceptStateConfirmAmount:
            progressMessage = @"Please confirm the amount in the terminal";
            break;
        case AcceptStateAskingForPIN:
            progressMessage = @"Please write the PIN";
            break;
        case AcceptStateCorrectPIN:
            progressMessage = @"PIN is correct";
            break;
        case AcceptStatePINEntryLastTry:
            progressMessage = @"Be careful writing your PIN now! This is your last chance before the card is blocked";
            break;
        case AcceptStatePinEntryWrong:
            progressMessage = @"Wrong PIN, please try again";
            break;
        case AcceptStateCardholderSignatureCheck:
            //Do nothing in Demo App, but in a more complex UI, the merchant will need to see the signature in another view for being able to confim when some device (ie Posmate) requires it
            break;
        default:
            progressMessage = [NSString stringWithFormat:@"Unknown Payment Progress state :%ld",(long)update];
            break;
    }
    
    NSLog(@"Progress status - %@", progressMessage);
    dispatch_async(dispatch_get_main_queue(), ^{
        [self updateInfoLabel:progressMessage];
    });
    
}
-(void)updateInfoLabel:(NSString *)text{
    dispatch_async(dispatch_get_main_queue(), ^{
        [self.infolbl setText:text];
    });
}
-(void)initialisationProgressTimerEnded
{
    NSLog(@">>> PaymentViewController - initialisationProgressTimerEnded");
    [self.btTimer invalidate];
    self.btTimer = nil;
    
    [Utils showAlertWithTitle:@"Error" andMessage:@"Failed to initialise the device"];
    
    [self cancelPayment:nil];
}

-(void)devicePluginProgressTimerEnded
{
    NSLog(@">>> PaymentViewController - devicePluginProgressTimerEnded");
    [self.btTimer invalidate];
    self.btTimer = nil;
    
    [Utils showAlertWithTitle:@"Error" andMessage:@"Device was not plugged-in"];
    
    [self cancelPayment:nil];
}

-(IBAction)cancelPayment:(id)sender
{
    NSLog(@">>> PaymentViewController - cancelPayment");
    [self.accept cancelPay];
}


-(void)requestSignature:(AcceptSignatureRequest *  )signatureRequest
{
    NSLog(@">>> PaymentViewController - requestSignature");
    //NOTE: Here is expected to open a view for manually inserting a signature. Demo app fakes the proccess sending a PNG file with it. It is also recommendable that the picture file does not excceed 4-6 kb in size
    NSURL *imgPath = [[NSBundle mainBundle] URLForResource:@"signature_sample" withExtension:@"png"];
    NSString*stringPath = [imgPath absoluteString];
    NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:stringPath]];
    UIImage *signatureImage = [[UIImage alloc] initWithData:data];
    signatureRequest.signatureCallback(signatureImage, nil);
}

-(void)requestAppSelection:(AcceptAppSelectionRequest * )appSelectionRequest
{
    NSLog(@">>> PaymentViewController - requestAppSelection");
    appSelectionRequest.appSelectionCallback(0, nil);
    //NOTE: appSelectionRequest retrieves the applications available in the app in case there are more than one, and a UI should be in place here to select the one to be used in that case
}

#pragma mark Printing Methods

-(IBAction)onPrint:(id)sender
{
    NSLog(@">>> PaymentViewController - requestAppSelection");
    __weak PaymentViewController *weakSelf = self;
    
    void (^completion)(BOOL, NSError*) = ^(BOOL success, NSError *error)
    {
        if (error || !success) {
            [weakSelf printFailure:error];
            [weakSelf updateInfoLabel:@"Printing failed, please check the printer"];
        }
        else
        {
            [weakSelf printSuccess];
            [weakSelf updateInfoLabel:@"Printing successful"];
        }
        
    };
    void(^progress)(AcceptPrinterStateUpdate) = ^(AcceptPrinterStateUpdate update){
        [weakSelf printProgress:update];
    };
    
    AcceptPrinterConfig *printerConfig = [[AcceptPrinterConfig alloc] init];
    printerConfig.vendorUUID = [[Utils sharedInstance] getSelectedPrinterVendor];
    printerConfig.printerUUID = [[Utils sharedInstance] getSelectedPrinter];
    [self updateInfoLabel:@"Printing started"];
    
    if ([[[Utils sharedInstance] getSelectedPrinterVendor] isEqualToString: @"MPOPAcceptExtension"])
    {
        UIImage *imgReceipt = [UIImage imageNamed:@"fakereceipt.png"];
        printerConfig.receiptImage = imgReceipt;
    }
    else
    {
        printerConfig.receipt = [self getAcceptReceipt];
    }
    
    [self.accept startPrint:printerConfig completion:completion progress:progress];
    
}

-(void)printProgress:(AcceptPrinterStateUpdate)update
{
    NSLog(@">>> PaymentViewController - printProgress");
    NSString *message = @"";
    switch (update)
    {
        case AcceptPrinterStateInitialize:
            message = @"Please Wait - printer initialisation";
            break;
        case AcceptPrinterStateConnecting:
            message = @"Connecting to printer";
            break;
        case AcceptPrinterStateConnected:
            message = @"Printer connected";
            break;
        case AcceptPrinterStatePrint:
            message = @"Printing ...";
            break;
        case AcceptPrinterStateFinish:
            message = @"Printing done";
            break;
        default:
            message = [NSString stringWithFormat:@"Unknown Print Progress state :%ld",(long)update];
            break;
    }
    
    [self updateInfoLabel:message];
}


-(void)printSuccess
{
    NSLog(@">>> PaymentViewController - printSuccess");
}

-(void)printFailure:(NSError *)error
{
    NSLog(@">>> PaymentViewController - printFailure");
    NSString *errorMessage = @"";
    AcceptPrintErrorCode errorCode =  (AcceptPrintErrorCode) error.code;
    
    if (error.userInfo)
    {
        switch (errorCode)
        {
            case AcceptPrinterTimeoutErrorCode:
                errorMessage = @"Printer communication timeout";
                break;
            case AcceptPrinterInitializationErrorCode:
                errorMessage = @"Printer failed to initialise";
                break;
            case AcceptPrinterLowBatteryLevelErrorCode:
                errorMessage = @"Printer battery low";
                break;
            case AcceptPrinterConnectionErrorCode:
                errorMessage = @"Printer connection failure";
                break;
            case AcceptPrinterNotConnectedErrorCode:
                errorMessage = @"Printer not connected";
                break;
            case AcceptPrinterOperationErrorCode:
                errorMessage = @"Printer operation failure";
                break;
            case AcceptPrinterUnsupportedDeviceErrorCode:
                errorMessage = @"Printer is not supported";
                break;
            default:
            {
                errorMessage = [NSString stringWithFormat:@"Unknown Print Error:%ld",(long)errorCode];
                
            }
                break;
        }
        
        [Utils showAlertWithTitle:@"Printer error" andMessage:errorMessage];
    }
}

-(AcceptReceipt *)getAcceptReceipt
{
    NSLog(@">>> PaymentViewController - getAcceptReceipt");
    AcceptReceipt *receipt = [[AcceptReceipt alloc] init];
    receipt.header = @"Customer Receipt";
    receipt.merchantName = @"Jackie Chan";
    receipt.merchantAddressLine1 = @"Elm Street";
    receipt.merchantAddressLine2 = @"Springfield";
    receipt.merchantAddressZipCode = @"90210";
    receipt.merchantAddressCityAndCountry = @"'Merica";
    receipt.merchantID = @"4321-4321-4321";
    receipt.merchantIDHeader = @"MID:";
    receipt.aidHeader = @"AID:";
    receipt.aid = @"987654321";
    receipt.merchantPhone = @"902902902";
    receipt.localisedReceiptDateHeader = @"Date";
    receipt.localisedPaymentDateHeader = @"Payment Date";
    receipt.localisedReceiptTimeHeader = @"Time";
    receipt.receiptDate = @"01/01/2018";
    receipt.receiptTime = @"15:45:22";
    receipt.localisedReceiptIDHeader = @"Receipt #";
    receipt.localisedReceiptNumberHeader = @"Receipt number";
    receipt.receiptID = @"12345";
    receipt.localisedCardTypeHeader = @"Card Type";
    receipt.cardType = @"Acme";
    receipt.transactionTypeString = @"Credit";
    receipt.localisedCardNumberHeader = @"Card Number";
    receipt.cardNumber = @"***********5678";
    receipt.cardHolder = @"John Smith";
    receipt.localisedCardHolderHeader = @"Cardholder Name";
    receipt.localisedExpiryDateHeader = @"Expiry Date";
    receipt.expiryDate = @"12/22";
    receipt.localisedTerminalIDHeader = @"Terminal ID";
    receipt.terminalID = @"777";
    receipt.localisedApprovalCodeHeader = @"Approval Code";
    receipt.approvalCode = @"11";
    receipt.localisedAmountHeader = @"Total";
    receipt.amount = @"1,000,000";
    receipt.localisedTransactionStatusHeader = @"Transaction Status";
    receipt.transactionStatus = @"Accepted";
    receipt.footer = @"Payment issued by Acme Inc.";
    receipt.localisedPaymentDetailsHeader = @"Payment details";
    receipt.paymentItems = [NSString stringWithFormat:@"%@\n%@ * %@\t%@\t%@\n"
                            , @"Item Description"
                            ,@"1"
                            ,@"999"
                            ,@"1,000"
                            ,@"1,000,000"];
    
    return receipt;
}

#pragma mark - Revert (Actions on) a Payment

-(IBAction)onTapRevert:(id)sender
{
    NSLog(@">>> PaymentViewController - onTapRevert");
    __weak PaymentViewController *weakSelf = self;
    void (^completionBlock)(AcceptTransaction*, NSError*) = ^(AcceptTransaction *transaction, NSError *error)
    {
        NSString *message, *title;
        if (transaction && transaction.uniqueId.length > 0)
        {
            if (!transaction.reversible)
            {
                title = @"Success";
                message = NSLocalizedString(@"Transaction reversed successfully", "Transaction reversed successfully");
                weakSelf.transaction = nil;
                [weakSelf.revertB setEnabled:NO];
            }
            else
            {
                title = @"Error";
                message = @"Online data processing error";
            }
        }
        else
        {
            title = @"Error";
            message = @"Online data processing error";
        }
        
        [Utils showAlertWithTitle:title andMessage:message];
    };
    
    if (self.transaction && self.transaction.uniqueId.length >0 && self.transaction.reversible)
    {
        [self.accept requestOperationOnPaymentWithID:self.transaction.uniqueId
                                      andAccessToken:[[Utils sharedInstance] accessTokenObject].accessToken
                                              config:[[Utils sharedInstance] backendConfig]
                                           operation:AcceptOperationOnPaymentReverse
                             paymentUpdateParameters:nil //this is used for sending receipt through email, phone number, etc.
                                          completion:completionBlock];
    }
    else
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"No transaction to reverse"];
    }
}

-(void)updateTerminalFirmware
{
    __weak PaymentViewController *weakSelf = self;
    NSString *iSelectedVendor = [[Utils sharedInstance] getSelectedVendor];
    
    AcceptTerminalVendor *currentVendor;
    for(AcceptTerminalVendor *vendor in self.arrVendors)
    {
        if ([vendor.uuid isEqualToString:iSelectedVendor])
        {
            currentVendor = vendor;
        }
    }
    if ([iSelectedVendor rangeOfString:AcceptSpireVendorUUID].location == NSNotFound)
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"Selected terminal does not support firmware updates."];
        return ;
    }
    
    NSString *iSelectedVendorTerminalDisplayName = [[Utils sharedInstance] getSelectedTerminal];
    __block id iSelectedVendorUUID = [[AcceptUtils sharedInstance] vendorIDForName:iSelectedVendorTerminalDisplayName andUUID:[[Utils sharedInstance] getSelectedVendor]];
    
    [self.accept discoverTerminalsForVendor:iSelectedVendorUUID completion:^(NSArray *discoveredTerminals, NSError *error) {
        
        __block AcceptTerminal *terminal = nil;
        
        for (AcceptTerminal *term in discoveredTerminals) {
            if ([term.displayName isEqualToString: iSelectedVendorTerminalDisplayName]) {
                terminal = term;
                break;
            }
        }
        
        AcceptPaymentConfig* paymentConfig = [[AcceptPaymentConfig alloc] init];
        paymentConfig.backendConfig = [Utils sharedInstance].backendConfig;
        paymentConfig.accessToken = [Utils sharedInstance].accessTokenObject.accessToken;
        paymentConfig.vendorUUID = iSelectedVendorUUID;
        paymentConfig.eaaSerialNumber = terminal.eaaSerialNumber;
        paymentConfig.allowGratuity = NO; //Gratuity is an optional feature for the payment
        
        
        [weakSelf.accept queryFirmware:paymentConfig completion:^(BOOL updateRequired, AcceptTerminalFirmware *firmware, NSError *error) {
            
            void (^completionAlertUI)(NSInteger, NSError*) = ^(NSInteger alertCode, NSError *error)
            {
                [[NSOperationQueue mainQueue] addOperationWithBlock:^
                 {
                     //An error of kind "Terminal cancelled file download" could happen because your terminal has a wrong image, or the firmware is badly named in backend (i.e. a production labelled as test firmware or viceversa). If problem persist and is reproducible in other devices, please ask terminal support for help.
                     [Utils showAlertWithTitle:@"Operation" andMessage:[NSString stringWithFormat: @"Alert code: %ld and error %@", (long)alertCode, error.description]];
                 }];
            };
            
            void (^progress)(AcceptConfigFilesProgress) = ^(AcceptConfigFilesProgress progress)
            {
                [self updateInfoLabel:[NSString stringWithFormat:@"Progress updating terminal, code: %ld", (long)progress]];
            };
            
            if (error)
            {
                [[NSOperationQueue mainQueue] addOperationWithBlock:^
                 {
                     [Utils showAlertWithTitle:@"Error" andMessage:[NSString stringWithFormat: @"Error %@", error.description]];
                 }];
            }
            else if(!updateRequired)
            {
                [[NSOperationQueue mainQueue] addOperationWithBlock:^
                 {
                     [Utils showAlertWithTitle:@"Info" andMessage:@"No firmware update required"];
                 }];
                
            }
            else //update requires means the newest version on backend is different from your current.
            {
                [weakSelf.accept updateTerminalFirmware:terminal
                                                 vendor:currentVendor
                                                  token:[[Utils sharedInstance] accessTokenObject].accessToken
                                                 config:[[Utils sharedInstance] backendConfig]
                                               progress:progress completion:completionAlertUI];
                
                //We reset the config files log in the iOS device as firmware update cleans it up on the terminal as well
                NSMutableDictionary *terminalVersionDict = [[NSMutableDictionary alloc] init];
                [terminalVersionDict setObject:@"0" forKey:terminal.displayName];
                NSDictionary *dictTerminal = [NSDictionary dictionaryWithObjects:[NSArray arrayWithObject:terminalVersionDict] forKeys:[NSArray arrayWithObject:iSelectedVendorUUID]];
                [[Utils sharedInstance] setTerminalConfigurationUploads:dictTerminal];
            }
        }];
    }];
}

-(IBAction)updateFirmwareButtonPressed:(id)sender
{
    //WARNING
    //Note that updating your terminal's firmware is a critical action. Do not switch off your terminal during this action and try to keep the app in foreground (screensaver off, etc)
    UIActionSheet *actionSheet = [[UIActionSheet alloc] initWithTitle:@"Do you want to update firmware of the terminal?"
                                                             delegate:self
                                                    cancelButtonTitle:@"NO"
                                               destructiveButtonTitle:nil
                                                    otherButtonTitles:@"YES", nil];
    actionSheet.tag = ACTION_SHEET_FIRMWARE;
    [actionSheet showInView:self.view];
}

#pragma mark mPOP Methods

-(IBAction)onOpenDrawer:(id)sender
{
    NSLog(@">>> PaymentViewController - onOpenDrawer");
    __weak PaymentViewController *weakSelf = self;
    
    if (![[[Utils sharedInstance] getSelectedPrinterVendor] isEqualToString: @"MPOPAcceptExtension"])
    {
        [weakSelf updateInfoLabel:@"Current printer disconnected or does not have cash drawer"];
        return;
    }
    
    void (^completion)(BOOL, NSError*) = ^(BOOL success, NSError *error)
    {
        if (error || !success) {
            [weakSelf printFailure:error];
            [weakSelf updateInfoLabel:@"Opening drawer failed, please check the drawer"];
        }
        else
        {
            [weakSelf printSuccess];
            [weakSelf updateInfoLabel:@"Drawer was opened"];
        }
        
    };
    
    AcceptPrinterConfig *printerConfig = [[AcceptPrinterConfig alloc] init];
    printerConfig.vendorUUID = [[Utils sharedInstance] getSelectedPrinterVendor];
    printerConfig.printerUUID = [[Utils sharedInstance] getSelectedPrinter];
    printerConfig.receipt = nil;//
    [self updateInfoLabel:@"Trying to open the drawer"];
    
    [self.accept openCashDrawer:printerConfig completion:completion];
}

#pragma mark Printing Methods

-(IBAction)onBarcodeReader:(id)sender
{
    NSLog(@">>> PaymentViewController - onBarcodeReader");
    __weak PaymentViewController *weakSelf = self;
    
    void (^barcodeDataReceived)(NSData*) = ^(NSData* data)
    {
        NSLog(@"Barcode Data received! %@", data);
        [weakSelf updateInfoLabel:@"Barcode data received!"];
    };
    
    void (^completion)(BOOL, NSError*) = ^(BOOL success, NSError *error)
    {
        
    };
    
    AcceptPrinterConfig *printerConfig = [[AcceptPrinterConfig alloc] init];
    printerConfig.vendorUUID = [[Utils sharedInstance] getSelectedPrinterVendor];
    printerConfig.printerUUID = [[Utils sharedInstance] getSelectedPrinter];
    
    [self.accept connectBarcodeScanner:printerConfig completion:completion andDataReceived:barcodeDataReceived];
}
-(void)startAlipayScanner{
    
    if (![[[[UIApplication sharedApplication ] windows] firstObject] viewWithTag:2322]) {
        BarCodeScannerIOS *barcodeScanner = [[BarCodeScannerIOS alloc] initWithView:self.view];
        barcodeScanner.tag = 2322;
        
        barcodeScanner.delegate = self;
        
    }
}

-(void)finishedBarcodeScan:(NSString *)barcodeData canceled:(BOOL)canceled{
    
    if (barcodeData) {
        __weak PaymentViewController *weakSelf = self;
        
        void(^progress)(AcceptStateUpdate) = ^(AcceptStateUpdate update)
        {
            [weakSelf paymentProgress:update];
        };
        
        void (^completion)(AcceptTransaction*, NSError*) = ^(AcceptTransaction *transaction, NSError *error)
        {
            if (error || !transaction)
            {
                [weakSelf paymentFailure:error transaction:transaction];
            }
            else
            {
                [weakSelf performSelectorOnMainThread:@selector(paymentDone:) withObject:transaction waitUntilDone:NO];
            }
        };
        
        //Preparing payment configuration
        AcceptPaymentConfig* paymentConfig = [[AcceptPaymentConfig alloc] init];
        paymentConfig.backendConfig = [Utils sharedInstance].backendConfig;
        paymentConfig.accessToken = [Utils sharedInstance].accessTokenObject.accessToken;
        paymentConfig.vendorUUID = [NSString string];
        paymentConfig.eaaSerialNumber = [NSString string];
        paymentConfig.allowGratuity = NO; //Gratuity is an optional feature for the payment
        // paymentConfig.alipayConsumerId = @"286006334965846411" ; //numeric data read from the Alipay barcode
        paymentConfig.alipayConsumerId = barcodeData; // real bar code data
        //Initializing the basket
        AcceptBasket *basket = [[AcceptBasket alloc] init];
        basket.currencyAsISO4217Code = @"USD"; //alipay gateway is setup only for USD
        basket.netTaxation = [NSNumber numberWithInt:1] ; //Set to 0 for tax inclusive
        //Note: Basket has the option for setting latitude and longitude, in case the need the location in the payment info
        //basket.lat, basket.lng
        
        //Adding the payment item to the basket
        AcceptBasketItem *basketItem =
        [self addBasketItem:1 //This is the number of items. We could have more than one with the same price
                     amount:[NSDecimalNumber decimalNumberWithString:self.amountTf.text]
                       note:@"Here we can add some description of the payment"
                        tax:0 //value indicating the tax % (note: 7% is indicated by 700; 7 would be 0.07%)
                 chargeType:@"NONE"/*there are 4 types of charge: NONE, NORMAL, TIP and SERVICE_CHARGE*/];
        
        [basket.items addObject:basketItem]; //Note that a basket could include many items on it repeating the precious lines for each payment item
        
        
        //add custom fields if required
        basket.customFields = @{@"myCustomOrderID":@"customOrderID"};
        
        //add sub merchant data if required
        AcceptSubMerchant *subMerchant = [AcceptSubMerchant new];
        subMerchant.subMerchantId = @"1234567889";
        subMerchant.name = @"MySubMerchant";
        subMerchant.country = @"Germany";
        subMerchant.state = @"";
        subMerchant.city =@"Munich";
        subMerchant.street = @"1 Circular";
        subMerchant.postalCode = @"12345";
        basket.subMerchant = subMerchant;
        
        //add Payment Engine details:
        basket.peFunctionID = @"MyPEFunctionID";
        basket.peJobID = @"MyPEJobID";
        
        //add Elasti Engine details:
        basket.eeDescriptor = @"MyEEDescriptor";
        basket.eeOrderNumber = @"MyEEOrderNumber";
        
        paymentConfig.basket = basket;
        
        [self.accept startAlipayPayment:paymentConfig completion:completion progress:progress];
    }
}


@end

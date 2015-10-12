//
//  Utils.m
//  Accept Demo
//
//  Created by Fortes, Francisco on 10/27/14.
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import "Utils.h"
#import <sys/socket.h>
#import <netinet/in.h>
#import <SystemConfiguration/SystemConfiguration.h>

@interface Utils()
    @property(nonatomic) BOOL paymentTimerOngoing;
    @property(nonatomic) BOOL waitingForPaymentTimer;
    @property (strong, nonatomic) NSTimer *tokenTimer;
@end

@implementation Utils

static Utils *sharedInstance = nil;

+ (Utils *)sharedInstance {
    if (nil != sharedInstance) {
        return sharedInstance;
    }
    
    static dispatch_once_t pred;
    dispatch_once(&pred, ^{
        sharedInstance = [[Utils alloc] init];
    });
    
    return sharedInstance;
}

-(id)init
{
    self = [super init];
    self.paymentTimerOngoing = NO;
    self.waitingForPaymentTimer = NO;
    self.dateFormatter = [[NSDateFormatter alloc] init];
    [self.dateFormatter setLocale:[[NSLocale alloc] initWithLocaleIdentifier:@"en_UK"]];
    [self.dateFormatter setDateFormat:kDateFormatType3];
    NSTimeZone *zone=[NSTimeZone defaultTimeZone];
    [self.dateFormatter setTimeZone:zone];
    self.backendConfig = [AcceptDataServiceConfig new];

    //EncryptedResources/accept.conf contains default DEV backend config
    //If you use default EncryptedResources/accept.conf there is no need to supply custom backendConfig
    self.backendConfig.url = @"https://test-mpos.wirecard.com/";//@"https://yourBackendURL.com/"; //Note the slash for closing "/"
    self.backendConfig.clientId = @"716220948d75bcec137f2ccaa311f2b83914bfc783ed19ef7253ecc93d2e93fe";// @"yourCliendID";
    self.backendConfig.clientSecret = @"f12dbd75bf12376da8757e00aae877d86df5cb3734fba24d9e49a3f1190bedf7"; // @"yourSecretID";
    self.accept = [[Accept alloc] init];
    
    return self;
}

+(BOOL)checkConnectivity{
    
    if (![Utils hasConnectivity])
    {
        [Utils showAlertWithTitle:@"Connection unavailable" andMessage:@"Please check your internet connection"];
        
        return YES;
    }
    
    return YES;
}

+(BOOL)hasConnectivity
{
    struct sockaddr_in zeroAddress;
    bzero(&zeroAddress, sizeof(zeroAddress));
    zeroAddress.sin_len = sizeof(zeroAddress);
    zeroAddress.sin_family = AF_INET;
    
    SCNetworkReachabilityRef reachability = SCNetworkReachabilityCreateWithAddress(kCFAllocatorDefault, (const struct sockaddr*)&zeroAddress);
    if(reachability != NULL) {
        //NetworkStatus retVal = NotReachable;
        SCNetworkReachabilityFlags flags;
        if (SCNetworkReachabilityGetFlags(reachability, &flags)) {
            if ((flags & kSCNetworkReachabilityFlagsReachable) == 0)
            {
                // if target host is not reachable
                return NO;
            }
            
            if ((flags & kSCNetworkReachabilityFlagsConnectionRequired) == 0)
            {
                // if target host is reachable and no connection is required
                //  then we'll assume (for now) that your on Wi-Fi
                return YES;
            }
            
            
            if ((((flags & kSCNetworkReachabilityFlagsConnectionOnDemand ) != 0) ||
                 (flags & kSCNetworkReachabilityFlagsConnectionOnTraffic) != 0))
            {
                // ... and the connection is on-demand (or on-traffic) if the
                //     calling application is using the CFSocketStream or higher APIs
                
                if ((flags & kSCNetworkReachabilityFlagsInterventionRequired) == 0)
                {
                    // ... and no [user] intervention is needed
                    return YES;
                }
            }
            
            if ((flags & kSCNetworkReachabilityFlagsIsWWAN) == kSCNetworkReachabilityFlagsIsWWAN)
            {
                // ... but WWAN connections are OK if the calling application
                //     is using the CFNetwork (CFSocketStream?) APIs.
                return YES;
            }
        }
    }
    
    return NO;
}

-(void)setVendorConfigurationVersion:(NSDictionary *)dict
{
    [[NSUserDefaults standardUserDefaults] setObject:dict forKey:@"vendorConfigurationVersion"];
}

-(NSString *)getVendorConfigurationVersion:(NSString *)vendorUUID{
    NSDictionary *dictVendorVersion = [[NSUserDefaults standardUserDefaults] objectForKey:@"vendorConfigurationVersion"];
    
    return [dictVendorVersion valueForKey:vendorUUID];
}

-(void)setSelectedVendor:(NSString *)value
{
    [[NSUserDefaults standardUserDefaults] setObject:value forKey:@"selectedVendor"];
}

-(NSString*) getSelectedVendor
{
    id defVendor = [[NSUserDefaults standardUserDefaults] objectForKey:@"selectedVendor"];
    
    if (defVendor)
    {
        return defVendor;
    }
    
    return [NSString string];
}

-(NSString*) getSelectedPrinterVendor
{
    id defVendor = [[NSUserDefaults standardUserDefaults] objectForKey:@"selectedPrinterVendor"];
    
    if (defVendor)
    {
        return defVendor;
    }
    
    return [NSString string];
}

-(NSString*) getSelectedPrinter
{
    id defPrinter = [[NSUserDefaults standardUserDefaults] objectForKey:@"selectedPrinter"];
    
    if (defPrinter)
    {
        return defPrinter;
    }
    else {
        [self setPrinterDefaultValue:PRINTER_DEFAULT_VALUE];
        [self setPrinterVendorDefaultValue:PRINTER_DEFAULT_VALUE];
        defPrinter = PRINTER_DEFAULT_VALUE;
    }
    
    return defPrinter;
}

-(void)setPrinterDefaultValue:(NSString *)value
{
    [[NSUserDefaults standardUserDefaults] setObject:value forKey:@"selectedPrinter"];
}

-(void)setPrinterVendorDefaultValue:(NSString *)value
{
    [[NSUserDefaults standardUserDefaults] setObject:value forKey:@"selectedPrinterVendor"];
}

-(void)setSelectedTerminal:(NSString *)value
{
    [[NSUserDefaults standardUserDefaults] setObject:value forKey:@"selectedTerminal"];
}

-(NSLocale*)getMerchantsCurrencyLocale
{
    id defLocale = [[NSUserDefaults standardUserDefaults] objectForKey:@"defaultCurrencyLocaleIdentifier"];
    
    if (!defLocale)
    {
        defLocale = LOCALE_DEFAULT_VALUE;
    }
    
    NSLocale *lcl = [[NSLocale alloc] initWithLocaleIdentifier:defLocale];
    
    return lcl;
}

-(NSString*)getCurrencyCodeDefaultValue
{
    id defValue = [[NSUserDefaults standardUserDefaults] objectForKey:@"currencyCode"];
    
    if (defValue){
        return defValue;
    }
    
    return CURRENCY_CODE_DEFAULT_VALUE;
}

-(NSString*)getCurrencySymbolDefaultValue
{
    id defValue = [[NSUserDefaults standardUserDefaults] objectForKey:@"currencySymbol"];
    
    if (defValue){
        return defValue;
    }
    
    return CURRENCY_SYMBOL_DEFAULT_VALUE;
}

-(NSString*) getSelectedTerminal
{
    id defTerminal = [[NSUserDefaults standardUserDefaults] objectForKey:@"selectedTerminal"];
    
    if (defTerminal)
    {
        return defTerminal;
    }
    
    return [NSString string];
}

-(NSDictionary*) getTerminalConfigurationUploads
{
    id defTerminalConfigurationUploads = [[NSUserDefaults standardUserDefaults] objectForKey:@"terminalConfigurationUploads"];
    
    if (defTerminalConfigurationUploads)
    {
        return defTerminalConfigurationUploads;
    }
    
    return nil;
}
-(NSString*) getVendorTerminalConfigurationVersion:(NSString *)vendorUUID terminalUUID:(NSString *)terminalUUID
{
    NSDictionary *dictTerminalsConfig = [self getTerminalConfigurationUploads];
    NSDictionary *dictVendorTerminals = [dictTerminalsConfig valueForKey:vendorUUID];
    NSString *dictTerminalConfigVersion = [dictVendorTerminals valueForKey:terminalUUID];
    return dictTerminalConfigVersion;
}

-(void)setTerminalConfigurationUploads:(NSDictionary *)terminalConfigVersion
{
    NSMutableDictionary *dictExistingTerminalConfig = [NSMutableDictionary dictionaryWithDictionary:[self getTerminalConfigurationUploads]];
    
    if (!dictExistingTerminalConfig)
    {
        dictExistingTerminalConfig = [[NSMutableDictionary alloc] init];
    }
    
    for (NSString *vendorKey in terminalConfigVersion)
    {
        NSMutableDictionary *dictExistingVendorTerminals =[NSMutableDictionary dictionaryWithDictionary:[dictExistingTerminalConfig valueForKey:vendorKey]];
        
        if (!dictExistingVendorTerminals)
        {
            dictExistingVendorTerminals=[[NSMutableDictionary alloc] init];
        }
        
        NSDictionary *dictTerminalConfigVersion = [terminalConfigVersion valueForKey:vendorKey];
        
        for (NSString *terminalKey in dictTerminalConfigVersion)
        {
            [dictExistingVendorTerminals setValue:[dictTerminalConfigVersion valueForKey:terminalKey] forKey:terminalKey];
        }
        
        [dictExistingTerminalConfig setValue:dictExistingVendorTerminals forKey:vendorKey];
    }
    
    [[NSUserDefaults standardUserDefaults] setObject:dictExistingTerminalConfig forKey:@"terminalConfigurationUploads"];
}


-(void)setTaxAmountsForMerchant:(NSArray *)arrTaxes
{
    if (arrTaxes.count > 0)
    {
        NSMutableArray *arrTmpNew = [[NSMutableArray alloc] init];
        
        for (id taxItem in arrTaxes)
        {
            NSDecimalNumber *decTax  = [NSDecimalNumber decimalNumberWithString: [NSString stringWithFormat:@"%@", taxItem]];
            decTax = [decTax decimalNumberByMultiplyingBy:[NSDecimalNumber decimalNumberWithString:@"10000"]];
            [arrTmpNew addObject:[decTax stringValue]];
        }
        
        if ([arrTmpNew indexOfObject:@"0"] == NSNotFound)
        { //add no tax option
            [arrTmpNew addObject:@"0"];
        }
        
        NSMutableArray *arrTmpSorted = [[NSMutableArray alloc] initWithArray:
                                        [arrTmpNew sortedArrayUsingComparator:^NSComparisonResult(id obj1, id obj2) {
            if ([obj1 intValue] < [obj2 intValue]) return NSOrderedAscending;
            else return NSOrderedDescending;
        }]];
        
        self.taxAmounts = arrTmpSorted;
    }
    else
    {
        self.taxAmounts = nil;
    }
}

-(void)setCurrenciesForMerchant:(NSArray *)arrCurrencies
{
    if (arrCurrencies.count > 0)
    {
        NSMutableArray *arrTmpNew = [[NSMutableArray alloc] init];
        
        for (id currencyItem in arrCurrencies)
        {
            [arrTmpNew addObject:currencyItem];
        }
        
        NSSortDescriptor* sortOrder = [NSSortDescriptor sortDescriptorWithKey: @"self" ascending: YES];
        NSArray *arrTmpSorted = [arrTmpNew sortedArrayUsingDescriptors: [NSArray arrayWithObject: sortOrder]];
        
        self.currencies = arrTmpSorted;
    }
    else
    {
        self.currencies = nil;
    }
}

-(void)setCountryCurrencyDefaultValue:(NSString *)pCurrencyLocale
{
    [[NSUserDefaults standardUserDefaults] setObject:pCurrencyLocale forKey:@"defaultCurrencyLocaleIdentifier"];
    
    NSLocale *lcl = [[NSLocale alloc] initWithLocaleIdentifier:pCurrencyLocale];
    [self.currencyFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    [self.currencyFormatter setLocale:lcl];
    [self.numberFormatter setLocale:lcl];
    
    [[NSUserDefaults standardUserDefaults] setObject:[self.currencyFormatter currencyCode] forKey:@"currency"];
    [[NSUserDefaults standardUserDefaults] setObject:[self.currencyFormatter currencySymbol] forKey:@"currencySymbol"];
}


-(void)setCurrencyCodeDefaultValue:(NSString *)pValue
{
    [[NSUserDefaults standardUserDefaults] setObject:pValue forKey:@"currencyCode"];
    NSNumberFormatter *numFormatter = [[NSNumberFormatter alloc] init];
    
    NSLocale *lcl = [self getMerchantsCurrencyLocale];
    [self.currencyFormatter setLocale:lcl];
    [self.numberFormatter setLocale:lcl];
    [self.currencyFormatter setCurrencyCode:pValue];
    [self.currencyFormatter setMaximumFractionDigits:2];
    [self.currencyFormatter setMinimumFractionDigits:2];
    [self.currencyFormatter setPaddingCharacter:@""];
    [self.currencyFormatter setGroupingSeparator:@""];
    [self.currencyFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    
    [numFormatter setLocale:lcl];
    [numFormatter setCurrencyCode:pValue];
    [numFormatter setMaximumFractionDigits:2];
    [numFormatter setMinimumFractionDigits:2];
    [numFormatter setPaddingCharacter:@""];
    [numFormatter setGroupingSeparator:@""];
    [numFormatter setNumberStyle:NSNumberFormatterCurrencyStyle];
    
    
    [[NSUserDefaults standardUserDefaults] setObject:[numFormatter currencyCode] forKey:@"currencyCode"];
    
    NSString *strNum = [numFormatter stringFromNumber:[NSNumber numberWithInt:0]];
    NSString *strSymbol = [[[[strNum stringByReplacingOccurrencesOfString:@"0" withString:@""]
                             stringByReplacingOccurrencesOfString:@"." withString:@""]
                            stringByReplacingOccurrencesOfString:@"," withString:@""]
                           stringByReplacingOccurrencesOfString:@" " withString:@""];
    
    if (strSymbol.length == 0) {
        strSymbol = numFormatter.currencySymbol;
    }
    
    [[NSUserDefaults standardUserDefaults] setObject:[strSymbol stringByReplacingOccurrencesOfString:@" " withString:@""] forKey:@"currencySymbol"];
}

-(void)setLocaleDefaultValue:(NSString *)pDefaultLocale
{
    [[NSUserDefaults standardUserDefaults] setObject:pDefaultLocale forKey:@"defaultLocaleIdentifier"];
    
}

-(BOOL)isPaymentTimerOngoing
{
    return self.paymentTimerOngoing;
}

-(void)startPaymentTimerWith:(NSTimeInterval)seconds
{
    if (self.paymentTimerOngoing)  return;
    self.paymentTimerOngoing = YES;
    [NSTimer scheduledTimerWithTimeInterval:seconds
                                     target:self
                                   selector:@selector(paymentTimerFinished)
                                   userInfo:nil
                                    repeats:NO];
}

-(void) paymentTimerFinished
{
    self.paymentTimerOngoing = NO;
    if (self.waitingForPaymentTimer)
    {
        self.waitingForPaymentTimer = NO;
        [[NSNotificationCenter defaultCenter] postNotificationName:kPaymentTimerNotificationName object:nil];
    }
}

+(BOOL)contains:(NSString *)string substring:(NSString*)substring
{
    if  (!string || !substring) return NO;
    NSError *error = NULL;
    NSRegularExpression *regex = [NSRegularExpression regularExpressionWithPattern:substring options:NSRegularExpressionCaseInsensitive error:&error];
    NSUInteger numberOfMatches = [regex numberOfMatchesInString:string options:0 range:NSMakeRange(0, [string length])];
    return numberOfMatches > 0;
}

+(void)showAlertWithTitle:(NSString*)title andMessage:(NSString*)text
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:title
                                                    message:text
                                                   delegate:nil
                                          cancelButtonTitle:nil
                                          otherButtonTitles:@"OK",nil];
    alert.delegate = nil;
    [alert show];
}

-(void) startTokenTimer
{
    self.tokenTimer = [NSTimer scheduledTimerWithTimeInterval:kTokenTimer target:self selector:@selector(tokenTimerDidExpire) userInfo:nil repeats:YES];
}

-(void) tokenTimerDidExpire
{
    [self.tokenTimer invalidate];
    [[NSNotificationCenter defaultCenter] postNotificationName:kTokenTimerNotificationName object:nil];
}

-(BOOL) tokenExpired
{
    self.tokenIsValid = NO;
    return ![self.tokenTimer isValid];
}

-(NSString *)getStringFromDate:(NSDate *)date withFormat:(NSString *)format
{
    NSString *oldFormat = self.dateFormatter.dateFormat;
    [self.dateFormatter setDateFormat:format];
    NSString *dateString = [self.dateFormatter stringFromDate:date];
    [self.dateFormatter setDateFormat:oldFormat];
    
    return dateString;
}

+(BOOL) isTheStringAnActualYear:(NSString*)someString
{
    NSString *currentYear = [[Utils sharedInstance] getStringFromDate:[NSDate date] withFormat:@"yyyy"];
    
    return ([Utils isTheString:someString ANumberWithSeparator:@""]
            && someString.length == 4
            && someString.intValue <= currentYear.integerValue
            && someString.intValue >= kYearOfAppBDay);
}

+(BOOL) isTheString:(NSString*)someString ANumberWithSeparator:(NSString*)separator //we decide to include also spaces
{
    NSCharacterSet *mySet = [NSCharacterSet characterSetWithCharactersInString:[NSString stringWithFormat: @"1234567890 %@",separator]];
    NSCharacterSet *revertedSet = [mySet invertedSet]; //here are all the characters that SHOULD NOT be in a number
    NSRange r = [someString rangeOfCharacterFromSet:revertedSet];
    return (r.location == NSNotFound); //invalid characters found?
}

-(NSDate*)getDateFromFormattedString:(NSString *)dateString withFormat:(NSString *)format
{
    if (dateString == nil || [dateString isEqualToString:@""] || [dateString isEqualToString:(NSString*) [NSNull null]])
    {
        return nil;
    }
    
    NSString *oldFormat = self.dateFormatter.dateFormat;
    [self.dateFormatter setDateFormat:format];
    NSDate *date = [self.dateFormatter dateFromString:dateString];
    [self.dateFormatter setDateFormat:oldFormat];
    
    return date;
}

-(NSString*)stringDateForServerFromString:(NSString*)preparedQueryString
{
    BOOL wrongFormat = NO;
    preparedQueryString = [preparedQueryString stringByReplacingOccurrencesOfString:@"-" withString:@""];
    
    NSDate *aDate = [[Utils sharedInstance] getDateFromFormattedString:preparedQueryString withFormat:kDateFormatType2B];
    if (!aDate)
    {
        //Format ddmmyyyy - hhmmss failed, we try with format ddmmyyyy
        aDate = [[Utils sharedInstance] getDateFromFormattedString:preparedQueryString withFormat:kDateFormatType2BOnlyDate];
        if (!aDate)
        {
            //Format ddmmyyyy failed, we try with format hhmmss
            aDate = [[Utils sharedInstance] getDateFromFormattedString:preparedQueryString withFormat:kDateFormatType2BOnlyTime];
            if (!aDate)
            {
                wrongFormat = YES;
            }
            else
            {
                preparedQueryString = [[Utils sharedInstance]getStringFromDate:aDate withFormat:kDateFormatType2BOnlyTime];
            }
        }
        else
        {
            preparedQueryString = [[Utils sharedInstance]getStringFromDate:aDate withFormat:kDateFormatType1BOnlyDate];
        }
    }
    else
    {
        preparedQueryString = [[Utils sharedInstance]getStringFromDate:aDate withFormat:kDateFormatType1B];
    }
    
    //Backend is expecting queries for dates between quotation marks, so we add them
    if (!wrongFormat)
    {
        preparedQueryString = [@"\"" stringByAppendingString:preparedQueryString];
        preparedQueryString = [preparedQueryString stringByReplacingOccurrencesOfString:@"." withString:@"/"];
        preparedQueryString = [preparedQueryString stringByAppendingString:@"\""];
    }
    
    return preparedQueryString;
}

@end

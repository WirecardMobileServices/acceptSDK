//
//  Utils.h
//  Accept Demo
//
//  Created by Fortes, Francisco on 10/27/14.
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "Accept.h"

#define PRINTER_DEFAULT_VALUE @"AirPrint"
#define CURRENCY_SYMBOL_DEFAULT_VALUE @"€"
#define CURRENCY_CODE_DEFAULT_VALUE @"EUR"
#define LOCALE_DEFAULT_VALUE @"en_DE"
#define kRefreshBT 5 //secs
#define kTokenTimer 900 //secs (5 min)
#define kPaymentTimeout 20 //secs
#define kHistoryTimer 20 //secs
#define kYearOfAppBDay 2013
#define kPaymentTimerNotificationName @"kPaymentTimerNotificationName"
#define kTokenTimerNotificationName @"kTokenTimerNotificationName"

#define CHARGE_TYPE_NONE @"NONE"
#define CHARGE_TYPE_NORMAL @"NORMAL"
#define CURRENCY_PRECISION 2
#define CHARGE_TYPE_TIP    @"TIP"
#define CHARGE_TYPE_SERVICE  @"SERVICE_CHARGE"

#define kDateFormatType1 @"yyyy-MM-dd HH:mm:ss"
#define kDateFormatType1B @"yyyy/MM/dd HH:mm:ss"
#define kDateFormatType1BOnlyDate @"yyyy/MM/dd"
#define kDateFormatType1COnlyDate @"yyyy-MM-dd"
#define kDateFormatType2 @"dd.MM.yyyy - HH:mm"
#define kDateFormatType2B @"dd.MM.yyyy HH:mm"
#define kDateFormatType2BOnlyDate @"dd.MM.yyyy"
#define kDateFormatType2BOnlyTime @"HH:mm"
#define kDateFormatTypeStats @"MM.yyyy"
#define kDateFormatType3 @"yyyyMMddHHmmss"

@interface Utils : NSObject
@property (nonatomic, strong) NSDateFormatter *dateFormatter;
@property (nonatomic, strong) NSNumberFormatter *numberFormatter;
@property (nonatomic, strong) NSNumberFormatter *currencyFormatter;
@property (nonatomic,strong) AcceptDataServiceConfig *backendConfig;
@property (nonatomic,strong) Accept *accept;
@property (nonatomic,strong) __block AcceptAccessToken *accessTokenObject;
@property (nonatomic,strong) NSArray *taxAmounts;
@property (nonatomic,strong) NSArray *currencies;
@property(nonatomic) BOOL tokenIsValid;

+(BOOL)checkConnectivity;
+(BOOL)hasConnectivity;
+ (Utils *)sharedInstance;
-(void)setVendorConfigurationVersion:(NSDictionary *)dict;
-(NSString *)getVendorConfigurationVersion:(NSString *)vendorUUID;

-(void)setSelectedVendor:(NSString *)value;
-(NSString*) getSelectedVendor;
-(NSString*) getSelectedPrinterVendor;
-(NSString*) getSelectedPrinter;
-(void)setPrinterDefaultValue:(NSString *)value;
-(void)setPrinterVendorDefaultValue:(NSString *)value;
-(void)setSelectedTerminal:(NSString *)value;
-(NSString*)getCurrencyCodeDefaultValue;
-(NSString*)getCurrencySymbolDefaultValue;
-(NSString*) getSelectedTerminal;
-(NSString*) getVendorTerminalConfigurationVersion:(NSString *)vendorUUID terminalUUID:(NSString *)terminalUUID;
-(void)setTerminalConfigurationUploads:(NSDictionary *)terminalConfigVersion;
-(void)setTaxAmountsForMerchant:(NSArray *)arrTaxes;
-(void)setCurrenciesForMerchant:(NSArray *)arrCurrencies;
-(void)setCountryCurrencyDefaultValue:(NSString *)pCurrencyLocale;
-(void)setCurrencyCodeDefaultValue:(NSString *)pValue;
-(void)setLocaleDefaultValue:(NSString *)pDefaultLocale;
-(BOOL)isPaymentTimerOngoing;
-(void)startPaymentTimerWith:(NSTimeInterval)seconds;
-(void) paymentTimerFinished;

+(BOOL)contains:(NSString *)string substring:(NSString*)substring;
+(void)showAlertWithTitle:(NSString*)title andMessage:(NSString*)text;

-(void) startTokenTimer;
-(BOOL) tokenExpired;

+(BOOL) isTheStringAnActualYear:(NSString*)someString;
+(BOOL) isTheString:(NSString*)someString ANumberWithSeparator:(NSString*)separator;
-(NSString*)stringDateForServerFromString:(NSString*)preparedQueryString;
@end

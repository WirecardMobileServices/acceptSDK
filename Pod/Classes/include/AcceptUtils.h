//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define WAIT_INTERVAL_SIGNATURE 30

@interface AcceptUtils : NSObject

+(AcceptUtils *)sharedInstance;

+ (NSUInteger) numberOfFractionDigitsForCurrency:(NSString*)currencyAsISO4217Code;
+ (NSUInteger) numberOfFractionDigitsForCurrencyIOS:(NSString *)currencyAsISO4217Code __attribute__((deprecated("Mismatch between iOS decimal places and ISO for IDR")));

+ (NSDecimalNumberHandler*) decimalHandlerForCurrency:(NSString*)currencyAsISO4217Code;
+ (NSDecimalNumberHandler *)decimalHandlerForCurrency:(NSString *)currencyAsISO4217Code netTaxation:(NSNumber*)netTaxation;

+ (NSUInteger) iso31661NumericCountryCodeFrom:(NSString*)iso3166Alpha3OrAlpha2;
+ (NSUInteger) isoISO4217CurrencyNumericCodeFrom:(NSString*)currencyAsISO4217Code;
+ (NSUInteger) isoISO4217CurrencyMinorUnitsFrom:(NSString*)currencyAsISO4217Code;

+ (NSString*) expandUnderlyingErrors:(NSError*)error;

+ (NSDecimalNumber*) amountWithoutFraction:(NSDecimalNumber*)amount currencyAsISO4217Code:(NSString*)currencyAsISO4217Code;

+ (NSData*) hexStringToData:(NSString*)hexText error:(NSError**)error;

+(BOOL)unzipFile:(NSString *)filePath toDocsDir:(NSString*)docsDir;

+ (BOOL) shouldAskForPINOnlineCheck:(NSString*)bin serviceCode:(NSString*)serviceCode;
+(NSString *)getMaskedPANFromTrack2:(NSString *)track2;
-(NSDictionary *)getIssuerInformationFromPAN:(NSString *)pan;
-(NSDictionary *)getIssuerInformationFromPreparedPAN:(NSString *)pan;

+(NSString*)getCurrencyStringCodeForLine:(NSString*)line;
+(NSString*)getCountryStringCodeForLine:(NSString*)line;

+ (NSData *)encodeEMVIccBlob:(NSArray *)iccData;

-(NSString*)vendorIDForName:(NSString*)vendorDisplayName andUUID:(NSString*)vendorUUID;

-(BOOL)isVendorHavingBluetoothTerminals:(NSString*)vendorName;

+(BOOL)isRequiringSignatureCVMResult:(NSString*)resultCVM;


+(void)showActivityIndicatorOnView:(UIView *)onView withMessage:(NSString *)message;

+(void)hideActivityIndicator:(UIView *)onView;

+(void)hideActivityIndicator:(UIView *)onView completion:(void (^)(void))moreCompletion;

@end

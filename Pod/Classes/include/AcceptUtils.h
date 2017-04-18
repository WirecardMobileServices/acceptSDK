//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#define WAIT_INTERVAL_SIGNATURE 30

/**
 *  @class AcceptUtils
 *  @discussion Accept utility functions
 **/
@interface AcceptUtils : NSObject

/**
 *  @brief Accept utilities Singleton
 *  @return shared instance
 **/
+(AcceptUtils *)sharedInstance;

/**
 *  @brief Get number of fraction digits
 *  @param currencyAsISO4217Code Currency code
 *  @return fraction digits count
 **/
+ (NSUInteger) numberOfFractionDigitsForCurrency:(NSString*)currencyAsISO4217Code;
/**
 *  @brief Get number of fraction digits using iOS frameworks
 *  @param currencyAsISO4217Code Currency code
 *  @return fraction digits count
 **/
+ (NSUInteger) numberOfFractionDigitsForCurrencyIOS:(NSString *)currencyAsISO4217Code __attribute__((deprecated("Mismatch between iOS decimal places and ISO for IDR")));

/**
 *  @brief Get decimal handler for currency taking into account decimal places for the currency
 *  @param currencyAsISO4217Code Currency code
 *  @return decimal handler
 **/
+ (NSDecimalNumberHandler*) decimalHandlerForCurrency:(NSString*)currencyAsISO4217Code;
/**
 *  @brief Get decimal handler for currency taking into account decimal places for the currency
 *  @param currencyAsISO4217Code Currency code
 *  @param netTaxation - tax inclusive | exclusive (net taxation)
 *  @return decimal handler
 **/
+ (NSDecimalNumberHandler *)decimalHandlerForCurrency:(NSString *)currencyAsISO4217Code netTaxation:(NSNumber*)netTaxation;

/**
 *  @brief Get the ISO country code from Alpha 2 or ALpha3 country code
 *  @param iso3166Alpha3OrAlpha2 Alpha 2 or ALpha3 country code
 *  @return ISO country code
 **/
+ (NSUInteger) iso31661NumericCountryCodeFrom:(NSString*)iso3166Alpha3OrAlpha2;
/**
 *  @brief Get the numeric currency code from ISO4217 currency code
 *  @param currencyAsISO4217Code ISO4217 currency code
 *  @return ISO currency code
 **/
+ (NSUInteger) isoISO4217CurrencyNumericCodeFrom:(NSString*)currencyAsISO4217Code;
/**
 *  @brief Get the minor units for the currency
 *  @param currencyAsISO4217Code ISO4217 currency code
 *  @return currency minor units
 **/
+ (NSUInteger) isoISO4217CurrencyMinorUnitsFrom:(NSString*)currencyAsISO4217Code;

/**
 *  @brief Expand underlying errors into a string
 *  @param error Errors
 *  @return string representation of underlying errors
 **/
+ (NSString*) expandUnderlyingErrors:(NSError*)error;
/**
 *  @brief Transform the amount to units according to currency
 *  @param amount decimal amount
 *  @return amount units
 **/
+ (NSDecimalNumber*) amountWithoutFraction:(NSDecimalNumber*)amount currencyAsISO4217Code:(NSString*)currencyAsISO4217Code;
/**
 *  @brief Transform hex string to data
 *  @param hexText hexa string to be transform to data
 *  @param error return transformation error
 *  @return data representation of hexa string
 **/
+ (NSData*) hexStringToData:(NSString*)hexText error:(NSError**)error;
/**
 *  @brief UNzip file at given path
 *  @param docsDir target directory for unzip
 *  @return YES if successful
 **/
+(BOOL)unzipFile:(NSString *)filePath toDocsDir:(NSString*)docsDir;
/**
 *  @brief Check if the payment flow should ask for PIN online validation based on BIN and service code
 *  @param bin Card BIN
 *  @param serviceCode Merchant service code
 *  @return YES if payment flow should ask for online PIN validation
 **/
+ (BOOL) shouldAskForPINOnlineCheck:(NSString*)bin serviceCode:(NSString*)serviceCode;
/**
 *  @brief Check if card has chip pased on the service code
 *  @param serviceCode Merchant service code
 *  @return YES if card has contact chip
 **/
+ (BOOL) hasChipBasedOn:(NSString*)serviceCode;
/**
 *  @brief Check if the BIN is Amex scheme
 *  @param bin Card BIN
 *  @return YES if BIN is Amex scheme
 **/
+ (BOOL)isBinFromAMEX:(NSString*)bin;
/**
 *  @brief Obtain the masked PAN from track2 equivalent
 *  @param track2 Track2 equivalent
 *  @return Masked PAN
 **/
+(NSString *)getMaskedPANFromTrack2:(NSString *)track2;
/**
 *  @brief Obtain issuer information from PAN
 *  @param pan Card PAN
 *  @return Issuer information
 **/
-(NSDictionary *)getIssuerInformationFromPAN:(NSString *)pan;
/**
 *  @brief Obtain issuer information from prepared PAN
 *  @param pan Card PAN (masked)
 *  @return Issuer information
 **/
-(NSDictionary *)getIssuerInformationFromPreparedPAN:(NSString *)pan;
/**
 *  @brief Obtain issuer information from accept card type
 *  @param acceptCardType Accept card type - if PAN not available
 *  @return Issuer information
 **/
-(NSDictionary *)getIssuerByAcceptCardType:(NSString *)acceptCardType;
/**
 *  @brief Obtain Currency code from EMVSwiper data line
 *  @param line EMVSwiper formatted currency line
 *  @return Currency code
 **/
+(NSString*)getCurrencyStringCodeForLine:(NSString*)line;
/**
 *  @brief Obtain Cuntry code from EMVSwiper data line
 *  @param line EMVSwiper formatted country line
 *  @return Country code
 **/
+(NSString*)getCountryStringCodeForLine:(NSString*)line;
/**
 *  @brief Get number of decimal places for the curency
 *  @param currency currency code
 *  @return number of decimal places
 **/
+(int)getCurrencyDecimalPlaces:(NSString *)currency;
/**
 *  @brief Get decimal number divider for the currency
 *  @param currency currency code
 *  @return decimal number divider
 **/
+(NSDecimalNumber *)getDecimalNumberDividerForCurrency:(NSString *)currency;
/**
 *  @brief Encode Array of EMV tags into EMV data
 *  @param iccData EMV data array (Posmate formatted)
 *  @return EMV data
 **/
+ (NSData *)encodeEMVIccBlob:(NSArray *)iccData;
/**
 *  @brief Obtain the vendor ID by its display name
 *  @param vendorDisplayName Vendor display name
 *  @param vendorUUID Vendor UUID
 *  @return Vendor ID
 **/
-(NSString*)vendorIDForName:(NSString*)vendorDisplayName andUUID:(NSString*)vendorUUID;
/**
 *  @brief Does vendor support Bluetooth terminals
 *  @param vendorName Vendor  name
 *  @return YES if vendors supporst Bluetooth terminals
 **/
-(BOOL)isVendorHavingBluetoothTerminals:(NSString*)vendorName;
/**
 *  @brief Does CVM result require Signature to be collected
 *  @param resultCVM CVM result
 *  @return YES if CVM result requires signature to be collected
 **/
+(BOOL)isRequiringSignatureCVMResult:(NSString*)resultCVM;
/**
 *  @brief Luhn check for PAN
 *  @param stringToTest PAN
 *  @return YES if luhn check OK
 **/
+ (BOOL) luhnCheck:(NSString *)stringToTest;
/**
 *  @brief Show activity indicator on a view
 *  @param onView view to show the activity indicator on
 *  @param message Message to show on the activity indicator
 **/
+(void)showActivityIndicatorOnView:(UIView *)onView withMessage:(NSString *)message;
/**
 *  @brief Hide displayed activity indicator on a view
 *  @param onView view to show the activity indicator on
 **/
+(void)hideActivityIndicator:(UIView *)onView;
/**
 *  @brief Hide displayed activity indicator on a view
 *  @param onView view to show the activity indicator on
 *  @param moreCompletion completion to call after hiding the view
 **/
+(void)hideActivityIndicator:(UIView *)onView completion:(void (^)(void))moreCompletion;
/**
 *  @brief Generate QR code from string data
 *  @param qrString String to create QR code for
 *  @return QR code
 **/
+(UIImage*)generateQRCodeFromString:(NSString *)qrString;
/**
 *  @brief Generate Bar code 128  code from string data
 *  @param stringData String to create Bar code for
 *  @return Bar code 128
 **/
+(UIImage*)generateBarCode128FromString:(NSString *)stringData;
/**
 *  @brief Generate unique ID
 *  @return UUID
 **/
+ (NSString *)uuid;
@end

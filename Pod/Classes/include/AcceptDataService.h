//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "AcceptExtensionTerminalInfo.h"
#import "AcceptDataServiceConfig.h"
#import "AcceptBasket.h"
#import "AcceptUserResponse.h"
#import "AcceptTransaction.h"
#import "AcceptCustomDataResponse.h"
#import "AcceptTransactionsQuery.h"
#import "AcceptExtensionTerminalInfo.h"
#import "AcceptTerminalConfig.h"
#import "AcceptUtils.h"
#import "AcceptPaymentParameters.h"
#import "AcceptV3DataTypes.h"
#import "AcceptStatistics.h"


/**
 *  @class AcceptExtendedProcessingInfo
 *  @discussion Extented processing info class. Content needed for some Chip transactions with online PIN verification and/or CVM methods
 **/
@interface AcceptExtendedProcessingInfo : NSObject
/// Gratuity amount
@property (nonatomic) NSInteger gratuityAmount;
/// Application ID
@property (nonatomic, strong) NSString * applicationId;
/// Merchant ID
@property (nonatomic, strong) NSString * merchantId;
/// Encrypted PIN
@property (nonatomic, strong) NSString * encryptedPIN;
/// Reversal is required
@property (nonatomic) BOOL reversalIsRequired;
/// Reversal reason
@property (nonatomic) int reversalReason;
/// Signature check is required
@property (nonatomic) BOOL signatureCheckIsRequired;
/// Application cryptogram
@property (nonatomic) NSString *applicationCryptogram;
/// Online authentication
@property (nonatomic) BOOL onlineAuthentication;
/// Capture is required
@property (nonatomic) BOOL isCaptureRequired;
/// Service code
@property (nonatomic, strong) NSString *serviceCode;
@end


/**
 *  @class AcceptAccessToken
 *  @discussion Access Token info class. access token and its expiration time
 **/
@interface AcceptAccessToken : NSObject
/// Access token
@property (nonatomic, strong) NSString * accessToken;
/// Expires in second
@property (nonatomic) NSNumber * expireInSeconds;
@end


/**
 *  @class AcceptTerminalFirmware
 *  @discussion Terminal firmware class. Content required for the Accept terminal firmware version
 **/
@interface AcceptTerminalFirmware : NSObject
/// Vendor UUID
@property (nonatomic, strong) NSString * vendorUUID;
/// Terminal UUID
@property (nonatomic, strong) NSString * terminalUUID;
/// Firmware URL
@property (nonatomic, strong) NSString *firmwareUrl;
/// Firmware version
@property (nonatomic, strong) NSString *firmwareVersion;
/// Firmware MD5
@property (nonatomic, strong) NSString *firmwareMD5;

@end

/**
 *  @class AcceptInventory
 *  @discussion Accept Inventory class. Content required for the Accept inventory
 **/
@interface AcceptInventory : NSObject
/// Inventory URL
@property (nonatomic, strong) NSString *url;
/// Version
@property (nonatomic, strong) NSString *version;
/// MD5
@property (nonatomic, strong) NSString *md5;

@end

/**
 *  @class AcceptDataService
 *  @discussion Data service providing all Web services API for Accept backend
 **/
@interface AcceptDataService : NSObject

/**
 *  @brief initialize the data service with configuration
 *  @param config Backend configuration
 *  @param sdkVersion SDK version
 **/
- (instancetype) initWithConfig:(AcceptDataServiceConfig*)config sdkVersion:(NSString*)sdkVersion;

/**
 *  @brief Request access token for the credentials
 *  @param username Username
 *  @param password Password
 **/
- (AcceptAccessToken*) requestAccessToken:(NSString*)username password:(NSString*)password error:(NSError**)error;
/**
 *  @brief Request user details
 *  @param accessToken access token
 *  @param error return error
 **/
- (AcceptUserResponse*) requestUser:(NSString*)accessToken error:(NSError**)error;
/**
 *  @brief Request custom data
 *  @param accessToken access token
 *  @param error return error
 **/
- (AcceptCustomDataResponse*) requestCustomData:(NSString*)accessToken error:(NSError**)error;
/**
 *  @brief Request new payment
 *  @param accessToken access token
 *  @param signature cardholder signature
 *  @param terminalInfo terminal details
 *  @param basket basket details to create the payment with
 *  @param cardInfo Card details
 *  @param extendedInfo Extended information for this payment
 *  @param error return error
 **/
- (AcceptTransaction*) requestNewPayment:(NSString*)accessToken signature:(UIImage*)signature terminalInfo:(AcceptExtensionTerminalInfo*)terminalInfo basket:(AcceptBasket*)basket cardInfo:(id)cardInfo extendedInfo:(AcceptExtendedProcessingInfo*)extendedInfo error:(NSError**)error;
/**
 *  @brief Request new cash payment
 *  @param transactionType Transaction type
 *  @param accessToken access token
 *  @param signature cardholder signature
 *  @param terminalInfo terminal details
 *  @param basket basket details to create the payment with
 *  @param cardInfo Card details
 *  @param extendedInfo Extended information for this payment
 *  @param error return error
 **/
- (AcceptTransaction*) requestNewPayment:(AcceptTransactionType)transactionType accessToken:(NSString*)accessToken signature:(UIImage*)signature terminalInfo:(AcceptExtensionTerminalInfo*)terminalInfo basket:(AcceptBasket*)basket cardInfo:(id)cardInfo extendedInfo:(AcceptExtendedProcessingInfo*)extendedInfo error:(NSError**)error;
/**
 *  @brief Request new cash payment
 *  @param accessToken access token
 *  @param basket basket details to create the payment with
 *  @param error return error
 **/
- (AcceptTransaction*) requestNewCashPayment:(NSString*)accessToken basket:(AcceptBasket*)basket error:(NSError**)error;
/**
 *  @brief Request new Alipay payment
 *  @param accessToken access token
 *  @param basket basket details to create the payment with
 *  @param consumerId Alipay Consumer ID
 *  @param error return error
 **/
- (AcceptTransaction*) requestNewAlipayPayment:(NSString*)accessToken
                                        basket:(AcceptBasket*)basket
                                    consumerId:(NSString *)consumerId
                                         error:(NSError**)error;
/**
 *  @brief Request new NULL payment - used to initialize Cash management for Austria
 *  @param accessToken access token
 *  @param currency Currency
 *  @param error return error
 **/
- (AcceptTransaction*) requestNewNullPayment:(NSString*)accessToken
                                    currency:(NSString*)currency
                                       error:(NSError**)error;
/**
 * Description: Resets the password for the specified User Id - the reset password instructions are sent by:
 *  - email if the merchant user has email address specified
 *  - SMS if the merchant user does not have the email address but has a phone number specified
 */
- (BOOL) resetPassword:(NSString*)userId error:(NSError**)error;

/**
 * Description: Forgot External Id - the reminder of External Id is sent to specified email
 */
- (BOOL) forgotExternalId:(NSString*)email error:(NSError**)error;

/*
 * Description: Change password - user want to replace old with new one and rewrites it as confirmation
 */
- (NSDictionary *) changePassword:(NSString*)userToken newPassword:(NSString*)newPassword reNewPassword:(NSString*)reNewPassword error:(NSError**)error;

/**
 *  @brief Query transactions
 *  @param accessToken access token
 *  @param query Query parameters
 *  @param error return error
 **/
- (NSArray*) requestTransactions:(NSString*)accessToken query:(AcceptTransactionsQuery*)query error:(NSError**)error;

/**
 *  @brief Get transaction statistics
 *  @param accessToken access token
 *  @param from From date
 *  @param to To date
 *  @param groupBy Group by criteria
 *  @param resultsGroup Results
 *  @param isNesting Nest the results by date
 *  @param error return error
 **/
- (AcceptStatistics*) requestStatistics:(NSString*)accessToken
                                   from:(NSDate*)from
                                     to:(NSDate*)to
                                groupBy:(AcceptStatisticsGroupBy)groupBy
                           resultsGroup:(NSArray *)resultsGroup
                          statusNesting:(BOOL)isNesting
                                  error:(NSError**)error;

/**
 *  @brief Get terminal configuration information by serial number
 *  @param accessToken access token
 *  @param terminalSerialNo Terminal serial number
 *  @param error return error
 **/
- (AcceptTerminalConfig*) requestTerminalConfigurationForSerialNo:(NSString*)accessToken terminalSerialNo:(NSString*)terminalSerialNo error:(NSError**)error;

/**
 *  @brief Get configuration information by version number
 *  @param accessToken access token
 *  @param version Version of the installed configuration
 *  @param error return error
 **/
- (AcceptTerminalConfigFiles*) requestConfigFile:(NSString*)accessToken currentVersion:(NSString*)version error:(NSError**)error;
/**
 *  @brief Get firmware for terminal
 *  @param accessToken access token
 *  @param terminalFamily Terminal family
 *  @param error return error
 **/
- (AcceptTerminalFirmware*) requestFirmware:(NSString*)accessToken terminalFamily:(NSString *)terminalFamily error:(NSError**)error;
/**
 *  @brief Get configuration files
 *  @param url file url
 *  @param error return error
 **/
- (NSData*)downloadConfigFilesBundleFromURL:(NSString*)url error:(NSError**)error;
/**
 *  @brief Get inventory files
 *  @param url file url
 *  @param error return error
 **/
- (NSData*)downloadInventoryFileFromURL:(NSString*)url error:(NSError**)error;

/**
 *  @brief Is the error connection error
 *  @return YES if connection error
 **/
+ (BOOL) isNoConnectionError:(NSError*)error;
/**
 *  @brief Is the error timeout error
 *  @return YES if timeout error
 **/
+ (BOOL) isRequestTimeoutError:(NSError*)error;
/**
 *  @brief Is the error authentication error
 *  @return YES if authentication error
 **/
+ (BOOL) isAuthError:(NSError*)error;
/**
 *  @brief Is the error unprocessable entity error
 *  @return YES if unprocessable entity error
 **/
+ (BOOL) isUnprocessableEntity:(NSError*)error;
/**
 *  @brief Is the error Accept backend error
 *  @return YES if Accept backend entity error
 **/
+ (BOOL) isAcceptError:(NSError*)error;
/**
 *  @brief Update payment
 *  @param paymentID Payment ID
 *  @param accessToken access token
 *  @param operation Update operation
 *  @param paymentUpdateParameters Update parameters
 *  @param error return error
 **/
- (AcceptTransaction*) requestOperationOnPaymentWithID:(NSString*)paymentID  accessToken:(NSString*)accessToken operation:(AcceptOperationOnPayment)operation  paymentUpdateParameters:(AcceptPaymentParameters *)paymentUpdateParameters  error:(NSError**)error;
/**
 *  @brief Get inventory changes for version
 *  @param accessToken access token
 *  @param version installed inventory version
 *  @param error return error
 **/
- (AcceptInventory*) requestInventory:(NSString*)accessToken currentVersion:(NSString*)version error:(NSError**)error;

/**
 *  @brief Generate DEP report on demand
 *  @param accessToken access token
 *  @param error return error
 *  @return YES if no error
 **/
- (BOOL) requestDEPReport:(NSString*)accessToken error:(NSError**)error;

@end

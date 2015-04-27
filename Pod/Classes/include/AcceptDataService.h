//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//
//  Authors:
//      damian.kolakowski@up-next.com
//      radoslav.danko@wirecard.com
//      francisco.fortes@wirecard.com

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
 *  @class AcceptAccessToken
 *  @discussion Access Token info class. access token and its expiration time
 **/
@interface AcceptAccessToken : NSObject
/**
 */
@property (nonatomic, strong) NSString * accessToken;
/**
 */
@property (nonatomic) NSNumber * expireInSeconds;
@end


/**
 *  @class AcceptTerminalFirmware
 *  @discussion Terminal firmware class. Content required for the Accept terminal firmware version
 **/
@interface AcceptTerminalFirmware : NSObject
/**
 */
@property (nonatomic, strong) NSString * vendorUUID;
/**
 */
@property (nonatomic, strong) NSString * terminalUUID;
/**
 */
@property (nonatomic, strong) NSString *firmwareUrl;
/**
 */
@property (nonatomic, strong) NSString *firmwareVersion;
/**
 */
@property (nonatomic, strong) NSString *firmwareMD5;

@end

/**
 *  @class AcceptInventory
 *  @discussion Accept Inventory class. Content required for the Accept inventory
 **/
@interface AcceptInventory : NSObject
/**
 */
@property (nonatomic, strong) NSString *url;
/**
 */
@property (nonatomic, strong) NSString *version;
/**
 */
@property (nonatomic, strong) NSString *md5;

@end

@interface AcceptDataService : NSObject


- (instancetype) initWithConfig:(AcceptDataServiceConfig*)config sdkVersion:(NSString*)sdkVersion;

- (AcceptAccessToken*) requestAccessToken:(NSString*)username password:(NSString*)password error:(NSError**)error;
- (AcceptUserResponse*) requestUser:(NSString*)accessToken error:(NSError**)error;
- (AcceptCustomDataResponse*) requestCustomData:(NSString*)accessToken error:(NSError**)error;

- (AcceptTransaction*) requestNewPayment:(NSString*)accessToken signature:(UIImage*)signature terminalInfo:(AcceptExtensionTerminalInfo*)terminalInfo basket:(AcceptBasket*)basket cardInfo:(id)cardInfo onlineAuthentication:(BOOL)onlineAuthentication error:(NSError**)error;

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
- (BOOL) changePassword:(NSString*)userToken newPassword:(NSString*)newPassword reNewPassword:(NSString*)reNewPassword error:(NSError**)error;

- (NSArray*) requestTransactions:(NSString*)accessToken query:(AcceptTransactionsQuery*)query error:(NSError**)error;

- (AcceptStatistics*) requestStatistics:(NSString*)accessToken
                                   from:(NSDate*)from
                                     to:(NSDate*)to
                                groupBy:(AcceptStatisticsGroupBy)groupBy
                           resultsGroup:(NSArray *)resultsGroup
                          statusNesting:(BOOL)isNesting
                                  error:(NSError**)error;

- (AcceptTerminalConfig*) requestTerminalConfigurationForSerialNo:(NSString*)accessToken terminalSerialNo:(NSString*)terminalSerialNo error:(NSError**)error;

- (AcceptTerminalConfigFiles*) requestConfigFile:(NSString*)accessToken currentVersion:(NSString*)version error:(NSError**)error;

- (AcceptTerminalFirmware*) requestFirmware:(NSString*)accessToken terminalFamily:(NSString *)terminalFamily error:(NSError**)error;

- (NSData*)downloadConfigFilesBundleFromURL:(NSString*)url error:(NSError**)error;
- (NSData*)downloadInventoryFileFromURL:(NSString*)url error:(NSError**)error;

+ (BOOL) isNoConnectionError:(NSError*)error;
+ (BOOL) isRequestTimeoutError:(NSError*)error;
+ (BOOL) isAuthError:(NSError*)error;
+ (BOOL) isUnprocessableEntity:(NSError*)error;
+ (BOOL) isAcceptError:(NSError*)error;

- (AcceptTransaction*) requestOperationOnPaymentWithID:(NSString*)paymentID  accessToken:(NSString*)accessToken operation:(AcceptOperationOnPayment)operation  paymentUpdateParameters:(AcceptPaymentParameters *)paymentUpdateParameters  error:(NSError**)error;

- (AcceptInventory*) requestInventory:(NSString*)accessToken currentVersion:(NSString*)version error:(NSError**)error;

@end

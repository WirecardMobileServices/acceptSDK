//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//
//  Authors:
//      damian.kolakowski@up-next.com
//      francisco.fortes@wirecard.com
//      radoslav.danko@wirecard.com

#import <Foundation/Foundation.h>

#import "AcceptTransaction.h"
#import "AcceptDataServiceConfig.h"
#import "AcceptDataService.h"
#import "AcceptBasket.h"
#import "AcceptBasketItem.h"
#import "AcceptTransactionsQuery.h"
#import "AcceptUserResponse.h"
#import "AcceptPaymentParameters.h"
#import "AcceptStatistics.h"
#import "AcceptV3DataTypes.h"
#import "AcceptReceipt.h"

#define SDK_VERSION @"1.6.106"

/**
 */
extern NSString * const AcceptSpireVendorUUID;
/**
 */
extern NSString * const AcceptbbPOSVendorUUID;
/**
 */
extern NSString * const AcceptIDTECHVendorUUID;
/**
 */
extern NSString * const AcceptDatecsVendorUUID;
/**
 */
extern NSString * const AcceptVeriFoneVendorUUID;
/**
 */
extern NSString * const AcceptErrorDomain;

/**
 *  @class AcceptTerminalVendor
 *  @discussion Terminal vendor class
 **/
@interface AcceptTerminalVendor : NSObject

/**
 */
@property (nonatomic, strong) NSString * uuid;
/**
 */
@property (nonatomic, strong) NSString * displayName;
/**
 */
@property (nonatomic, strong) NSString * alternativeDisplayName;
@end

/**
 *  @class AcceptTerminal
 *  @discussion Terminal model class
 **/
@interface AcceptTerminal : NSObject
/**
 */
@property (nonatomic, strong) NSString * uuid;
/**
 */
@property (nonatomic, strong) NSString * displayName;
/**
 */
@property (nonatomic, strong) NSString * alternativeDisplayName;
@end

/**
 *  @class AcceptPrinterVendor
 *  @discussion Printer vendor class
 **/
@interface AcceptPrinterVendor : NSObject
/**
 */
@property (nonatomic, strong) NSString * uuid;
/**
 */
@property (nonatomic, strong) NSString * displayName;
/**
 */
@property (nonatomic, strong) NSString * alternativeDisplayName;
@end

/**
 *  @class AcceptPrinter
 *  @discussion Printer model class
 **/
@interface AcceptPrinter : NSObject
/**
 */
@property (nonatomic, strong) NSString * uuid;
/**
 */
@property (nonatomic, strong) NSString * displayName;
/**
 */
@property (nonatomic, strong) NSString * alternativeDisplayName;
@end

/**
 *  @class AcceptPaymentConfig
 *  @discussion Payment configuration class. Content required to execute the payment flow
 **/
@interface AcceptPaymentConfig : NSObject
/**
 */
@property (nonatomic, strong) NSString * vendorUUID;
/**
 */
@property (nonatomic, strong) NSString * terminalUUID;
/**
 */
@property (nonatomic, strong) AcceptDataServiceConfig * backendConfig;
/**
 */
@property (nonatomic, strong) AcceptBasket * basket;
/**
 */
@property (nonatomic, strong) NSString * accessToken;
/**
 */
@property (nonatomic) BOOL allowGratuity;
@end

/**
 *  @class AcceptSignatureRequest
 *  @discussion Signature request class. It should be given fulfilled once the signature image has been captured, to be included in the transaction body when required
 **/
@interface AcceptSignatureRequest: NSObject
/**
 */
@property (nonatomic, strong) NSString *cardHolderName;
/**
 */
@property (nonatomic, strong) NSString *cardNumber;
/**
 */
@property (nonatomic) NSInteger gratuityAmount;
/**
 */
@property (nonatomic, copy) void(^signatureCallback)(UIImage*, NSError*);
@end

/**
 *  @class AcceptAppSelectionRequest
 *  @discussion Application selection request class. It should be given fulfilled once a prefered application has been chosen from the list (used in chip compatible terminals with no screen)
 **/
@interface AcceptAppSelectionRequest: NSObject
/**
 */
@property (nonatomic, strong) NSArray *appsArray;
/**
 */
@property (nonatomic, copy) void(^appSelectionCallback)(NSUInteger, NSError*);
@end

/**
 *  @class AcceptPrinterConfig
 *  @discussion Printer configuration class. Content required to execute the printing flow
 **/
@interface AcceptPrinterConfig : NSObject
/**
 */
@property (nonatomic, strong) NSString * vendorUUID;
/**
 */
@property (nonatomic, strong) NSString * printerUUID;
/**
 */
@property (nonatomic, strong) AcceptReceipt *receipt;
@end

/**
 *  @class AcceptExtendedProcessingInfo
 *  @discussion Extented processing info class. Content needed for some Chip transactions with online PIN verification and/or CVM methods
 **/
@interface AcceptExtendedProcessingInfo : NSObject
/**
 */
@property (nonatomic) NSInteger gratuityAmount;
/**
 */
@property (nonatomic, strong) NSString * applicationId;
/**
 */
@property (nonatomic, strong) NSString * merchantId;
/**
 */
@property (nonatomic, strong) NSString * encryptedPIN;
/**
 */
@property (nonatomic) BOOL reversalIsRequired;
/**
 */
@property (nonatomic) int reversalReason;
/**
 */
@property (nonatomic) BOOL signatureCheckIsRequired;
/**
 */
@property (nonatomic) NSString *applicationCryptogram;
/**
 */
@property (nonatomic) BOOL onlineAuthentication;
/**
 */
@property (nonatomic) BOOL isCaptureRequired;
@end

/**
*  @class Accept
*  @discussion Main SDK class. It contains all public properties and functions
**/
@interface Accept : NSObject
/**
 */
///version Current SDK version
@property (nonatomic, readonly) NSString * version;

/**
 *  @brief Adquire an array of available terminal vendors
 *  @param completion The array of vendors found, returned with objects of class AcceptTerminalVendor
 **/
- (void) discoverSupportedVendors:(void (^)(NSArray *))completion;

/**
 *  @brief Adquire an array of terminal models for a single vendor
 *  @param vendorUUID The Unique vendor id string. vendorUUIDs are adquired using discoverSupportedVendors
 *  @param completionBlock Block that receives the array of AcceptTerminal objects or an error
 **/
- (void) discoverTerminalsForVendor:(NSString*)vendorUUID
                         completion:(void (^)(NSArray *, NSError*))completionBlock;

/**
 *  @brief Update terminals for a vendor. Chip compatible terminals receive config files from backend; this function will decide if the updates are needed according current version
 *  @param vendorUUID The Unique vendor id string. vendorUUIDs are adquired using discoverSupportedVendors
 *  @param token The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param completionAlertUI Block that receives the latest updated version or an error
 **/
- (void) updateTerminalsForVendor:(NSString*)vendorUUID
                         andToken:(NSString*)token andConfig:(AcceptDataServiceConfig*)config
                       completion:(void (^)(NSInteger, NSError*))completionAlertUI;

/**
 *  @brief Update terminals firmware for a vendor. Chip compatible terminals receive firmware files from backend; this function will decide if the updates are needed according current version
 *  @param vendorUUID The Unique vendor id string. vendorUUIDs are adquired using discoverSupportedVendors
 *  @param token The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param firmware Firmware details
 *  @param completionAlertUI Block that receives the latest updated version or an error
 **/
- (void) updateTerminalFirmwareForVendor:(NSString*)vendorUUID
                                andToken:(NSString*)token
                               andConfig:(AcceptDataServiceConfig*)config
                             andFirmware:(AcceptTerminalFirmware *)firmware
                              completion:(void (^)(NSInteger, NSError*))completionAlertUI;

/**
 *  @brief Discover supported printer vendors
 *  @param completion Block that will receive an array of AcceptPrinterVendor objects
 **/
-(void) discoverSupportedPrinterVendors:(void (^)(NSArray *))completion;

/**
 *  @brief Discover the printer types for a brand/vendor
 *  @param vendorUUID The Unique vendor id string. vendorUUIDs are adquired using discoverSupportedPrinterVendors
 *  @param completion Block that will receive an array of AcceptPrinter objects and an error if it exists
 **/
- (void) discoverPrintersForVendor:(NSString*)vendorUUID
                        completion:(void (^)(NSArray *, NSError*))completion;

/**
 *  @brief Request the user session access token (that will expire if no activity is executed after several minutes)
 *  @param username unique username for login in
 *  @param password user password
 *  @param config Instance needed to use backend services
 *  @param completion Block that receives the server response or an error
 **/
- (void) requestAccessToken:(NSString*)username
                   password:(NSString*)password
                     config:(AcceptDataServiceConfig*)config
                 completion:(void (^)(AcceptAccessToken*, NSError*))completion;

/**
 *  @brief Request merchant info from an user session token
 *  @param accessToken The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param completion Block that receives the merchant info or an error
 **/
- (void) requestMerchantInfo:(NSString *)accessToken
                      config:(AcceptDataServiceConfig*)config
                  completion:(void (^)(AcceptUserResponse *, NSError *))completion;

/**
 *  @brief Request for the config file in backend
 *  @param accessToken The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param version Current version already downloaded. This can be hardcoded to zero for simplification.
 *  @param completion Block that receives the config file or an error
 *  @return
 **/
- (void) queryConfigFile:(NSString*)accessToken
                  config:(AcceptDataServiceConfig*)config
       andCurrentVersion:(NSString*)version
              completion:(void (^)(AcceptTerminalConfigFiles*, NSError*))completion;

/**
 *  @brief Request for the firmware file in backend
 *  @param config Instance needed to use backend services
 *  @param completion Block that receives the config file or an error
 *  @return
 **/
- (void) queryFirmware:(AcceptPaymentConfig*)config completion:(void (^)(BOOL, AcceptTerminalFirmware*, NSError*))completion;

/**
 *  @brief Request for the inventory file in backend
 *  @param config Instance needed to use backend services
 *  @param completion Block that receives the config file or an error
 *  @return
 **/
- (void) queryInventoryFile:(NSString*)accessToken
                     config:(AcceptDataServiceConfig*)config
          andCurrentVersion:(NSString*)version
                 completion:(void (^)(AcceptInventory*, NSError*))completion;

/**
 *  @brief Request to download inventory data
 *  @param config:(AcceptDataServiceConfig*)config
 *  @param url to download the inventory data from
 *  @param completion Block that receives the data file or an error
 *  @return
 **/
-(void)getInventoryData:(AcceptDataServiceConfig *)config
                 theURL:(NSString *)theURL
             completion:(void (^)(BOOL, NSInteger, NSData *, NSError*))completionAlertUI;

/**
 *  @brief Start the payment process
 *  @param config Instance needed to use backend services
 *  @param completion Block that will be called at the very end of payment flow. It provides an AcceptTransaction object (that may be nil if unauthorised) or a descriptive error
 *  @param progress Block with info to update the UI in base of alerts, errors or general info messages. Pure feedback for the user
 *  @param signatureRequest Block that needs to execute the option to capture a signature an return the signature data
 *  @param signatureVerification Block that informs that a signature needs to be verified. This is done after the transaction has been already send to background, but the final approval depends on the merchant. Only terminals with signature verification built it (i.e. Spire Posmate) requires actions here. And signatureVerification block can be handled in the same way as the completion block, as indicates a completion itself (just lacking the second generate AC)
 *  @param appSelection Block informs that an application selection is needed with the chip card inserted.
 **/
- (void) startPay:(AcceptPaymentConfig*)config
       completion:(void (^)(AcceptTransaction*, NSError*))completion
         progress:(void (^)(AcceptStateUpdate))progress
        signature:(void (^)(AcceptSignatureRequest*))signatureRequest
signatureVerification:(void (^)(AcceptTransaction*, NSError*))signatureVerification
     appSelection:(void (^)(AcceptAppSelectionRequest *))appSelection;

/**
 *  @brief Cancel the payment flow. This is usually called from UI (cancel button when available) or some error from signature or completion block. Notice that an improper usage of this function (for example during online communication or level 2 flow in terminal) can produce unexpected errors
 **/
- (void) cancelPay;

/**
 *  @brief Start the printing flow
 *  @param config Instance needed to use the printer
 *  @param completion Block that will receive the success as a boolean and an error if it exists
 *  @param progress Block with the progress status
 *  @return
 **/
- (void) startPrint:(AcceptPrinterConfig*)config
         completion:(void (^)(BOOL, NSError*))completion
           progress:(void (^)(AcceptPrinterStateUpdate))progress;

/**
 *  @brief Search for transactions from a specify query
 *  @param accessToken The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param query Query for the search
 *  @param completion Block that will receive the array of transaction objects (type AcceptTransaction) or an error
 **/
- (void) queryTransactions:(NSString*)accessToken
                    config:(AcceptDataServiceConfig*)config
                     query:(AcceptTransactionsQuery*)query
                completion:(void (^)(NSArray*, NSError*))completion;

/**
 *  @brief Resetting the password of a user
 *  @param userId the unique user id
 *  @param config Instance needed to use backend services
 *  @param completion Block that will receive a boolean indicating the success or an error
 **/
- (void) resetPassword:(NSString*)userId
                config:(AcceptDataServiceConfig*)config
            completion:(void (^)(BOOL, NSError*))completion;

/**
 *  @brief Request for email with the userId on it
 *  @param email email address to receive the content
 *  @param config Instance needed to use backend services
 *  @param completion Block that will receive a boolean indicating the success or an error
 **/
- (void) forgotUserId:(NSString *)email
               config:(AcceptDataServiceConfig*)config
           completion:(void (^)(BOOL, NSError*))completion;

/**
 *  @brief Request for changing the password
 *  @param userToken The user session token for authentication
 *  @param newPassword The new password following the specs of the backend
 *  @param reNewPassword Confirmation for the password (second input of the same string to be accepted)
 *  @param config Instance needed to use backend services
 *  @param completion Block that will receive a boolean indicating the success or an error
 **/
- (void) changePasswordForToken:(NSString*)userToken
                    newPassword:(NSString*)newPassword
                  reNewPassword:(NSString*)reNewPassword
                         config:(AcceptDataServiceConfig*)config
                     completion:(void (^)(BOOL, NSError*))completion;

/**
 *  @brief Request of statistic data
 *  @param accessToken The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param from starting date of the statistic range (note: response will include automatically only dates after user's acount creation day)
 *  @param to end date of the statistic range
 *  @param groupBy option to group the data by type
 *  @param resultsGroup array of the grouped statistic data
 *  @param isNesting boolean indicating that we want a status dictionary (authorised, rejected, reversed, etc.) per each groupBy element. NO as default
 *  @param completion Block that will receive the rest of statistic data or an error
 **/
- (void) queryStatistics:(NSString*)accessToken
                  config:(AcceptDataServiceConfig*)config
                    from:(NSDate*)from to:(NSDate*)to
                 groupBy:(AcceptStatisticsGroupBy)groupBy
            resultsGroup:(NSArray *)resultsGroup
           statusNesting:(BOOL)isNesting
              completion:(void (^)(AcceptStatistics*, NSError*))completion;

/**
 *  @brief Request of one of the available operations: reverse, refund, or prepare a receipt for a payment
 *  @param paymentID Unique id of the transaction to apply the operation
 *  @param accessToken The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param operation enumerator indicating the operation to be applied
 *  @param paymentUpdateParameters Extra paramenters are needed in the case of the receipt: where to send it, email, phone number, etc
 *  @param completion Block that will receive the transaction as the result of the operation an error if it exists. NOTE: The success of the operation is calculated by comparing the current status of the transaction to the previous one.
 **/
- (void) requestOperationOnPaymentWithID:(NSString*)paymentID
                          andAccessToken:(NSString*)accessToken
                                  config:(AcceptDataServiceConfig*)config
                               operation:(AcceptOperationOnPayment)operation
                 paymentUpdateParameters:(AcceptPaymentParameters *)paymentUpdateParameters
                              completion:(void (^)(AcceptTransaction*, NSError*))completion;


/**
 *  @brief Request the battery level of the connected terminal. NOTE: this function should NOT be called if an operation in the terminal is ongoing (ie startPay has not finished)
 *  @param vendorID Unique id of the terminal's vendor we are requesting the info
 *  @param completionBlock Block that will receive the battery level as a signed integer. If negative, then it indicates an error between three possible cases: "-1" for showing that the selected terminalID is wrong or that the terminal does not support battery level info. "-2" for indicating that the terminal does not respond (not ready or not connected). "-3" for indicating that the terminal is currently charging through a cable.
 **/
- (void)percentageBatteryRemainingForTerminal:(NSString*)vendorID completion:(void (^)(NSInteger))completionBlock;
@end

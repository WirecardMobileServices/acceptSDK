//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//


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


/**
 *Current version of Accept SDK
 */
extern NSString * const ACCEPT_SDK_VERSION;

#define ENABLE_IDTECH   0
#define ENABLE_BBPOS    1
#define ENABLE_DATECS   0
#define ENABLE_SPIRE    1
#define ENABLE_VERIFONE 0
#define ENABLE_PRT_DATECS 1
#define ENABLE_MPOP 1

/**
 * Possible note texts (reasons) in transaction reversals
 */
extern NSString * const  SignatureVerificationTimeout;
/// Merchant rejected customer signature message
extern NSString * const  MerchantRejectedCustomerSignature;
/// Transaction declined by card message
extern NSString * const  TransactionDeclinedByCard;
/// Advice not supported message
extern NSString * const  AdviceNotSupported;
/// Capture not supported message
extern NSString * const  CaptureNotSupported;
/// No EFT response messsage
extern NSString * const  NoEFTResponse;
/// Transaction terminated by terminal message
extern NSString * const  TransactionTerminatedByTerminal;


/**
 *Current Vendors IDs supported by the SDK
 */
extern NSString * const AcceptSpireVendorUUID;
/// BBPOS vendor UUID
extern NSString * const AcceptbbPOSVendorUUID;
/// IDTECH  vendor UUID
extern NSString * const AcceptIDTECHVendorUUID;
/// Datecs vendor UUID
extern NSString * const AcceptDatecsVendorUUID;
/// Verifone vendor UUID
extern NSString * const AcceptVeriFoneVendorUUID;
/// Accept error domain
extern NSString * const AcceptErrorDomain;

/**
 *  @class AcceptTerminalVendor
 *  @discussion Terminal vendor class
 **/
@interface AcceptTerminalVendor : NSObject<NSCoding>

/// UUID
@property (nonatomic, strong) NSString * uuid;
/// Display Name
@property (nonatomic, strong) NSString * displayName;
/// Alternative display name
@property (nonatomic, strong) NSString * alternativeDisplayName;
@end

/**
 *  @class AcceptTerminal
 *  @discussion Terminal model class
 **/
@interface AcceptTerminal : NSObject<NSCoding>
/// UUID
@property (nonatomic, strong) NSString * uuid;
/// Display Name
@property (nonatomic, strong) NSString * displayName;
/// Alternative display name
@property (nonatomic, strong) NSString * alternativeDisplayName;
/// EAA Serial number
@property (nonatomic, strong) NSString *  eaaSerialNumber;
@end

/**
 *  @class AcceptPrinterVendor
 *  @discussion Printer vendor class
 **/
@interface AcceptPrinterVendor : NSObject<NSCoding>
/// UUID
@property (nonatomic, strong) NSString * uuid;
/// Display name
@property (nonatomic, strong) NSString * displayName;
/// Alternative display name
@property (nonatomic, strong) NSString * alternativeDisplayName;
@end

/**
 *  @class AcceptPrinter
 *  @discussion Printer model class
 **/
@interface AcceptPrinter : NSObject<NSCoding>
/// UUID
@property (nonatomic, strong) NSString * uuid;
/// Display name
@property (nonatomic, strong) NSString * displayName;
/// Alternative display name
@property (nonatomic, strong) NSString * alternativeDisplayName;
/// EAA serial number
@property (nonatomic, strong) NSString * eaaSerialNumber;
@end

/**
 *  @class AcceptPaymentConfigCore
 *  @discussion Payment configuration core class.
 **/
@interface AcceptPaymentConfigCore : NSObject
///
@property (nonatomic, strong) AcceptDataServiceConfig * backendConfig;
///
@property (nonatomic, strong) NSString * accessToken;
@end
/**
 *  @class AcceptPaymentConfig
 *  @discussion Payment configuration class. Content required to execute the payment flow
 **/
@interface AcceptPaymentConfig : AcceptPaymentConfigCore
/// Vendor UUID
@property (nonatomic, strong) NSString * vendorUUID;
/// EAA serial number
@property (nonatomic, strong) NSString * _Nonnull eaaSerialNumber;
/// Basket
@property (nonatomic, strong) AcceptBasket * basket;
/// Gratuity allowed
@property (nonatomic) BOOL allowGratuity;
/**
 * numeric data read from the Alipay barcode
 */
@property (nonatomic, strong,nullable) NSString * alipayConsumerId;
/// Transaction type
@property (nonatomic) AcceptTransactionType transactionType;
@end

/**
 *  @class AcceptSignatureRequest
 *  @discussion Signature request class. It should be given fulfilled once the signature image has been captured, to be included in the transaction body when required
 **/
@interface AcceptSignatureRequest: NSObject
/// Cardholder name
@property (nonatomic, strong) NSString *cardHolderName;
/// Card number
@property (nonatomic, strong) NSString *cardNumber;
/// Card type
@property (nonatomic, strong) NSString * cardType;
/// Issuer
@property (nonatomic, strong) NSString * issuer;
/// Masked PAN
@property (nonatomic, strong) NSString *maskedPAN;
/// Gratuity amount
@property (nonatomic) NSInteger gratuityAmount;
/// Signature collection callback
@property (nonatomic, copy) void(^signatureCallback)(UIImage*, NSError*);
@end

/**
 *  @class AcceptAppSelectionRequest
 *  @discussion Application selection request class. It should be given fulfilled once a prefered application has been chosen from the list (used in chip compatible terminals with no screen)
 **/
@interface AcceptAppSelectionRequest: NSObject
/// Card applications
@property (nonatomic, strong) NSArray *appsArray;
/// Card application selection callback
@property (nonatomic, copy) void(^appSelectionCallback)(NSUInteger, NSError*);
@end

/**
 *  @class AcceptPrinterConfig
 *  @discussion Printer configuration class. Receipt Content or Receipt Image required to execute the printing flow
 **/
@interface AcceptPrinterConfig : NSObject
/// Vendor UUID
@property (nonatomic, strong) NSString * vendorUUID;
/// Printer UUID
@property (nonatomic, strong) NSString * printerUUID;
/// Receipt data
@property (nonatomic, strong) AcceptReceipt *receipt;
/// Receipt Image
@property (nonatomic, strong) UIImage *receiptImage;
@end

/**
 *  @class AcceptExtensionConnectionStatus
 *  @discussion The terminal connection status enumerator
 **/
typedef NS_ENUM(NSInteger, AcceptExtensionConnectionStatus){
    AcceptExtensionConnectionStatusConnected,
    AcceptExtensionConnectionStatusDisconnected,
    AcceptExtensionConnectionStatusUnknown
};

/**
 *  @class SignatureVerificationResultCallback
 *  @discussion The callback to pass to startPay function with the result of Customer signature verification
 *  @param AcceptSignatureVerificationResult the result of the Merchant veryfying the customer signature
 **/
typedef void (^AcceptSignatureVerificationResultCallback)(AcceptSignatureVerificationResult);

/**
*  @class Accept
*  @discussion Main SDK class. It contains all public properties and functions
**/
@interface Accept : NSObject
///
///version Current SDK version
@property (nonatomic, readonly) NSString * version;



/**
 *  @brief Adquire an array of available terminal vendors
 *  @param completion The array of vendors found, returned with objects of class AcceptTerminal
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
                         andToken:(NSString*)token
                        andConfig:(AcceptDataServiceConfig*)config
                       completion:(void (^)(NSInteger, NSError*))completionAlertUI __deprecated_msg("Use updateTerminal:vendor:token:config:progess:completion");

/**
 *  @brief Update terminals for a vendor. Chip compatible terminals receive config files from backend; this function will decide if the updates are needed according current version
 *  @param terminal The terminal obtained using discoverTerminalsForVendor
 *  @param vendor The vendor obtained using discoverSupportedVendors
 *  @param token The user session token for authentication
 *  @param config Instance needed to use backend services - will use backend config from accept.conf if nil
 *  @param progress Progress of the config file update
 *  @param completion Block that receives the update status or error
 **/
- (void) updateTerminal:(AcceptTerminal * _Nonnull)terminal
                 vendor:(AcceptTerminalVendor*_Nonnull)vendor
                  token:(NSString*_Nonnull)token
                 config:(AcceptDataServiceConfig*)config
               progress:(void (^)(AcceptConfigFilesProgress))progress
             completion:(void (^)(AcceptConfigFilesStatus status, NSError* error))completion;


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
                    completion:(void (^)(NSInteger, NSError*))completionAlertUI; __deprecated_msg("Use updateTerminalFirmware:vendor:token:config:firmware:progess:completion");

/**
 *  @brief Update terminal's firmware . Chip compatible terminals receive firmware files from backend; this function will decide if the updates are needed according current version
 *  @param terminal The terminal obtained using discoverTerminalsForVendor
 *  @param vendor The vendor obtained using discoverSupportedVendors
 *  @param token The user session token for authentication
 *  @param config Instance needed to use backend services
 *  @param progress Progress of the config file update
 *  @param completion Block that receives the update status or error
 **/
- (void) updateTerminalFirmware:(AcceptTerminal * _Nonnull)terminal
                 vendor:(AcceptTerminalVendor*_Nonnull)vendor
                  token:(NSString*_Nonnull)token
                 config:(AcceptDataServiceConfig*)config
               progress:(void (^)(AcceptConfigFilesProgress))progress
             completion:(void (^)(AcceptConfigFilesStatus status, NSError* error))completion;


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
signatureVerification:(void (^)(AcceptTransaction*,AcceptSignatureVerificationResultCallback , NSError*))signatureVerification
     appSelection:(void (^)(AcceptAppSelectionRequest *))appSelection;

/**
 *  @brief Start the Cash payment process
 *  @param config Instance needed to use backend services
 *  @param completion Block that will be called at the very end of payment flow. It provides an AcceptTransaction object (that may be nil if unauthorised) or a descriptive error
 *  @param progress Block with info to update the UI in base of alerts, errors or general info messages. Pure feedback for the user
 **/
- (void) startCashPayment:(AcceptPaymentConfig*)config
               completion:(void (^)(AcceptTransaction*, NSError*))completion
                 progress:(void (^)(AcceptStateUpdate))progress;

/**
 *  @brief Start the Alipay payment process
 *  @param config Instance needed to use backend services
 *  @param completion Block that will be called at the very end of payment flow. It provides an AcceptTransaction object (that may be nil if unauthorised) or a descriptive error
 *  @param progress Block with info to update the UI in base of alerts, errors or general info messages. Pure feedback for the user
 **/
- (void) startAlipayPayment:(AcceptPaymentConfig*)config
                 completion:(void (^)(AcceptTransaction*, NSError*))completion
                   progress:(void (^)(AcceptStateUpdate))progress;

/**
 *  @brief Used in Austria - Ministry of Finance requirement to record  all transactions of the merchant if merchant is registered with A-Trust
 *  to be called if merchant agrees to MOF T&Cs and merchantUser.rksvReady = true and merchantUser.rksvInitiated=false
 *  @param config Instance needed to use backend services - it is only necessary to set the backendConfig, access token and
 *   currency as ISO4217 Code set
 *  @param completion Block that will be called at the very end of payment flow. It provides an AcceptTransaction object (that may be nil if unauthorised) or a descriptive error
 *  @param progress Block with info to update the UI in base of alerts, errors or general info messages. Pure feedback for the user
 *
 **/
- (void) startTransactionsRecording:(AcceptPaymentConfigCore*)config
                     currency:(NSString*)currency
               completion:(void (^)(AcceptTransaction*, NSError*))completion;

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

/**
 *  @brief Request the terminal connection status. NOTE: this function should NOT be called if an operation in the terminal is ongoing (ie startPay has not finished)
 *  @param vendorID Unique id of the terminal's vendor we are requesting the info
 *  @param completionBlock Block that will receive the terminal connection status.
 **/
- (void)terminalConnectionStatus:(NSString*)vendorID completion:(void (^)(AcceptExtensionConnectionStatus))completionBlock __deprecated_msg("Use connectionStatus:completion");;

/**
 *  @brief Request the connection status of the specified terminal/device
 *  @param terminal terminal  we are requesting the info
 *  @param completion Block that will receive connection status of the terminal/device
 **/
- (void)connectionStatus:(AcceptTerminal*)terminal
                  vendor:(AcceptTerminalVendor*)vendor
              completion:(void (^)(AcceptExtensionConnectionStatus))completion;

/**
 *  @brief List the backends from the Accept configuration file
 **/
-(NSArray *)getSupportedBackends;

/**
 * @brief Opens cash drawer for supported printers (ie StarIO mPOP)
 * @param config Instance needed to use the device
 * @param completion block with the result as BOOL (YES for success) and an error if exists
 **/
- (void) openCashDrawer:(AcceptPrinterConfig*)config
             completion:(void (^)(BOOL, NSError*))completion;

/**
 * @brief Connects bascode scanner for supported printers (ie StarIO mPOP)
 * @param config Instance needed to use the device
 * @param completion block with the result as BOOL (YES for success when connecting) and an error if exists
* @param block that will be called each time the barcode reader gets some data, returning it
 **/
- (void) connectBarcodeScanner:(AcceptPrinterConfig*)config
                    completion:(void (^)(BOOL, NSError*))completion
               andDataReceived:(void (^)(NSData*))barcodeDataReceived;

@end

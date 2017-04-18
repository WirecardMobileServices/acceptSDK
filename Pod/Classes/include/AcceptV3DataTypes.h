//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//


#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  @class AcceptStateUpdate
 *  @discussion Enumerator of statuses for informing the flow status or asking feedback to the user, received in the progress block of startPay function.
 **/
typedef NS_ENUM(NSInteger, AcceptStateUpdate ) {
    AcceptStateWaitingForPlugIn = 0,
    AcceptStateWaitingForSwipe,
    AcceptStateDamagedChipAndWaitingForSwipe,
    AcceptStateProcessingData,
    AcceptStateOnlineProcessingData,
    AcceptStateFollowTerminalInstructions,
    AcceptStateInitialize,
    AcceptStateTerminalConfigOngoing,
    AcceptStateInsertOrSwipeCard,
    AcceptStateTapOrInsertOrSwipeCard,
    AcceptStateWaitingForInsertCard,
    AcceptStateCheckingCard,
    AcceptStateRemoveCard,
    AcceptStateCardRemoved,
    AcceptStateConfirmAmount,
    AcceptStateAmountConfirmed,
    AcceptStatePINEntered,
    AcceptStateCorrectPIN, //deprecated
    AcceptStatePINEntryLastTry,
    AcceptStateAskingForPIN,
    AcceptStatePinEntryWrong, //deprecated
    AcceptStateCardholderSignatureCheck,
    AcceptStateTerminalRestarting,
    AcceptStateGratuityEntryStarted,
    AcceptStateApplicationSelectionStarted,
    AcceptStateApplicationSelectionFinished,
    AcceptStateFollowInstructionsOnConsumerDevice, //on device CVM for contactless
    AcceptStateOnlineATrustWait
};

/**
 *  @class AcceptPayErrorCode
 *  @discussion Enumerator of error codes received in the completion block of startPay function.
 **/
typedef NS_ENUM(NSInteger, AcceptPayErrorCode) {
    AcceptPlugInTimeoutErrorCode = 0,
    AcceptSignatureTimeoutErrorCode,
    AcceptInitializationErrorCode,
    AcceptLowBatteryLevelErrorCode,
    AcceptSwipeTimeoutError,
    AcceptBadSwipeError,
    AcceptNotSupportedCardTypeErrorCode,
    AcceptDataProcessingErrorCode,
    AcceptOnlineProcessingErrorCode,
    AcceptTransactionNotApprovedErrorCode,
    AcceptHardwareAccessPermissionErrorCode,
    AcceptTokenExpiredErrorCode,
    AcceptPayConnectionErrorCode,
    AcceptSignatureRequestErrorCode,
    AcceptCantLoadTerminalConfiguration,
    AcceptCantLoadSwiperTerminalConfiguration,
    AcceptTerminalDamagedError,
    AcceptNoDUKPTError,
    AcceptFailedToStartEMVError,
    AcceptFailedToSendOfflineEMVError,
    AcceptFailedToSendOnlineEMVError,
    AcceptTerminalNotSetInMerchantError,
    AcceptResponseLostErrorCode,
    AcceptTransactionTerminatedErrorCode,
    AcceptTransactionDeclinedErrorCode,
    AcceptBlockedCardTypeErrorCode,
    AcceptFailedBluetoothConnectionError,
    AcceptTerminalNotReady,
    AcceptTerminalTimeoutApplicationSelection,
    AcceptTerminalFailedToGetICCApplicationsList,
    AcceptTerminalFailedToTerminateCurrentTerminalPaymentFlow,
    AcceptLowPowerInAudioJackErrorCode,
    AcceptMonoAudioEnabledErrorCode,
    AcceptTerminalCommandTimeOutErrorCode,
    AcceptTerminalTimeOutErrorCode,
    AcceptDeviceRootedErrorCode
} ;

/**
 *  @class AcceptTransactionsQueryErrorCode
 *  @discussion Enumerator of errors when trying to do a transaction request, this is, using the function queryTransactions.
 **/
typedef NS_ENUM(NSInteger, AcceptCommonErrorCode) {
    AcceptUnsupportedFeature = -1000,
    AcceptTransactionsQueryTokenExpiredErrorCode = 0,
    AcceptTransactionsQueryNoConnectionErrorCode,
    AcceptWrongUserNameOrPasswordErrorCode,
    AcceptRequestTokenConnectionErrorCode,
    AcceptRequestMerchantInfoTokenExpiredErrorCode,
    AcceptRequestMerchantInfoNoConnectionErrorCode,
    AcceptVendorNotFoundError,
    AcceptApplicationConfigurationInvalid,               // some extensions requires additional configuration changes in host application .plist file.
    AcceptResetPasswordConnectionErrorCode,         // no internet connection
    AcceptExternalIdNotFoundErrorCode,                   // there is no user/merchant with given external id. ( HTTP 422 )
    AcceptChangePasswordCriteriaNotMet,                  //password change criteria not met
    AcceptQueryStatsTokenExpiredErrorCode,
    AcceptQueryStatsConnectionErrorCode,
    AcceptForgotExternalIdConnectionErrorCode,      // no internet connection
    AcceptForgotExternalIdNotFoundErrorCode = 14,             // there is no user/merchant with given email address. ( HTTP 422 )
    AcceptGenericRequestTimeoutErrorCode = 1001         // connection timeout
};


/**
 *  @class AcceptConfigFilesInfoErrorCode
 *  @discussion Enumerator of errors when trying to request, download, unzip and install config files in a terminal that requires it (chip compatible devices).
 **/
typedef NS_ENUM(NSInteger, AcceptConfigFilesInfoErrorCode) {
    AcceptConfigFilesUnsupportedFeature = -1000,
    AcceptConfigFilesInfoTimeoutErrorCode = 0,
    AcceptConfigFilesInfoNoConnectionErrorCode,         // no internet connection
    AcceptConfigFilesInfoNoProperResponseErrorCode,      //if backend did not response with version and url
    AcceptConfigFilesZipDownloadErrorCode,
    AcceptConfigFilesTerminalDisconnectedErrorCode,
    AcceptConfigFilesTerminalMayNotBeSetErrorCode,
    AcceptConfigFilesTerminalCancelledFileDownload,
    AcceptConfigFilesProductionFirmwareOnDevelopmentTerminal,
    AcceptConfigFilesDevelopmentFirmwareOnProductionTerminal,
    AcceptConfigFilesTerminalUnsupported,
    AcceptConfigFilesTokenExpiredErrorCode,
    AcceptConfigFilesInfoNoDataErrorCode,
    AcceptConfigFilesTerminalFirmwareDoesNotExist
};

/**
 *  @class AcceptSignatureResultBlock
 *  @discussion Block type for giving the signature image captured after it was requested with signatureBlock of startPay.
 **/
typedef void (^AcceptSignatureResultBlock)(UIImage*, NSError*);

/**
 *  @class AcceptTaxationType
 *  @discussion Enumerator with the taxation types.
 **/
typedef NS_ENUM(NSInteger, AcceptTaxationType ) {
    AcceptTaxationTypeGross = 0,
    AcceptTaxationTypeNet = 1
};

/**
 *  @class AcceptConfigFilesUIAlerts
 *  @discussion Enumerator with the status during an config file update in terminal. Values will be send to the block completionAlertUI in function updateTerminalsForVendor.
 **/
typedef NS_ENUM(NSInteger, AcceptConfigFilesUIAlerts) {
    AcceptConfigFilesTerminalNotReady = -1,
    AcceptConfigFilesUpdateWillStart,
    AcceptConfigFilesDownloading,
    AcceptConfigFilesUnzipping,
    AcceptConfigFilesUploading,
    AcceptConfigFilesSuccess,
    AcceptConfigFilesUnnecessary,
    AcceptConfigFilesDeferredInstall
} ;

/**
 *  @class AcceptConfigFilesProgress
 *  @discussion Enumerator with the progress  during an config file update in terminal
 **/
typedef NS_ENUM(NSInteger, AcceptConfigFilesProgress) {
    AcceptConfigFilesProgressUpdateWillStart,
    AcceptConfigFilesProgressDownloading,
    AcceptConfigFilesProgressUnzipping,
    AcceptConfigFilesProgressUploading
} ;

/**
 *  @class AcceptConfigFilesStatus
 *  @discussion Enumerator with the status at the end of the config file update in terminal.
 **/
typedef NS_ENUM(NSInteger, AcceptConfigFilesStatus) {
    AcceptConfigFilesStatusOnlineError = -2,
    AcceptConfigFilesStatusTerminalNotReady = -1,
    AcceptConfigFilesStatusSuccess=0,
    AcceptConfigFilesStatusUnnecessary,
    AcceptConfigFilesStatusDeferredInstall
} ;

/**
 *  @class AcceptInventoryUIAlerts
 *  @discussion Enumerator with the status during an inventory file update in terminal. Values will be send to the block completionAlertUI in function getInventoryData.
 **/
typedef NS_ENUM(NSInteger, AcceptInventoryUIAlerts) {
    AcceptInventoryProcessFailure = -1,
    AcceptInventoryUpdateWillStart,
    AcceptInventoryDownloading,
    AcceptInventoryUnzipping,
    AcceptInventoryUploading,
    AcceptInventorySuccess,
    AcceptInventoryUnnecessary,
    AcceptInventoryDeferredInstall
} ;

/**
 *  @class AcceptOperationOnPayment
 *  @discussion Enumerator with the status we wish to send an existing transaction. Used in the function requestOperationOnPaymentWithID
 **/
typedef NS_ENUM(NSInteger, AcceptOperationOnPayment)
{
    AcceptOperationOnPaymentRefund = 0,
    AcceptOperationOnPaymentReverse = 1,
    AcceptOperationOnPaymentReceipt = 3, //a receipt will be requested; the transaction won't be modified
    AcceptOperationOnPaymentConfirmResponseReceived = 4,
    AcceptOperationOnPaymentSignatureUpdate = 5, //SPm2 send signature AFTER completion in contactless flow
    AcceptOperationOnPaymentCapture =6 //For Authorized or Preauthorized transactions
};

/**
 *  @class AcceptStatisticsGroupBy
 *  @discussion Enumerator with the groupBy mode for statistics. Note that the keys in the JSON response are affected (yyyy/MM/dd, yyyy/MM, yyyy or even yyyy/QN for quarters, being Q1-Q4 the range of values). Used in function queryStatistics.
 **/
typedef NS_ENUM(NSInteger, AcceptStatisticsGroupBy)
{
    AcceptStatisticsGroupByDay = 1,
    AcceptStatisticsGroupByWeek ,
    AcceptStatisticsGroupByMonth,
    AcceptStatisticsGroupByQuarter,
    AcceptStatisticsGroupByYear
};

/**
 *  @class AcceptStatisticsOnly
 *  @discussion Enumerator with the statuses we want to include in the statistics request, (range from 0 to all of them). If non is provided, turnover is returned as default. Used in function queryStatistics.
 **/
typedef NS_ENUM(NSInteger, AcceptStatisticsOnly)
{
    AcceptStatisticsOnlyStatuses = 0,
    AcceptStatisticsOnlyCount ,
    AcceptStatisticsOnlyAverage,
    AcceptStatisticsOnlyTurnover,
    AcceptStatisticsOnlyMaxMin,
    AcceptStatisticsOnlySum
};

/**
 *  @class AcceptPrinterStateUpdate
 *  @discussion Enumerator with the statuses of the printing flow, received in progress block of startPrint.
 **/
typedef NS_ENUM(NSInteger, AcceptPrinterStateUpdate ) {
    AcceptPrinterStateInitialize = 0,
    AcceptPrinterStateConnecting,
    AcceptPrinterStateConnected,
    AcceptPrinterStatePrint,
    AcceptPrinterStateFinish
};

/**
 *  @class AcceptPrintErrorCode
 *  @discussion Enumerator with the errors of printing flow, received in completion block of startPrint.
 **/
typedef NS_ENUM(NSInteger, AcceptPrintErrorCode) {
    AcceptPrinterTimeoutErrorCode = 0,
    AcceptPrinterInitializationErrorCode,
    AcceptPrinterLowBatteryLevelErrorCode,
    AcceptPrinterConnectionErrorCode,
    AcceptPrinterNotConnectedErrorCode,
    AcceptPrinterOperationErrorCode,
    AcceptPrinterUnsupportedDeviceErrorCode
} ;

/**
 *  @class AcceptReversalReason
 *  @discussion Enumerator with the reversal reasons
 **/
typedef NS_ENUM(NSInteger, AcceptReversalReason)
{   AcceptReversalReasonUndefined = -1,
    AcceptReversalReasonSignatureDeclined = 0,
    AcceptReversalReasonAdviceUnsupported = 1,
    AcceptReversalReasonCardDeclined=2,
    AcceptReversalReasonCaptureUnsupported=4,
    AcceptReversalReasonNoEFTResponse = 6,
    AcceptReversalReasonTerminalTerminated=7,
    AcceptReversalReasonSignatureVerificationTimeout = 10,
    AcceptReversalReasonOfflineDeclined = 11
};

/**
 *  @class AcceptSignatureVerificationResult
 *  @discussion Enumerator with the result of the merchant verification
 **/
typedef NS_ENUM(NSInteger, AcceptSignatureVerificationResult)
{
    AcceptSignatureVerificationResultNotDefined = 0,
    AcceptSignatureVerificationResultApproved = 1,
    AcceptSignatureVerificationResultRejected = 2
};

/**
 *  @class AcceptV3DataTypes
 *  @discussion Standard class of types for backend version 3.
 **/
@interface AcceptV3DataTypes : NSObject

/**
 *  @brief Just of a translator of enumerator to string
 *  @param groupBy enum value to translate
 *  @return String equivalent to enum value name. Example: integer 1 equivalent to "day"
 **/
+ (NSString *)statisticsGroupByType:(AcceptStatisticsGroupBy)groupBy;

/**
 *  @brief Just of a translator of enumerator to string
 *  @param statisticsResultsGroup enum value to translate
 *  @return String equivalent to enum value name. Example: integer 1 equivalent to "turnover"
 **/
+ (NSArray *)statisticsOnlyType:(NSArray *)statisticsResultsGroup;
@end

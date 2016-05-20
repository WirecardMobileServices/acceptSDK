//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kAcceptTransactionStatus_Approved         @"approved"
#define kAcceptTransactionStatus_Pending          @"pending"
#define kAcceptTransactionStatus_Refunded         @"refunded"
#define kAcceptTransactionStatus_Rejected         @"rejected"
#define kAcceptTransactionStatus_Reversed         @"reversed"
#define kAcceptTransactionStatus_New              @"new"
#define kAcceptTransactionStatus_Authorized       @"preauthorized"
#define kAcceptTransactionStatus_Preauthorized    @"preauthorized"
#define kAcceptTransactionStatus_Bookbacked       @"bookbacked"
#define kAcceptTransactionStatus_Chargebacked     @"chargebacked"
#define kAcceptTransactionStatus_Canceled         @"canceled"


#define kTransactionReversalRequired @"Transaction reversal required"
#define kTransactionReversedByTerminal @"Transaction reversed by terminal"
#define kTransactionReversalFailed @"Transaction reversal failed"
#define kSignatureRejectedByTerminal @"Merchant rejected customer signature"
#define kTransactionUpdateFailed @"Transaction update failed"
#define kTransactionUpdateFailedPrevApproved @"Transaction update failed, prev approved"
#define kTransactionUpdateFailedPrevFailed @"Transaction update failed, prev failed"
#define kValidAppDataFailed @"Can't find valid Transaction And Application data"
#define kTransactionRejected @"Transaction declined"
#define kDeviceRootedError @"Transactions cannot be run on rooted device"

typedef NS_ENUM(NSUInteger, AcceptTransactionState) {
    AcceptTransactionStateApproved,
    AcceptTransactionStateDeclined,
    AcceptTransactionStateReversed,
    AcceptTransactionStateRefunded,
    AcceptTransactionStatePending,
    AcceptTransactionStateAuthorized,
    AcceptTransactionStatePreauthorized
};

typedef NS_ENUM(NSInteger,AcceptTransactionType) {
    AcceptTransactionTypePurchase = 0,
    AcceptTransactionTypeAuthorize,
    AcceptTransactionTypePreauthorize,
    AcceptTransactionTypeSEPA

};

/**
 *  @class AcceptTransactionPaymentItem
 *  @discussion Basic Payment item info
 **/
@interface AcceptTransactionPaymentItem : NSObject
/**
 */
@property (nonatomic) NSInteger paymentId;
/**
 */
@property (nonatomic, strong) NSString* createdAt;
/**
 */
@property (nonatomic, strong) NSString* updatedAt;
/**
 */
@property (nonatomic) NSInteger id_;
/**
 */
@property (nonatomic, strong) NSString* note;
/**
 */
@property (nonatomic, strong) NSString* taxRate;
/**
 */
@property (nonatomic, strong) NSString* paymentRequestId;
/**
 */
@property (nonatomic) NSInteger price;
/**
 */
@property (nonatomic) NSInteger quantity;
@end

/**
 *  @class AcceptTransactionSignatureSmall
 *  @discussion Basic signature info
 **/
@interface AcceptTransactionSignatureSmall : NSObject
/**
 */
@property (nonatomic, strong) NSString* url;
@end

/**
 *  @class AcceptTransactionSignature
 *  @discussion Complete signature info
 **/
@interface AcceptTransactionSignature : NSObject
/**
 */
@property (nonatomic, strong) NSString* url;
/**
 */
@property (nonatomic, strong) AcceptTransactionSignatureSmall* small;
@end


/**
 *  @class AcceptTransactionVoidance
 *  @discussion Reversal or Refund details
 **/
@interface AcceptTransactionVoidance : NSObject
/**
 */
@property (nonatomic, strong) NSString* note;
/**
 */
@property (nonatomic, strong) NSString* triggeredBy;
/**
 */
@property (nonatomic, strong) NSString* createdAtUTC;

@end

/**
 *  @class AcceptReceiptTaxSummaryItem
 *  @discussion Receipt Item data
 **/
@interface AcceptReceiptItem : NSObject

/**
 */
@property (nonatomic, strong) NSDecimalNumber  *itemQuantity;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *itemGrossPrice;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *itemTaxRate;
/**
 */
@property (nonatomic, strong) NSString  *itemDescription;
/**
 */
@property (nonatomic, strong) NSString  *currency;
/**
 */
@property (nonatomic ) BOOL inclusiveTax;
/**
 * @discussion Calculated Item Netto price
 */
-(NSDecimalNumber  *)itemNettoPrice;
/**
 * @discussion Calculated Item Tax Amount
 */
-(NSDecimalNumber  *)itemTaxAmount;
/**
 * @discussion Calculated Netto price
 */
-(NSDecimalNumber *)totalNetto;
/**
 * @discussion Calculated Gross price
 */
-(NSDecimalNumber *)totalGross;
/**
 * @discussion Calculated Tax Amount
 */
-(NSDecimalNumber *)totalTaxAmount;
@end

/**
 *  @class AcceptReceiptTaxSummaryItem
 *  @discussion Receipt Item Tax Summary data
 **/
@interface AcceptReceiptTaxSummary : NSObject
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *totalNetto;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *totalQuantity;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *totalGross;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *taxRate;
/**
 */
@property (nonatomic, strong) NSDecimalNumber  *totalTaxAmount;
/**
 */
@property (nonatomic, strong) NSString  *itemDescription;
@end

/**
 *  @class AcceptReceiptData
 *  @discussion Complete Receipt Data
 **/
@interface AcceptReceiptData : NSObject
/**
 */
@property (nonatomic, strong) NSArray  *receiptItems;
/**
 */
@property (nonatomic, strong) NSArray  *taxSummaryItems;
/**
 */
@property (nonatomic) BOOL  inclusiveTax;
/**
 */
@property (nonatomic, strong) AcceptReceiptItem  *serviceChargeItem;
/**
 */
@property (nonatomic, strong) AcceptReceiptItem  *tipItem;
/**
 */
@property (nonatomic, strong) NSDate  *utcPaymentDate;
/**
 */
@property (nonatomic) NSDecimalNumber *totalAmount;
/**
 */
@property (nonatomic) AcceptTransactionState transactionState;
/**
 */
@property (nonatomic) NSString * maskedCardNumber;
/**
 */
@property (nonatomic) NSString * cardholderName;
/**
 */
@property (nonatomic) NSString * cardType;
/**
 */
@property (nonatomic) NSString * emvAID;
/**
 */
@property (nonatomic) NSString * emvTID;
/**
 */
@property (nonatomic) NSString * emvMID;
/**
 */
@property (nonatomic) NSString * emvTransactionType;
/**
 */
@property (nonatomic) NSInteger receiptID;
/**
 */
@property (nonatomic) NSString * currencyCode;
/**
 */
@property (nonatomic) NSInteger currencyMinorUnits;
/**
 */
@property (nonatomic) NSString * approvalCode;
/**
 */
@property (nonatomic) NSString * transactionCertificate; //all emv tags
/**
 */
@property (nonatomic) NSString * technicalMessage;
/**
 */
@property (nonatomic) NSString * posEntryMode;
/**
 */
@property (nonatomic) NSString * issuerScript;
/**
 */
@property (nonatomic) NSString * emvTVR;
/**
 * @discussion Receipt data stringified to print out in the console
 */
-(NSString *)receiptDescription;
@end

/**
 *  @class AcceptTransaction
 *  @discussion Complete Payment item info
 **/
@interface AcceptTransaction : NSObject
/**
 */
@property (nonatomic, strong) NSString* tipTaxRate;
/**
 */
@property (nonatomic, strong) NSString* guwid;
/**
 */
@property (nonatomic, strong) NSString* gatewaySignature;
/**
 */
@property (nonatomic, strong) NSString* cnpTransactionCertificate;
/**
 */
@property (nonatomic) BOOL receiptRequested;
/**
 */
@property (nonatomic) BOOL taxHidden;
/**
 */
@property (nonatomic, strong) NSString* currency;
/**
 */
@property (nonatomic, strong) NSString* deviceType;
/**
 */
@property (nonatomic) BOOL gatewayLive;
/**
 */
@property (nonatomic, strong) NSString* processedAt;
/**
 */
@property (nonatomic, strong) NSString* cardHolderLastName;
/**
 */
@property (nonatomic, strong) NSString* lng;
/**
 */
@property (nonatomic, strong) NSString* additionalInfo;
/**
 */
@property (nonatomic) BOOL serviceChargeHidden;
/**
 */
@property (nonatomic, strong) NSString* technicalMessage;
/**
 */
@property (nonatomic, strong) NSString* note;
/**
 */
@property (nonatomic, strong) NSString* cnpApplicationId;
/**
 */
@property (nonatomic) BOOL emailReceipt;
/**
 */
@property (nonatomic) NSInteger txNumber;
/**
 */
@property (nonatomic, strong) NSString* gratuityType;
/**
 */
@property (nonatomic) NSInteger tip;
/**
 */
@property (nonatomic) NSInteger countryCode;
/**
 */
@property (nonatomic, strong) NSString* cardHolderFirstName;
/**
 */
@property (nonatomic, strong) NSString* state;
/**
 */
@property (nonatomic, strong) NSString* location;
/**
 */
@property (nonatomic) BOOL refundable;
/**
 */
@property (nonatomic, strong) NSString* gatewayLogin;
/**
 */
@property (nonatomic, strong) NSString* cnpTvr;
/**
 */
@property (nonatomic, strong) NSString* type;
/**
 */
@property (nonatomic, strong) NSString* status;
/**
 */
@property (nonatomic, strong) NSString* bankCode;
/**
 */
@property (nonatomic) NSInteger tax;
/**
 */
@property (nonatomic, strong) NSString* cnpIssuerResponseCode;
/**
 */
@property (nonatomic, strong) NSString* cnpAuthorizationNumber;
/**
 */
@property (nonatomic, strong) NSString* cnpAuthorizationCode;
/**
 */
@property (nonatomic, strong) NSString* cnpMerchantId;
/**
 */
@property (nonatomic, strong) NSString* emvTransactionType;
/**
 */
@property (nonatomic) BOOL expectsTC;
/**
 */
@property (nonatomic) BOOL capturable;
/**
 */
@property (nonatomic) BOOL reversible;
/**
 */
@property (nonatomic, strong) NSString* referenceId;
/**
 */
@property (nonatomic, strong) NSString* gatewayPassword;
/**
 */
@property (nonatomic, strong) NSString* lat;
/**
 */
@property (nonatomic) NSInteger merchantId;
/**
 */
@property (nonatomic, strong) NSString* cnpApplicationLabel;
/**
 */
@property (nonatomic, strong) NSArray* items;
/**
 */
@property (nonatomic, strong) NSString* createdAt;
/**
 */
@property (nonatomic, strong) NSString* transactionType;
/**
 */
@property (nonatomic, strong) NSString* cardType;
/**
 */
@property (nonatomic) NSInteger amount;
/**
 */
@property (nonatomic, strong) NSString* cnpTsi;
/**
 */
@property (nonatomic, strong) NSString* uniqueId;
/**
 */
@property (nonatomic, strong) AcceptTransactionSignature* signature;
/**
 */
@property (nonatomic, strong) NSArray* refunds;
/**
 */
@property (nonatomic, strong) NSArray* reversals;

/**
 */
@property (nonatomic, strong) NSString* errorCode;
/**
 */
@property (nonatomic, strong) NSString* cardNumber;
/**
 */
@property (nonatomic) NSInteger serviceChargeAmount;
/**
 */
@property (nonatomic) NSDecimalNumber *serviceChargeTaxRate;
/**
 */
@property (nonatomic, strong) NSString* cnpTerminalId;
/**
 */
@property (nonatomic, strong) NSString* issuerScript;
/**
 */
@property (nonatomic) BOOL netTaxation;
/**
 */
@property (nonatomic, strong) NSString* posEntryMode;
/**
 */
@property (nonatomic, strong) NSDictionary* customFields;
/**
 */
@property (nonatomic) NSDecimalNumber *discount;
/**
 * @discussion Get the receipt data from this transaction
 */
-(AcceptReceiptData *)getAcceptReceiptData;

@end



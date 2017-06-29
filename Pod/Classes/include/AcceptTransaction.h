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
#define kAcceptTransactionStatus_Authorized       @"authorized"
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
#define kTransactionFailed @"Transaction failed"
#define kDeviceRootedError @"Transactions cannot be run on rooted device"

/**
 * @class Transaction status enum
 * @discussion used to report the transaction status
 **/
typedef NS_ENUM(NSUInteger, AcceptTransactionState) {
    AcceptTransactionStateApproved,
    AcceptTransactionStateDeclined,
    AcceptTransactionStateReversed,
    AcceptTransactionStateRefunded,
    AcceptTransactionStatePending,
    AcceptTransactionStateAuthorized,
    AcceptTransactionStatePreauthorized
};

/**
 * @class Transaction type enum
 * @discussion used to create the transaction with appropriate type
 **/
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
/// Payment ID
@property (nonatomic) NSInteger paymentId;
/// Created timestamp
@property (nonatomic, strong) NSString* createdAt;
/// Updated timestamp
@property (nonatomic, strong) NSString* updatedAt;
/// internal ID
@property (nonatomic) NSInteger id_;
/// Payment note
@property (nonatomic, strong) NSString* note;
/// Tax rate
@property (nonatomic, strong) NSString* taxRate;
/// Request ID
@property (nonatomic, strong) NSString* paymentRequestId;
/// Unit Price
@property (nonatomic) NSDecimalNumber* price;
/// Quantity
@property (nonatomic) NSInteger quantity;
@end

/**
 *  @class AcceptTransactionSignatureSmall
 *  @discussion Basic signature info
 **/
@interface AcceptTransactionSignatureSmall : NSObject
/// URL of the signature
@property (nonatomic, strong) NSString* url;
@end

/**
 *  @class AcceptTransactionSignature
 *  @discussion Complete signature info
 **/
@interface AcceptTransactionSignature : NSObject
/// URL of a signature - large resolution
@property (nonatomic, strong) NSString* url;
/// Signature thumbnail
@property (nonatomic, strong) AcceptTransactionSignatureSmall* small;
@end


/**
 *  @class AcceptTransactionVoidance
 *  @discussion Reversal or Refund details
 **/
@interface AcceptTransactionVoidance : NSObject
/// Transaction Voidance note
@property (nonatomic, strong) NSString* note;
/// Voidance triggered by
@property (nonatomic, strong) NSString* triggeredBy;
/// Created at
@property (nonatomic, strong) NSString* createdAtUTC;

@end

/**
 *  @class AcceptReceiptTaxSummaryItem
 *  @discussion Receipt Item data
 **/
@interface AcceptReceiptItem : NSObject

/// Item quantity
@property (nonatomic, strong) NSDecimalNumber  *itemQuantity;
/// Item gross price
@property (nonatomic, strong) NSDecimalNumber  *itemGrossPrice;
/// Item tax rate
@property (nonatomic, strong) NSDecimalNumber  *itemTaxRate;
/// Item description
@property (nonatomic, strong) NSString  *itemDescription;
/// Currency
@property (nonatomic, strong) NSString  *currency;
/// Inclusive tax
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
/// Total Netto
@property (nonatomic, strong) NSDecimalNumber  *totalNetto;
/// Total Quantity
@property (nonatomic, strong) NSDecimalNumber  *totalQuantity;
/// Total Gross
@property (nonatomic, strong) NSDecimalNumber  *totalGross;
/// Tax rate
@property (nonatomic, strong) NSDecimalNumber  *taxRate;
/// Total tax amount
@property (nonatomic, strong) NSDecimalNumber  *totalTaxAmount;
/// Item summary description
@property (nonatomic, strong) NSString  *itemDescription;
@end

/**
 *  @class AcceptReceiptData
 *  @discussion Complete Receipt Data
 **/
@interface AcceptReceiptData : NSObject
/// Receipt items
@property (nonatomic, strong) NSArray  *receiptItems;
/// Tax summary items
@property (nonatomic, strong) NSArray  *taxSummaryItems;
/// tax inslusive
@property (nonatomic) BOOL  inclusiveTax;
/// Service charge
@property (nonatomic, strong) AcceptReceiptItem  *serviceChargeItem;
/// Gratuity
@property (nonatomic, strong) AcceptReceiptItem  *tipItem;
/// Payment date
@property (nonatomic, strong) NSDate  *utcPaymentDate;
/// Total amount
@property (nonatomic) NSDecimalNumber *totalAmount;
/// Transaction status
@property (nonatomic) AcceptTransactionState transactionState;
/// Masked card number
@property (nonatomic) NSString * maskedCardNumber;
/// Cardholder name
@property (nonatomic) NSString * cardholderName;
/// Card type
@property (nonatomic) NSString * cardType;
/// AID
@property (nonatomic) NSString * emvAID;
/// TID
@property (nonatomic) NSString * emvTID;
/// MID
@property (nonatomic) NSString * emvMID;
/// Transaction type
@property (nonatomic) NSString * emvTransactionType;
/// Receipt ID
@property (nonatomic) NSInteger receiptID;
/// Currency
@property (nonatomic) NSString * currencyCode;
/// Currency Minor units
@property (nonatomic) NSInteger currencyMinorUnits;
/// Approval code
@property (nonatomic) NSString * approvalCode;
/// EMV data
@property (nonatomic) NSString * transactionCertificate; //all emv tags
/// technical message
@property (nonatomic) NSString * technicalMessage;
/// POS entry mode
@property (nonatomic) NSString * posEntryMode;
/// Issuer script
@property (nonatomic) NSString * issuerScript;
/// TVR
@property (nonatomic) NSString * emvTVR;
/**
 * @discussion Receipt data stringified to print out in the console
 */
-(NSString *)receiptDescription;
@end


/**
 *  @class AcceptSubMerchant
 *  @discussion Sub Merchant data
 **/
@interface AcceptSubMerchant : NSObject
/// Sub Merchant ID
@property (nonatomic, strong) NSString  *subMerchantId;
///
@property (nonatomic, strong) NSString  *name;
///
@property (nonatomic, strong) NSString  *country;
///
@property (nonatomic, strong) NSString  *state;
///
@property (nonatomic, strong) NSString  *city;
///
@property (nonatomic, strong) NSString  *street;
///
@property (nonatomic, strong) NSString  *postalCode;
@end

/**
 *  @class AcceptTransaction
 *  @discussion Complete Payment item info
 **/
@interface AcceptTransaction : NSObject
/// Tip tax rate
@property (nonatomic, strong) NSString* tipTaxRate;
/// GUWID
@property (nonatomic, strong) NSString* guwid;
/// gateway signature
@property (nonatomic, strong) NSString* gatewaySignature;
/// EMV data
@property (nonatomic, strong) NSString* cnpTransactionCertificate;
/// Receipt requested flag
@property (nonatomic) BOOL receiptRequested;
/// Tax hidden
@property (nonatomic) BOOL taxHidden;
/// Currency
@property (nonatomic, strong) NSString* currency;
/// Device type
@property (nonatomic, strong) NSString* deviceType;
/// gateway Live flag
@property (nonatomic) BOOL gatewayLive;
/// Processed date
@property (nonatomic, strong) NSString* processedAt;
/// Cardholder last name
@property (nonatomic, strong) NSString* cardHolderLastName;
/// Longitude
@property (nonatomic, strong) NSString* lng;
/// Additional information
@property (nonatomic, strong) NSString* additionalInfo;
/// Service charge hidden flag
@property (nonatomic) BOOL serviceChargeHidden;
/// Technical message
@property (nonatomic, strong) NSString* technicalMessage;
/// Note
@property (nonatomic, strong) NSString* note;
/// Application ID
@property (nonatomic, strong) NSString* cnpApplicationId;
/// receipt emailed flag
@property (nonatomic) BOOL emailReceipt;
/// TX Number
@property (nonatomic) NSInteger txNumber;
/// gratuity type
@property (nonatomic, strong) NSString* gratuityType;
/// Gratuity
@property (nonatomic) NSInteger tip;
/// Country code
@property (nonatomic) NSInteger countryCode;
/// Cardholder first name
@property (nonatomic, strong) NSString* cardHolderFirstName;
/// Status
@property (nonatomic, strong) NSString* state;
/// Location
@property (nonatomic, strong) NSString* location;
/// Refundable flag
@property (nonatomic) BOOL refundable;
/// Gateway login
@property (nonatomic, strong) NSString* gatewayLogin;
/// TVR
@property (nonatomic, strong) NSString* cnpTvr;
/// Type
@property (nonatomic, strong) NSString* type;
/// Status
@property (nonatomic, strong) NSString* status;
/// Bank code
@property (nonatomic, strong) NSString* bankCode;
/// Tax
@property (nonatomic) NSInteger tax;
/// Issuer response code
@property (nonatomic, strong) NSString* cnpIssuerResponseCode;
/// Authorization number
@property (nonatomic, strong) NSString* cnpAuthorizationNumber;
/// Authorization code
@property (nonatomic, strong) NSString* cnpAuthorizationCode;
/// EMV Merchant ID
@property (nonatomic, strong) NSString* cnpMerchantId;
/// Transaciton type
@property (nonatomic, strong) NSString* emvTransactionType;
/// Expects Transaction confirmation
@property (nonatomic) BOOL expectsTC;
/// Capturable flag
@property (nonatomic) BOOL capturable;
/// Reversible flag
@property (nonatomic) BOOL reversible;
/// Reference ID
@property (nonatomic, strong) NSString* referenceId;
/// gateway password
@property (nonatomic, strong) NSString* gatewayPassword;
/// latitude
@property (nonatomic, strong) NSString* lat;
/// Internal Merchant ID
@property (nonatomic) NSInteger merchantId;
/// Application label
@property (nonatomic, strong) NSString* cnpApplicationLabel;
/// Items
@property (nonatomic, strong) NSArray* items;
/// Created at
@property (nonatomic, strong) NSString* createdAt;
/// Transaction type
@property (nonatomic, strong) NSString* transactionType;
/// Card type
@property (nonatomic, strong) NSString* cardType;
/// Amount
@property (nonatomic) NSDecimalNumber* amount;
/// TSI
@property (nonatomic, strong) NSString* cnpTsi;
/// Unique ID
@property (nonatomic, strong) NSString* uniqueId;
/// Signature
@property (nonatomic, strong) AcceptTransactionSignature* signature;
/// Refunds
@property (nonatomic, strong) NSArray* refunds;
/// Reversals
@property (nonatomic, strong) NSArray* reversals;

/// Error code
@property (nonatomic, strong) NSString* errorCode;
/// Card number
@property (nonatomic, strong) NSString* cardNumber;
/// Service charge amount
@property (nonatomic) NSInteger serviceChargeAmount;
/// Service charge tax
@property (nonatomic) NSDecimalNumber *serviceChargeTaxRate;
/// Terminal ID
@property (nonatomic, strong) NSString* cnpTerminalId;
/// Issuer script
@property (nonatomic, strong) NSString* issuerScript;
/// nat Taxation
@property (nonatomic) BOOL netTaxation;
/// POS Entry mode
@property (nonatomic, strong) NSString* posEntryMode;
/// Custom fields
@property (nonatomic, strong) NSDictionary* customFields;
/// Discount
@property (nonatomic) NSDecimalNumber *discount;
/// ATrust ID
@property (nonatomic, strong) NSString* atrust_id;
/// ATrust qr payload
@property (nonatomic, strong) NSString* qr_payload;
/// ATrust Cashier ID
@property (nonatomic, strong) NSString* cashier_id;
/// Sub Merchant
@property (nonatomic, strong) AcceptSubMerchant* subMerchant;

/// Receipt Ready to print - there is a delay in the case of ATrust transactions, if false then query the transaction details again
@property (nonatomic) BOOL receipt_ready;
/**
 * @discussion Get the receipt data from this transaction
 */
-(AcceptReceiptData *)getAcceptReceiptData;

@end



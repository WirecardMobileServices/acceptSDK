//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

#define kAcceptTransactionStatus_Approved         @"approved"
#define kAcceptTransactionStatus_Pending          @"pending"
#define kAcceptTransactionStatus_Refunded         @"refunded"
#define kAcceptTransactionStatus_Rejected         @"rejected"
#define kAcceptTransactionStatus_Reversed         @"reversed"
#define kAcceptTransactionStatus_New              @"new"
#define kAcceptTransactionStatus_Preauthorized    @"preauthorized"
#define kAcceptTransactionStatus_Bookbacked       @"bookbacked"
#define kAcceptTransactionStatus_Chargebacked     @"chargebacked"
#define kAcceptTransactionStatus_Canceled         @"canceled"


#define kTransactionReversalRequired @"Transaction reversal required"
#define kTransactionReversedByTerminal @"Transaction reversed by terminal"
#define kTransactionReversalFailed @"Transaction reversal failed"
#define kSignatureRejectedByTerminal @"Signature was rejected by terminal"
#define kTransactionUpdateFailed @"Transaction update failed"
#define kValidAppDataFailed @"Can't find valid Transaction And Application data"

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
@property (nonatomic, strong) NSString* cnpTerminalId;
/**
 */
@property (nonatomic, strong) NSString* issuerScript;

@end



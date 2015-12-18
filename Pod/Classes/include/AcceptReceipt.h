//
//  AcceptReceipt.h
//  Pods
//
//  Created by Danko, Radoslav on 8/7/14.
//
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptReceipt
 *  @discussion Receipt content class
 **/
@interface AcceptReceipt : NSObject
/**
 */
@property (nonatomic,strong) NSString *header;
/**
 */
@property (nonatomic,strong) NSString *merchantName;
/**
 */
@property (nonatomic,strong) NSString *merchantIDHeader;
/**
 */
@property (nonatomic,strong) NSString *merchantID;
/**
 */
@property (nonatomic,strong) NSString *merchantAddressLine1;
/**
 */
@property (nonatomic,strong) NSString *merchantAddressLine2;
/**
 */
@property (nonatomic,strong) NSString *merchantAddressZipCode;
/**
 */
@property (nonatomic,strong) NSString *merchantAddressCityAndCountry;
/**
 */
@property (nonatomic,strong) NSString *merchantPhone;
/**
 */
@property (nonatomic,strong) NSString *localisedReceiptDateHeader;
/**
 */
@property (nonatomic,strong) NSString *localisedPaymentDateHeader;
/**
 */
@property (nonatomic,strong) NSString *receiptDate;
/**
 */
@property (nonatomic,strong) NSString *localisedReceiptTimeHeader;
/**
 */
@property (nonatomic,strong) NSString *receiptTime;
/**
 */
@property (nonatomic,strong) NSString *localisedReceiptIDHeader;
/**
 */
@property (nonatomic,strong) NSString *localisedReceiptNumberHeader;
/**
 */
@property (nonatomic,strong) NSString *receiptID;
/**
 */
@property (nonatomic,strong) NSString *aidHeader;
/**
 */
@property (nonatomic,strong) NSString *aid;
/**
 */
@property (nonatomic,strong) NSString *localisedCardTypeHeader;
/**
 */
@property (nonatomic,strong) NSString *cardType;
/**
 */
@property (nonatomic,strong) NSString *transactionTypeString;
/**
 */
@property (nonatomic,strong) NSString *localisedTransactionTypeHeader;
/**
 */
@property (nonatomic,strong) NSString *localisedCardNumberHeader;
/**
 */
@property (nonatomic,strong) NSString *cardNumber;
/**
 */
@property (nonatomic,strong) NSString *localisedCardHolderHeader;
/**
 */
@property (nonatomic,strong) NSString *cardHolder;
/**
 */
@property (nonatomic,strong) NSString *localisedExpiryDateHeader;
/**
 */
@property (nonatomic,strong) NSString *expiryDate;
/**
 */
@property (nonatomic,strong) NSString *localisedTerminalIDHeader;
/**
 */
@property (nonatomic,strong) NSString *terminalID;
/**
 */
@property (nonatomic,strong) NSString *localisedApprovalCodeHeader;
/**
 */
@property (nonatomic,strong) NSString *approvalCode;
/**
 */
@property (nonatomic,strong) NSString *localisedAmountHeader;
/**
 */
@property (nonatomic,strong) NSString *localisedAOSAHeader;
/**
 */
@property (nonatomic,strong) NSString *amount;
/**
 */
@property (nonatomic,strong) NSString *localisedTransactionStatusHeader;
/**
 */
@property (nonatomic,strong) NSString *transactionStatus;
/**
 */
@property (nonatomic,strong) NSString *paymentItems;
/**
 */
@property (nonatomic,strong) NSString *taxSummary;
/**
 */
@property (nonatomic,strong) NSString *tipSummary;
/**
 */
@property (nonatomic,strong) NSString *serviceChargeSummary;
/**
 */
@property (nonatomic,strong) NSString *localisedPaymentDetailsHeader;
/**
 */
@property (nonatomic,strong) NSString *footer;
/**
 */
@property (nonatomic,strong) NSString *footerThankYou;
/**
 */
@property (nonatomic,strong) NSString *footerCopyright;
/**
 */
@property (nonatomic,strong) NSString *receiptQRCodeString;
/**
 */
@property (nonatomic,strong) NSString *availableOfflineSpendingAmount;
/**
 */
@property (nonatomic) BOOL verifiedOnDeviceCVM;
/**
 */
@property (nonatomic,strong) NSString *appCrypt;
/**
 */
@property (nonatomic,strong) NSString *cryptID;
/**
 */
@property (nonatomic,strong) NSString *appTransCounter;
/**
 */
@property (nonatomic,strong) NSString *declinedReason;
/**
 */
@property (nonatomic) BOOL PINVerified;
/**
 */
@property (nonatomic,strong) NSString *transactionTypeAsText;
@end

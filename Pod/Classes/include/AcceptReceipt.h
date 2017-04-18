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
 *  @discussion Data to be displayed on the receipt
 **/
@interface AcceptReceipt : NSObject
/// Receipt header
@property (nonatomic,strong) NSString *header;
/// Merchant name
@property (nonatomic,strong) NSString *merchantName;
/// Merchant ID header - localized
@property (nonatomic,strong) NSString *merchantIDHeader;
/// Merchant ID
@property (nonatomic,strong) NSString *merchantID;
/// Address line 1
@property (nonatomic,strong) NSString *merchantAddressLine1;
/// Address line 2
@property (nonatomic,strong) NSString *merchantAddressLine2;
/// Zip Code
@property (nonatomic,strong) NSString *merchantAddressZipCode;
/// City and Country
@property (nonatomic,strong) NSString *merchantAddressCityAndCountry;
/// Phone No.
@property (nonatomic,strong) NSString *merchantPhone;
/// Localized receipt date header
@property (nonatomic,strong) NSString *localisedReceiptDateHeader;
/// Localized payment date header
@property (nonatomic,strong) NSString *localisedPaymentDateHeader;
/// Formatted receipt date
@property (nonatomic,strong) NSString *receiptDate;
/// Localized receipt time header
@property (nonatomic,strong) NSString *localisedReceiptTimeHeader;
/// Formatted Receipt Time
@property (nonatomic,strong) NSString *receiptTime;
/// localized Receipt ID header
@property (nonatomic,strong) NSString *localisedReceiptIDHeader;
/// Localized Receipt Number header
@property (nonatomic,strong) NSString *localisedReceiptNumberHeader;
/// Receipt ID
@property (nonatomic,strong) NSString *receiptID;
/// AID header
@property (nonatomic,strong) NSString *aidHeader;
/// AID
@property (nonatomic,strong) NSString *aid;
/// Localized card type header
@property (nonatomic,strong) NSString *localisedCardTypeHeader;
/// Card type
@property (nonatomic,strong) NSString *cardType;
/// Transaction Type
@property (nonatomic,strong) NSString *transactionTypeString;
/// Localized transaction type header
@property (nonatomic,strong) NSString *localisedTransactionTypeHeader;
/// Localized Card Number header
@property (nonatomic,strong) NSString *localisedCardNumberHeader;
/// Card Number
@property (nonatomic,strong) NSString *cardNumber;
/// Cardholder name header
@property (nonatomic,strong) NSString *localisedCardHolderHeader;
/// Cardholder name
@property (nonatomic,strong) NSString *cardHolder;
/// Localized Expiry date header
@property (nonatomic,strong) NSString *localisedExpiryDateHeader;
/// Expiry date
@property (nonatomic,strong) NSString *expiryDate;
/// Localized Terminal ID header
@property (nonatomic,strong) NSString *localisedTerminalIDHeader;
/// Terminal ID
@property (nonatomic,strong) NSString *terminalID;
/// Localized Approval code header
@property (nonatomic,strong) NSString *localisedApprovalCodeHeader;
/// Approval code
@property (nonatomic,strong) NSString *approvalCode;
/// Localized Amount header
@property (nonatomic,strong) NSString *localisedAmountHeader;
/// localized AOSA header - used for contactless transations
@property (nonatomic,strong) NSString *localisedAOSAHeader;
/// Formatted Amount
@property (nonatomic,strong) NSString *amount;
/// Localized transaction status header
@property (nonatomic,strong) NSString *localisedTransactionStatusHeader;
/// Transaction status
@property (nonatomic,strong) NSString *transactionStatus;
/// payment items - formatted with \t and \n to fit the width of Datecs DPP250 printer paper width
@property (nonatomic,strong) NSString *paymentItems;
/// Tax summary - formatted with \t and \n to fit the width of Datecs DPP250 printer paper width
@property (nonatomic,strong) NSString *taxSummary;
/// Tip Summary - formatted with \t and \n to fit the width of Datecs DPP250 printer paper width
@property (nonatomic,strong) NSString *tipSummary;
/// Service charge - formatted with \t and \n to fit the width of Datecs DPP250 printer paper width
@property (nonatomic,strong) NSString *serviceChargeSummary;
/// Localized Payment details header
@property (nonatomic,strong) NSString *localisedPaymentDetailsHeader;
/// Receipt Fotter
@property (nonatomic,strong) NSString *footer;
/// Receipt thank you message
@property (nonatomic,strong) NSString *footerThankYou;
/// Receipt footer copyright
@property (nonatomic,strong) NSString *footerCopyright;
/// Receipt QR Code
@property (nonatomic,strong) NSString *receiptQRCodeString;
/// Available offline spending amount - for contactless transaction
@property (nonatomic,strong) NSString *availableOfflineSpendingAmount;
/// Verified on Device CVM - for contactless transaction
@property (nonatomic) BOOL verifiedOnDeviceCVM;
/// Application cryptogram
@property (nonatomic,strong) NSString *appCrypt;
/// Cryptogram ID
@property (nonatomic,strong) NSString *cryptID;
/// Application transaction counter
@property (nonatomic,strong) NSString *appTransCounter;
/// Transaction declined reason
@property (nonatomic,strong) NSString *declinedReason;
/// PIN verified
@property (nonatomic) BOOL PINVerified;
/// Transaction type - description
@property (nonatomic,strong) NSString *transactionTypeAsText;
/// Is the transaction contactless
@property (nonatomic) BOOL isContactless;
/// POS Entry mode
@property (nonatomic,strong) NSString *posEntryModeInterpreted;
/// Payment type
@property (nonatomic,strong) NSString *paymentType;
/// Custom fields
@property (nonatomic,strong) NSDictionary *customFields;
/// Localized discount header
@property (nonatomic,strong) NSString *localisedDiscountHeader;
/// Formatted discount
@property (nonatomic,strong) NSString *discount;
/// ATrust ID
@property (nonatomic, strong) NSString* atrust_id;
/// ATrust Cashier ID
@property (nonatomic, strong) NSString* cashier_id;
/// ATrust Cashier ID localized header
@property (nonatomic, strong) NSString* localised_cashier_id;
@end

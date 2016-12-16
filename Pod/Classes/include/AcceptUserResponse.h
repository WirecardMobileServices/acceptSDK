//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

/**
 *  @class AcceptUserResponseMerchantWhiteLabelApp
 *  @discussion Basic merchant info as defined and received from backend
 **/
@interface AcceptUserResponseMerchantWhiteLabelApp : NSObject
/// Name
@property (nonatomic, strong) NSString* name;
/// Acquirer identifier
@property (nonatomic, strong) NSString* acquirerIdentifier;
/// Locale
@property (nonatomic, strong) NSString* locale;
/// Created at
@property (nonatomic, strong) NSString* createdAt;
/// Country ID
@property (nonatomic) NSInteger countryId;
/// Time Zone
@property (nonatomic, strong) NSString* timeZone;
/// Updated at
@property (nonatomic, strong) NSString* updatedAt;
/// Amount Upper limit
@property (nonatomic) NSDecimalNumber* amountUpperLimit;
/// Amount Lower limit
@property (nonatomic) NSInteger amountLowerLimit;
/// Support phone number
@property (nonatomic, strong) NSString* customerSupportPhoneNumber;
/// Internal ID
@property (nonatomic) NSInteger id_;
/// Identifier
@property (nonatomic, strong) NSString* identifier;
/// Amount Daily limit
@property (nonatomic) NSDecimalNumber* amountDailyLimit;
/// Email
@property (nonatomic, strong) NSString* emailFrom;
/// Service Charge amount
@property (nonatomic, strong) NSString* serviceChargeAmount;
/// Default Currency for merchant
@property (nonatomic, strong) NSString* defaultCurrency;
@end

/**
 *  @class AcceptUserResponseMerchant
 *  @discussion Complete merchant info as defined and received from backend
 **/
@interface AcceptUserResponseMerchant : NSObject
/// Status
@property (nonatomic, strong) NSString* status;
/// Locale
@property (nonatomic, strong) NSString* locale;
/// Gateway Signature
@property (nonatomic, strong) NSString* gatewaySignature;
/// Terminal Id
@property (nonatomic, strong) NSString* terminalId;
/// updated at
@property (nonatomic, strong) NSString* updatedAt;
/// Currency - default
@property (nonatomic, strong) NSString* currency;
/// Available Currencies
@property (nonatomic, strong) NSArray* currencies;
/// Country code
@property (nonatomic, strong) NSString* countryCode;
/// Gateway Live
@property (nonatomic) BOOL gatewayLive;
/// Internal Id
@property (nonatomic) NSInteger id_;
/// City
@property (nonatomic, strong) NSString* city;
/// Country Id
@property (nonatomic) NSInteger countryId;
/// Tax Rates
@property (nonatomic, strong) NSArray* taxRates;
/// State
@property (nonatomic, strong) NSString* state;
/// Country
@property (nonatomic, strong) NSString* countryState;
/// Owner Id
@property (nonatomic) NSInteger ownerId;
/// Phone Number
@property (nonatomic, strong) NSString* phoneNumber;
/// Address line 2
@property (nonatomic, strong) NSString* address2;
/// Gateway Login
@property (nonatomic, strong) NSString* gatewayLogin;
/// Gateway Password
@property (nonatomic, strong) NSString* gatewayPassword;
/// Whitelabel App  settings
@property (nonatomic, strong) AcceptUserResponseMerchantWhiteLabelApp* whiteLabelApp;
/// Name
@property (nonatomic, strong) NSString* name;
/// Acquirer identifier
@property (nonatomic, strong) NSString* acquirerIdentifier;
/// Created at
@property (nonatomic, strong) NSString* createdAt;
/// Merchant category code
@property (nonatomic, strong) NSString* merchantCategoryCode;
/// Whitelabel app id
@property (nonatomic) NSInteger whiteLabelAppId;
/// Operator PIN
@property (nonatomic, strong) NSString* cnpOperatorPin;
/// Address line 1
@property (nonatomic, strong) NSString* address1;
/// Support phone number
@property (nonatomic, strong) NSString* customerSupportPhoneNumber;
/// VAT id
@property (nonatomic, strong) NSString* vatId;
/// ZIP
@property (nonatomic, strong) NSString* zipCode;
/// External ID
@property (nonatomic, strong) NSString* externalId;
/// Terminal Type
@property (nonatomic, strong) NSString* cnp_terminal_type;
/// Transaction Category code
@property (nonatomic, strong) NSString* cnp_transaction_category_code;
/// Transaction Type
@property (nonatomic, strong) NSString* cnp_transaction_type;
/// Terminal capabilities
@property (nonatomic, strong) NSString* cnp_terminal_capabilities;
/// Terminal additional capabilities
@property (nonatomic, strong) NSString* cnp_terminal_additional_capabilities;
/// Application version number
@property (nonatomic, strong) NSString* cnp_application_version_number;
/// Force online
@property (nonatomic, strong) NSString* cnp_force_online;
/// TAC default
@property (nonatomic, strong) NSString* cnp_tac_default;
/// TAX denial
@property (nonatomic, strong) NSString* cnp_tac_denial;
/// TAC online
@property (nonatomic, strong) NSString* cnp_tac_online;
/// Target %
@property (nonatomic, strong) NSString* cnp_target_percentage;
/// MAX target %
@property (nonatomic, strong) NSString* cnp_max_target_percentage;
///Threshold value
@property (nonatomic, strong) NSString* cnp_treshold_value;
/// Floor limit
@property (nonatomic, strong) NSString* cnp_floor_limit;
/// Constraint checks
@property (nonatomic, strong) NSString* cnp_constraint_checks;
/// Net taxation
@property (nonatomic) BOOL net_taxation;
/// RKSV Ready - Austrian cash management
@property (nonatomic) BOOL rksv_ready;
/// RKSV Initiated - Austrian cash management
@property (nonatomic) BOOL rksv_initiated;
@end

/**
 *  @class AcceptUserResponseWhiteLabelApp
 *  @discussion Basic user info as defined and received from backend
 **/
@interface AcceptUserResponseWhiteLabelApp : NSObject
/// Name
@property (nonatomic, strong) NSString* name;
/// Acquirer identifier
@property (nonatomic, strong) NSString* acquirerIdentifier;
/// Locale
@property (nonatomic, strong) NSString* locale;
/// Created at
@property (nonatomic, strong) NSString* createdAt;
/// Country Id
@property (nonatomic) NSInteger countryId;
/// Updated at
@property (nonatomic, strong) NSString* updatedAt;
/// Tax rates
@property (nonatomic, strong) NSArray* taxRates;
/// Amount Upper limit
@property (nonatomic,strong) NSDecimalNumber  *amountUpperLimit;
/// Amount Lower limit
@property (nonatomic) NSInteger amountLowerLimit;
/// Time zone
@property (nonatomic, strong) NSString* timeZone;
/// Support phone number
@property (nonatomic, strong) NSString* customerSupportPhoneNumber;
/// Email
@property (nonatomic, strong) NSString* emailFrom;
/// Identifier
@property (nonatomic, strong) NSString* identifier;
/// Amount Daily limit
@property (nonatomic, strong) NSDecimalNumber *amountDailyLimit;
/// Internal ID
@property (nonatomic) NSInteger id_;
/// Service charge amount
@property (nonatomic, strong) NSString* serviceChargeAmount;
/// Default currency
@property (nonatomic, strong) NSString* defaultCurrency;
/// Service charge tax
@property (nonatomic,strong) NSString * service_charge_tax;
@end

/**
 *  @class AcceptUserResponseAvatarAvatarSmall
 *  @discussion User response with small avatar
 **/
@interface AcceptUserResponseAvatarAvatarSmall : NSObject
/// URL of the image
@property (nonatomic, strong) NSString* url;
@end

/**
 *  @class AcceptUserResponseAvatarAvatar
 *  @discussion User response with regular avatar
 **/
@interface AcceptUserResponseAvatarAvatar : NSObject
/// URL of the large image
@property (nonatomic, strong) NSString* url;
/// URL of the small image
@property (nonatomic, strong) AcceptUserResponseAvatarAvatarSmall* small;
@end

/**
 *  @class AcceptUserResponseAvatar
 *  @discussion User avatar response
 **/
@interface AcceptUserResponseAvatar : NSObject
/// URL of the image
@property (nonatomic, strong) AcceptUserResponseAvatarAvatar* avatar;
@end

/**
 *  @class AidConfigurationItem
 *  @discussion Aid configuration as defined and received from backend
 **/
@interface AidConfigurationItem : NSObject
/// Application name
@property (nonatomic, strong) NSString* cnpAppName;
/// TAC Default
@property (nonatomic, strong) NSString* cnpAppTacDefault;
/// Internal ID
@property (nonatomic) NSInteger id_;
/// TAC Denial
@property (nonatomic, strong) NSString* cnpAppTacDenial;
/// Application version
@property (nonatomic, strong) NSString* cnpAppVersion;
/// Application ID
@property (nonatomic, strong) NSString* cnpAppId;
/// App Target %
@property (nonatomic, strong) NSString* cnpAppTargetPercentage;
/// App Threshold value
@property (nonatomic, strong) NSString* cnpAppTresholdValue;
/// MAX target %
@property (nonatomic, strong) NSString* cnpAppMaxTargetPercentage;
/// TAC Online
@property (nonatomic, strong) NSString* cnpAppTacOnline;
/// Floor limit
@property (nonatomic, strong) NSString* cnpAppFloorLimit;
/// Constraint checks
@property (nonatomic, strong) NSString* cnpConstraintsChecks;
/// DDOL
@property (nonatomic, strong) NSString* cnpDDOL;
/// Target %
@property (nonatomic, strong) NSString* cnpTargetPercentage;
/// TDOL
@property (nonatomic, strong) NSString* cnpTDOL;
/// Transaction Type
@property (nonatomic, strong) NSString* cnpTransactionType;
@end

/**
 *  @class AcceptUserResponse
 *  @discussion User response info
 **/
@interface AcceptUserResponse : NSObject
/// Merchant
@property (nonatomic, strong) AcceptUserResponseMerchant* merchant;
/// Last name
@property (nonatomic, strong) NSString* lastName;
/// Terminal ID
@property (nonatomic, strong) NSString* terminalId;
/// Updated at
@property (nonatomic, strong) NSString* updatedAt;
/// Gateway Live
@property (nonatomic) BOOL gatewayLive;
/// Internal ID
@property (nonatomic) NSInteger id_;
/// First name
@property (nonatomic, strong) NSString* firstName;
/// Gateway Signature
@property (nonatomic, strong) NSString* gatewaySignature;
/// Email
@property (nonatomic, strong) NSString* email;
/// Phone number
@property (nonatomic, strong) NSString* phoneNumber;
/// Gateway Login
@property (nonatomic, strong) NSString* gatewayLogin;
/// User image URL
@property (nonatomic, strong) NSString* avatarFilenameToken;
/// Gateway password
@property (nonatomic, strong) NSString* gatewayPassword;
/// Whitelabel app
@property (nonatomic, strong) AcceptUserResponseWhiteLabelApp* whiteLabelApp;
/// Mobile device
@property (nonatomic, strong) NSString* mobileDevice;
/// Merchant ID
@property (nonatomic) NSInteger merchantId;
/// Acquirer identifier
@property (nonatomic, strong) NSString* acquirerIdentifier;
/// Gender
@property (nonatomic, strong) NSString* gender;
/// Created At
@property (nonatomic, strong) NSString* createdAt;
/// Whitelabel App ID
@property (nonatomic) NSInteger whiteLabelAppId;
/// User image
@property (nonatomic, strong) AcceptUserResponseAvatar* avatar;
/// External ID
@property (nonatomic, strong) NSString* externalId;
/// AID configurations
@property (nonatomic, strong) NSArray* aidConfigurations;
/// Unique ID
@property (nonatomic, strong) NSString* uniqueId;
/// Merchant identifier
@property (nonatomic, strong) NSString* cnp_merchant_identifier;
/// TAC default
@property (nonatomic, strong) NSString* cnp_tac_default;
/// TAC denial
@property (nonatomic, strong) NSString* cnp_tac_denial;
/// TAC online
@property (nonatomic, strong) NSString* cnp_tac_online;
/// Target %
@property (nonatomic, strong) NSString* cnp_target_percentage;
/// MAX target %
@property (nonatomic, strong) NSString* cnp_max_target_percentage;
/// Threshold value
@property (nonatomic, strong) NSString* cnp_treshold_value;
/// Floor limit
@property (nonatomic, strong) NSString* cnp_floor_limit;
/// Needs password update
@property (nonatomic) BOOL needsPasswordUpdate;
/// Transaction confirmation expires in
@property (nonatomic) NSInteger tc_expires_in;
@end


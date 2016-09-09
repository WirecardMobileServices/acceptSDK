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
/**
 */
@property (nonatomic, strong) NSString* name;
/**
 */
@property (nonatomic, strong) NSString* acquirerIdentifier;
/**
 */
@property (nonatomic, strong) NSString* locale;
/**
 */
@property (nonatomic, strong) NSString* createdAt;
/**
 */
@property (nonatomic) NSInteger countryId;
/**
 */
@property (nonatomic, strong) NSString* timeZone;
/**
 */
@property (nonatomic, strong) NSString* updatedAt;
/**
 */
@property (nonatomic) NSDecimalNumber* amountUpperLimit;
/**
 */
@property (nonatomic) NSInteger amountLowerLimit;
/**
 */
@property (nonatomic, strong) NSString* customerSupportPhoneNumber;
/**
 */
@property (nonatomic) NSInteger id_;
/**
 */
@property (nonatomic, strong) NSString* identifier;
/**
 */
@property (nonatomic) NSDecimalNumber* amountDailyLimit;
/**
 */
@property (nonatomic, strong) NSString* emailFrom;
/**
 */
@property (nonatomic, strong) NSString* serviceChargeAmount;
/**
 */
@property (nonatomic, strong) NSString* defaultCurrency;
@end

/**
 *  @class AcceptUserResponseMerchant
 *  @discussion Complete merchant info as defined and received from backend
 **/
@interface AcceptUserResponseMerchant : NSObject
/**
 */
@property (nonatomic, strong) NSString* status;
/**
 */
@property (nonatomic, strong) NSString* locale;
/**
 */
@property (nonatomic, strong) NSString* gatewaySignature;
/**
 */
@property (nonatomic, strong) NSString* terminalId;
/**
 */
@property (nonatomic, strong) NSString* updatedAt;
/**
 */
@property (nonatomic, strong) NSString* currency;
/**
 */
@property (nonatomic, strong) NSArray* currencies;
/**
 */
@property (nonatomic, strong) NSString* countryCode;
/**
 */
@property (nonatomic) BOOL gatewayLive;
/**
 */
@property (nonatomic) NSInteger id_;
/**
 */
@property (nonatomic, strong) NSString* city;
/**
 */
@property (nonatomic) NSInteger countryId;
/**
 */
@property (nonatomic, strong) NSArray* taxRates;
/**
 */
@property (nonatomic, strong) NSString* state;
/**
 */
@property (nonatomic, strong) NSString* countryState;
/**
 */
@property (nonatomic) NSInteger ownerId;
/**
 */
@property (nonatomic, strong) NSString* phoneNumber;
/**
 */
@property (nonatomic, strong) NSString* address2;
/**
 */
@property (nonatomic, strong) NSString* gatewayLogin;
/**
 */
@property (nonatomic, strong) NSString* gatewayPassword;
/**
 */
@property (nonatomic, strong) AcceptUserResponseMerchantWhiteLabelApp* whiteLabelApp;
/**
 */
@property (nonatomic, strong) NSString* name;
/**
 */
@property (nonatomic, strong) NSString* acquirerIdentifier;
/**
 */
@property (nonatomic, strong) NSString* createdAt;
/**
 */
@property (nonatomic, strong) NSString* merchantCategoryCode;
/**
 */
/**
 */
@property (nonatomic) NSInteger whiteLabelAppId;
/**
 */
@property (nonatomic, strong) NSString* cnpOperatorPin;
/**
 */
@property (nonatomic, strong) NSString* address1;
/**
 */
@property (nonatomic, strong) NSString* customerSupportPhoneNumber;
/**
 */
@property (nonatomic, strong) NSString* vatId;
/**
 */
@property (nonatomic, strong) NSString* zipCode;
/**
 */
@property (nonatomic, strong) NSString* externalId;
/**
 */
@property (nonatomic, strong) NSString* cnp_terminal_type;
/**
 */
@property (nonatomic, strong) NSString* cnp_transaction_category_code;
/**
 */
@property (nonatomic, strong) NSString* cnp_transaction_type;
/**
 */
@property (nonatomic, strong) NSString* cnp_terminal_capabilities;
/**
 */
@property (nonatomic, strong) NSString* cnp_terminal_additional_capabilities;
/**
 */
@property (nonatomic, strong) NSString* cnp_application_version_number;
/**
 */
@property (nonatomic, strong) NSString* cnp_force_online;
/**
 */
@property (nonatomic, strong) NSString* cnp_tac_default;
/**
 */
@property (nonatomic, strong) NSString* cnp_tac_denial;
/**
 */
@property (nonatomic, strong) NSString* cnp_tac_online;
/**
 */
@property (nonatomic, strong) NSString* cnp_target_percentage;
/**
 */
@property (nonatomic, strong) NSString* cnp_max_target_percentage;
/**
 */
@property (nonatomic, strong) NSString* cnp_treshold_value;
/**
 */
@property (nonatomic, strong) NSString* cnp_floor_limit;
/**
 */
@property (nonatomic, strong) NSString* cnp_constraint_checks;
/**
 */
@property (nonatomic) BOOL net_taxation;
/**
 */
@property (nonatomic) BOOL rksv_ready;
/**
 */
@property (nonatomic) BOOL rksv_initiated;
@end

/**
 *  @class AcceptUserResponseWhiteLabelApp
 *  @discussion Basic user info as defined and received from backend
 **/
@interface AcceptUserResponseWhiteLabelApp : NSObject
/**
 */
@property (nonatomic, strong) NSString* name;
/**
 */
@property (nonatomic, strong) NSString* acquirerIdentifier;
/**
 */
@property (nonatomic, strong) NSString* locale;
/**
 */
@property (nonatomic, strong) NSString* createdAt;
/**
 */
@property (nonatomic) NSInteger countryId;
/**
 */
@property (nonatomic, strong) NSString* updatedAt;
/**
 */
@property (nonatomic, strong) NSArray* taxRates;
/**
 */
@property (nonatomic,strong) NSDecimalNumber  *amountUpperLimit;
/**
 */
@property (nonatomic) NSInteger amountLowerLimit;
/**
 */
@property (nonatomic, strong) NSString* timeZone;
/**
 */
@property (nonatomic, strong) NSString* customerSupportPhoneNumber;
/**
 */
@property (nonatomic, strong) NSString* emailFrom;
/**
 */
@property (nonatomic, strong) NSString* identifier;
/**
 */
@property (nonatomic, strong) NSDecimalNumber *amountDailyLimit;
/**
 */
@property (nonatomic) NSInteger id_;
/**
 */
@property (nonatomic, strong) NSString* serviceChargeAmount;
/**
 */
@property (nonatomic, strong) NSString* defaultCurrency;
/**
 */
@property (nonatomic,strong) NSString * service_charge_tax;
@end

/**
 *  @class AcceptUserResponseAvatarAvatarSmall
 *  @discussion User response with small avatar
 **/
@interface AcceptUserResponseAvatarAvatarSmall : NSObject
/**
 */
@property (nonatomic, strong) NSString* url;
@end

/**
 *  @class AcceptUserResponseAvatarAvatar
 *  @discussion User response with regular avatar
 **/
@interface AcceptUserResponseAvatarAvatar : NSObject
/**
 */
@property (nonatomic, strong) NSString* url;
/**
 */
@property (nonatomic, strong) AcceptUserResponseAvatarAvatarSmall* small;
@end

/**
 *  @class AcceptUserResponseAvatar
 *  @discussion User avatar response
 **/
@interface AcceptUserResponseAvatar : NSObject
/**
 */
@property (nonatomic, strong) AcceptUserResponseAvatarAvatar* avatar;
@end

/**
 *  @class AidConfigurationItem
 *  @discussion Aid configuration as defined and received from backend
 **/
@interface AidConfigurationItem : NSObject
/**
 */
@property (nonatomic, strong) NSString* cnpAppName;
/**
 */
@property (nonatomic, strong) NSString* cnpAppTacDefault;
/**
 */
@property (nonatomic) NSInteger id_;
/**
 */
@property (nonatomic, strong) NSString* cnpAppTacDenial;
/**
 */
@property (nonatomic, strong) NSString* cnpAppVersion;
/**
 */
@property (nonatomic, strong) NSString* cnpAppId;
/**
 */
@property (nonatomic, strong) NSString* cnpAppTargetPercentage;
/**
 */
@property (nonatomic, strong) NSString* cnpAppTresholdValue;
/**
 */
@property (nonatomic, strong) NSString* cnpAppMaxTargetPercentage;
/**
 */
@property (nonatomic, strong) NSString* cnpAppTacOnline;
/**
 */
@property (nonatomic, strong) NSString* cnpAppFloorLimit;
/**
 */
@property (nonatomic, strong) NSString* cnpConstraintsChecks;
/**
 */
@property (nonatomic, strong) NSString* cnpDDOL;
/**
 */
@property (nonatomic, strong) NSString* cnpTargetPercentage;
/**
 */
@property (nonatomic, strong) NSString* cnpTDOL;
/**
 */
@property (nonatomic, strong) NSString* cnpTransactionType;
@end

/**
 *  @class AcceptUserResponse
 *  @discussion User response info
 **/
@interface AcceptUserResponse : NSObject
/**
 */
@property (nonatomic, strong) AcceptUserResponseMerchant* merchant;
/**
 */
@property (nonatomic, strong) NSString* lastName;
/**
 */
@property (nonatomic, strong) NSString* terminalId;
/**
 */
@property (nonatomic, strong) NSString* updatedAt;
/**
 */
@property (nonatomic) BOOL gatewayLive;
/**
 */
@property (nonatomic) NSInteger id_;
/**
 */
@property (nonatomic, strong) NSString* firstName;
/**
 */
@property (nonatomic, strong) NSString* gatewaySignature;
/**
 */
@property (nonatomic, strong) NSString* email;
/**
 */
@property (nonatomic, strong) NSString* phoneNumber;
/**
 */
@property (nonatomic, strong) NSString* gatewayLogin;
/**
 */
@property (nonatomic, strong) NSString* avatarFilenameToken;
/**
 */
@property (nonatomic, strong) NSString* gatewayPassword;
/**
 */
@property (nonatomic, strong) AcceptUserResponseWhiteLabelApp* whiteLabelApp;
/**
 */
@property (nonatomic, strong) NSString* mobileDevice;
/**
 */
@property (nonatomic) NSInteger merchantId;
/**
 */
@property (nonatomic, strong) NSString* acquirerIdentifier;
/**
 */
@property (nonatomic, strong) NSString* gender;
/**
 */
@property (nonatomic, strong) NSString* createdAt;
/**
 */
@property (nonatomic) NSInteger whiteLabelAppId;
/**
 */
@property (nonatomic, strong) AcceptUserResponseAvatar* avatar;
/**
 */
@property (nonatomic, strong) NSString* externalId;
/**
 */
@property (nonatomic, strong) NSArray* aidConfigurations;
/**
 */
@property (nonatomic, strong) NSString* uniqueId;
/**
 */
@property (nonatomic, strong) NSString* cnp_merchant_identifier;
/**
 */
@property (nonatomic, strong) NSString* cnp_tac_default;
/**
 */
@property (nonatomic, strong) NSString* cnp_tac_denial;
/**
 */
@property (nonatomic, strong) NSString* cnp_tac_online;
/**
 */
@property (nonatomic, strong) NSString* cnp_target_percentage;
/**
 */
@property (nonatomic, strong) NSString* cnp_max_target_percentage;
/**
 */
@property (nonatomic, strong) NSString* cnp_treshold_value;
/**
 */
@property (nonatomic, strong) NSString* cnp_floor_limit;
/**
 */
@property (nonatomic) BOOL needsPasswordUpdate;
/**
 */
@property (nonatomic) NSInteger tc_expires_in;
@end


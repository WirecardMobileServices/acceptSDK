//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

/**
 *  @class AcceptTerminalAidConfig
 *  @discussion Terminal AID configuration - these are EMV configurations for the current terminal
 **/
@interface AcceptTerminalAidConfig : NSObject
/// Floor limit
@property (nonatomic, strong) NSString * emvFloorLimit;
// Application version number
@property (nonatomic, strong) NSString * emvApplicationVersionNumber ;
/// Force Online flag
@property (nonatomic, strong) NSString * emvForceOnline;
/// Configuration version
@property (nonatomic, strong) NSString * configurationVersion;
/// TAC online
@property (nonatomic, strong) NSString * emvTacOnline;
/// TDOL
@property (nonatomic, strong) NSString * emvTdol;
/// Acquirer identifier
@property (nonatomic, strong) NSString * acquirerIdentifier;
/// MAX Target %
@property (nonatomic, strong) NSString * emvMaxTargetPercentage;
/// Terminal type
@property (nonatomic, strong) NSString * terminalType;
/// DDOL
@property (nonatomic, strong) NSString * emvDdol;
/// TAC denial
@property (nonatomic, strong) NSString * emvTacDenial;
/// TAC default
@property (nonatomic, strong) NSString * emvTacDefault;
/// Transaction type
@property (nonatomic, strong) NSString * emvTransactionType;
/// Target %
@property (nonatomic, strong) NSString * emvTargetPercentage;
/// Threshold value
@property (nonatomic, strong) NSString * emvThresholdValue;
/// Application name
@property (nonatomic, strong) NSString* emvAppName;

@end

/**
 *  @class AcceptTerminalConfig
 *  @discussion Terminal configuration
 **/
@interface AcceptTerminalConfig : NSObject
/// Terminal capabilities template
@property (nonatomic, strong) NSString * terminalCapabilities;
/// Terminal type
@property (nonatomic, strong) NSString * emvTerminalType;
/// Terminal Additional Capabilities
@property (nonatomic, strong) NSString * terminalAdditionalCapabilities;
/// AID configurations
@property (nonatomic, strong) NSDictionary * aidConfigurations;
/// Merchant category code
@property (nonatomic, strong) NSString * merchantCategoryCode;
/// Transaction category code
@property (nonatomic, strong) NSString * transactionCategoryCode;
/// MID
@property (nonatomic, strong) NSDictionary * applicationMid;
/// TID
@property (nonatomic, strong) NSDictionary * applicationTid;
/// Terminal coutnry code
@property (nonatomic, strong) NSString * terminalCountryCode;
/// POS entry mode
@property (nonatomic, strong) NSString * posEntryMode;
/// Currency code
@property (nonatomic, strong) NSString * currencyCode;
/// Merchant name
@property (nonatomic, strong) NSString * merchantName;

@end

/**
 *  @class AcceptTerminalConfigFiles
 *  @discussion Terminal configuration files
 **/
@interface AcceptTerminalConfigFiles : NSObject
/**
 * @discussion Set URL and version for the config files
 * @param url URL
 * @param version  config file version
 **/
-(void)setURL:(NSString*)url andVersion:(NSString*)version;
/// URL of this config files
-(NSString*)getURL;
/// version of this config files
-(NSString*)getVersion;

@end

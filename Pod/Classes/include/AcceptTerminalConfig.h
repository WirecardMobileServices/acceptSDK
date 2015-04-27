//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

@interface AcceptTerminalAidConfig : NSObject

@property (nonatomic, strong) NSString * emvFloorLimit;
@property (nonatomic, strong) NSString * emvApplicationVersionNumber ;
@property (nonatomic, strong) NSString * emvForceOnline;
@property (nonatomic, strong) NSString * configurationVersion;
@property (nonatomic, strong) NSString * emvTacOnline;
@property (nonatomic, strong) NSString * emvTdol;
@property (nonatomic, strong) NSString * acquirerIdentifier;
@property (nonatomic, strong) NSString * emvMaxTargetPercentage;
@property (nonatomic, strong) NSString * terminalType;
@property (nonatomic, strong) NSString * emvDdol;
@property (nonatomic, strong) NSString * emvTacDenial;
@property (nonatomic, strong) NSString * emvTacDefault;
@property (nonatomic, strong) NSString * emvTransactionType;
@property (nonatomic, strong) NSString * emvTargetPercentage;
@property (nonatomic, strong) NSString * emvThresholdValue;
@property (nonatomic, strong) NSString* emvAppName;

@end

@interface AcceptTerminalConfig : NSObject

@property (nonatomic, strong) NSString * terminalCapabilities;
@property (nonatomic, strong) NSString * emvTerminalType;
@property (nonatomic, strong) NSString * terminalAdditionalCapabilities;

@property (nonatomic, strong) NSDictionary /* NSString -> AcceptTerminalAidConfig */ * aidConfigurations;

@property (nonatomic, strong) NSString * merchantCategoryCode;
@property (nonatomic, strong) NSString * transactionCategoryCode;

@property (nonatomic, strong) NSDictionary * applicationMid;
@property (nonatomic, strong) NSDictionary * applicationTid;

@property (nonatomic, strong) NSString * terminalCountryCode;

@property (nonatomic, strong) NSString * posEntryMode;
@property (nonatomic, strong) NSString * currencyCode;
@property (nonatomic, strong) NSString * merchantName;

@end

@interface AcceptTerminalConfigFiles : NSObject

-(void)setURL:(NSString*)url andVersion:(NSString*)version;
-(NSString*)getURL;
-(NSString*)getVersion;

@end
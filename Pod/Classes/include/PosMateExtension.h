//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import "AcceptExtension.h"
#import "PosMateMessaging.h"
#import "AcceptEncryptedCreditCardEMV.h"
#import "AcceptEncryptedCreditCard.h"

/**
 *  @class PosMateExtension
 *  @discussion Posmate extension
 **/
@interface PosMateExtension : AcceptExtension

/**
 *  @brief Get terminal information
 *  @param completion return the terminal information
 **/
-(void)getTerminalSerialNo:(void (^)(PosMateTerminalInformation*, NSError *))completion;
/**
 *  @brief Upload configuration files to the terminal
 *  @param version configuration version
 *  @param serial serial number
 *  @param completion return the action result
 **/
-(void)uploadConfigFilesToTerminalForVersion:(NSString*)version AndSerial:(NSString*)serial completion:(void (^)(BOOL, NSError *))completion;
/**
 *  @brief Upload firmware file to the terminal
 *  @param firmwareVersion firmware version
 *  @param serial serial number
 *  @param completion return the action result
 **/
-(void)uploadFirmwareToTerminalForVersion:(NSString*)firmwareVersion AndSerial:(NSString*)serial  completion:(void (^)(BOOL, NSError *))completion;
/**
 *  @brief Build accept card information from go online message
 *  @param suplementary Supplementary data obtained by terminal
 *  @return Card EMV details
 **/
+ (AcceptEncryptedCreditCardEMV*) buildAcceptCardFromPosMateGoOnlineSuplementary:(PosmateGoOnlineSuplementary*)suplementary;
/**
 *  @brief Build terminal information from posmate collected information
 *  @param posMateTerminalInfo terminal information obtained natively
 *  @return Accept terminal details
 **/
+ (AcceptExtensionTerminalInfo*) buildAcceptTerminalInfoFromPosMateInfo:(PosMateTerminalInformation*)posMateTerminalInfo;
/**
 *  @brief Set the flag that the signature verification expired
 *  @param timer to replace the current one
 **/
- (void)closeSignatureVerification:(NSTimer *)timer;
/**
 *  @brief Revert the current terminal to stand by mode
 **/
- (void)revertToStandBy;
/**
 *  @brief Set the terminal model by F/W version number
 *  @param version F/W version of the terminal
 **/
- (void)setTerminalModelForVersion:(NSString*)version;
/**
 *  @brief get the terminal model name
 *  @return terminal model name
 **/
- (NSString*) getModelName;
/**
 *  @brief Update the EAA accessory to the connected one by EAA serial number
 *  @param eeSerialNumber Serial number
 *  @return YES if EAA accessory connected
 **/
- (BOOL) updatedConnectedAccessory:(NSString*)eeSerialNumber;
@end

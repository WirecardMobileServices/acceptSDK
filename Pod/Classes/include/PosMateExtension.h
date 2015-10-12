//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 31/03/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import "AcceptExtension.h"
#import "PosMateMessaging.h"
#import "AcceptEncryptedCreditCardEMV.h"
#import "AcceptEncryptedCreditCard.h"

@interface PosMateExtension : AcceptExtension

-(void)getTerminalSerialNo:(void (^)(PosMateTerminalInformation*, NSError *))completion;
-(void)uploadConfigFilesToTerminalForVersion:(NSString*)version AndSerial:(NSString*)serial completion:(void (^)(BOOL, NSError *))completion;
-(void)uploadFirmwareToTerminalForVersion:(NSString*)firmwareVersion AndSerial:(NSString*)serial  completion:(void (^)(BOOL, NSError *))completion;
+ (AcceptEncryptedCreditCardEMV*) buildAcceptCardFromPosMateGoOnlineSuplementary:(PosmateGoOnlineSuplementary*)suplementary;
+ (AcceptExtensionTerminalInfo*) buildAcceptTerminalInfoFromPosMateInfo:(PosMateTerminalInformation*)posMateTerminalInfo;
- (void)closeSignatureVerification:(NSTimer *)timer;
- (void)revertToStandBy;
- (void)setTerminalModelForVersion:(NSString*)version;
- (NSString*) getModelName;
@end

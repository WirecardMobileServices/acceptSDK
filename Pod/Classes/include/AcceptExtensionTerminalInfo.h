//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AcceptExtensionTerminalInfo : NSObject <NSCoding>

@property (nonatomic,strong) NSString * firmwareVersion;
@property (nonatomic,strong) NSString * familyName;
@property (nonatomic,strong) NSString * serialNo;
@property (nonatomic,strong) NSString * vendorSDKVersion;
@property (nonatomic,strong) NSString * terminalId;
@property (nonatomic,strong) NSString * vendor;
@end

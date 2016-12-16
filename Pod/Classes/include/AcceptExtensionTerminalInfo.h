//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptExtensionTerminalInfo
 *  @discussion Brief information for the current terminal
 **/
@interface AcceptExtensionTerminalInfo : NSObject <NSCoding>

/// Firmware version
@property (nonatomic,strong) NSString * firmwareVersion;
/// Device family
@property (nonatomic,strong) NSString * familyName;
/// Serial number
@property (nonatomic,strong) NSString * serialNo;
/// Vendor SDK version
@property (nonatomic,strong) NSString * vendorSDKVersion;
/// device ID
@property (nonatomic,strong) NSString * terminalId;
/// Vendor
@property (nonatomic,strong) NSString * vendor;
@end

//
//  Accept for iOS
//
//  Created by Radoslav Danko on 05/08/14.
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptExtensionPrinterInfo
 *  @discussion Brief information for the current printer
 **/
@interface AcceptExtensionPrinterInfo : NSObject <NSCoding>

/// Firmware version
@property (nonatomic,strong) NSString * firmwareVersion;
/// Device family
@property (nonatomic,strong) NSString * familyName;
/// Serial number
@property (nonatomic,strong) NSString * serialNo;
/// Vendor SDK version
@property (nonatomic,strong) NSString * vendorSDKVersion;
/// device ID
@property (nonatomic,strong) NSString * deviceId;

@end

//
//  Accept for iOS
//
//  Created by Radoslav Danko on 05/08/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AcceptExtensionPrinterInfo : NSObject <NSCoding>

@property (nonatomic,strong) NSString * firmwareVersion;
@property (nonatomic,strong) NSString * familyName;
@property (nonatomic,strong) NSString * serialNo;
@property (nonatomic,strong) NSString * vendorSDKVersion;
@property (nonatomic,strong) NSString * deviceId;

@end

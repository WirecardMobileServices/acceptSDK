//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
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

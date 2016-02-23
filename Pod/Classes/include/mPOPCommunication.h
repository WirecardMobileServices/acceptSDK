//
//  Communication.h
//  mPOP SDK
//
//  Created by Yuji on 2015/06/10.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "SMPort.h"
#import "StarIoExtManager.h"

@interface Communication : NSObject

+ (BOOL)setCommandsData:(NSData *)commands andPort:(SMPort *)port andManager:(StarIoExtManager *)manager andCompletion:(void (^)(BOOL, NSError*))completion;
+ (BOOL)setCommandsDataWithoutCondition:(NSData *)commands andPort:(SMPort *)port;

+ (BOOL)setCommandsData                   :(NSData *)commands andPortName:(NSString *)portName andPortSettings:(NSString *)portSettings andTimeout:(NSInteger)timeout;
+ (BOOL)setCommandsDataWithoutCondition:(NSData *)commands andPortName:(NSString *)portName andPortSettings:(NSString *)portSettings andTimeout:(NSInteger)timeout;

@end

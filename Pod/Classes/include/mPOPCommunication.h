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

/**
 *  @class Communication
 *  @discussion Stario MPOP communication
 **/
@interface Communication : NSObject

/**
 *  @brief Send command data to the device
 *  @param port port to send the data to
 *  @param manager stario manager to send the data to
 *  @param completion completion for the command
 *  @return YES if success
 **/
+ (BOOL)setCommandsData:(NSData *)commands andPort:(SMPort *)port andManager:(StarIoExtManager *)manager andCompletion:(void (^)(BOOL, NSError*))completion;

/**
 *  @brief Send command data
 *  @param port port to send the data to
 *  @return YES if success
 **/
+ (BOOL)setCommandsDataWithoutCondition:(NSData *)commands andPort:(SMPort *)port;

/**
 *  @brief Send command data to the device
 *  @param commands commands to send
 *  @param port port to send the data to
 *  @param portSettings port specific settings
 *  @param timeout communication timeout
 *  @return YES if success
 **/
+ (BOOL)setCommandsData:(NSData *)commands andPortName:(NSString *)portName andPortSettings:(NSString *)portSettings andTimeout:(NSInteger)timeout;
/**
 *  @brief Send command data to the device
 *  @param commands commands to send
 *  @param port port to send the data to
 *  @param portSettings port specific settings
 *  @param timeout communication timeout
 *  @return YES if success
 **/
+ (BOOL)setCommandsDataWithoutCondition:(NSData *)commands andPortName:(NSString *)portName andPortSettings:(NSString *)portSettings andTimeout:(NSInteger)timeout;

@end

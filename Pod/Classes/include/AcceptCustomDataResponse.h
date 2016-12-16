//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptCustomDataResponse
 *  @discussion Custom data for EMV flow
 **/
@interface AcceptCustomDataResponse : NSObject
/// Regular expression to obtain the cardholder name form track2 data equivalent
@property (nonatomic, strong) NSString * ccCardholderRegex;
/// Regular expression to obtain the EFT card number  form track2 data equivalent
@property (nonatomic, strong) NSString * eftCardNumberRegex;
/// Regular expression to obtain the Card number  form track2 data equivalent
@property (nonatomic, strong) NSString * ccCardNumberRegex;
/// Regular expression to recognize the EFT card
@property (nonatomic, strong) NSString * eftRecognitionRegex;

@end

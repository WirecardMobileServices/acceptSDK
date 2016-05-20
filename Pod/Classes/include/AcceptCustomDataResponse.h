//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AcceptCustomDataResponse : NSObject

@property (nonatomic, strong) NSString * ccCardholderRegex;
@property (nonatomic, strong) NSString * eftCardNumberRegex;
@property (nonatomic, strong) NSString * ccCardNumberRegex;
@property (nonatomic, strong) NSString * eftRecognitionRegex;

@end

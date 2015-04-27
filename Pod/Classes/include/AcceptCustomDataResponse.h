//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface AcceptCustomDataResponse : NSObject

@property (nonatomic, strong) NSString * ccCardholderRegex;
@property (nonatomic, strong) NSString * eftCardNumberRegex;
@property (nonatomic, strong) NSString * ccCardNumberRegex;
@property (nonatomic, strong) NSString * eftRecognitionRegex;

@end

//
//  Accept for iOS
//
//  Created by Radoslav Danko on 26/06/2014.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptPaymentParameters
 *  @discussion User payment parameters
 **/
@interface AcceptPaymentParameters : NSObject
/**
 */
@property (nonatomic, strong) NSString * customerEmail;
/**
 */
@property (nonatomic, strong) NSString * customerPhone;
/**
 */
@property (nonatomic)  bool receiptRequested;
/**
 */
@property (nonatomic, strong) NSString * note;
/**
 */
@property (nonatomic, strong) NSString * applicationCryptogram;
@end

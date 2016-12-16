//
//  Accept for iOS
//
//  Created by Radoslav Danko on 26/06/2014.
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 *  @class AcceptPaymentParameters
 *  @discussion User payment parameters
 **/
@interface AcceptPaymentParameters : NSObject
/// Customers email
@property (nonatomic, strong) NSString * customerEmail;
/// Customers phone
@property (nonatomic, strong) NSString * customerPhone;
/// Flag if receipt was requested already
@property (nonatomic)  bool receiptRequested;
/// note
@property (nonatomic, strong) NSString * note;
/// Application crytogram to update the transaction with
@property (nonatomic, strong) NSString * applicationCryptogram;
/// Signature image to update the transaction with
@property (nonatomic, strong) UIImage * signatureImage;
@end

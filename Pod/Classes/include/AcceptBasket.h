//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptBasket
 *  @discussion Basket info class
 **/
@interface AcceptBasket : NSObject
/**
 */
@property (nonatomic, strong) NSString * transactionUniqueId;
/**
 */
@property (nonatomic, readonly) NSMutableArray * items;
/**
 */
@property (nonatomic, strong) NSString * note;
/**
 */
@property NSNumber *lat, *lng;
/**
 */
@property (nonatomic, strong) NSString * currencyAsISO4217Code;
/**
 */
@property (nonatomic, strong) NSNumber * netTaxation;

/**
 *  @brief Calculate the total for the basket
 *  @param handler Number handler efining decimal behaviour
 **/
- (NSDecimalNumber*) total:(NSDecimalNumberHandler*)handler;

/**
 *  @brief Add tip to the basket
 *  @param tip Tip value to be added
 **/
- (void)addTip:(NSInteger)tip;

@end

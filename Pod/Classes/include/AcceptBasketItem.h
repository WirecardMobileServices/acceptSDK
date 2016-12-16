//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/** typedef NS_ENUM(NSInteger, AcceptBasketItemType)
 */
typedef NS_ENUM(NSInteger, AcceptBasketItemType) {
    /**
     */
    ACCEPT_ITEM_CHARGE_TYPE_NORMAL            =0,
    /**
     */
    ACCEPT_ITEM_CHARGE_TYPE_TIP               =1,
    /**
     */
    ACCEPT_ITEM_CHARGE_TYPE_SERVICE_CHARGE    =2
};

/**
 *  @class AcceptBasketItem
 *  @discussion Basket item info
 **/
@interface AcceptBasketItem : NSObject
/// Gross price
@property (nonatomic, strong) NSDecimalNumber * grossPrice;
/// Item note
@property (nonatomic, strong) NSString * note;
/// Quentity
@property (nonatomic) NSUInteger quantity;
/// Tax rate
@property (nonatomic) NSDecimalNumber *taxRate;
/// Item type
@property (nonatomic) AcceptBasketItemType itemType;

/**
 *  @brief Calculate total price according gross value, quantity of items, etc
 *  @param numberHandler defining decimal behaviour
 **/
- (NSDecimalNumber*) totalPrice:(NSDecimalNumberHandler*)numberHandler;

@end

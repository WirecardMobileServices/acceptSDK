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
/**
 */
@property (nonatomic, strong) NSDecimalNumber * grossPrice;
/**
 */
@property (nonatomic, strong) NSString * note;
/**
 */
@property (nonatomic) NSUInteger quantity;
/**
 */
@property (nonatomic) NSDecimalNumber *taxRate;
/**
 */
@property (nonatomic) AcceptBasketItemType itemType;

/**
 *  @brief Calculate total price according gross value, quantity of items, etc
 *  @param numberHandler defining decimal behaviour
 **/
- (NSDecimalNumber*) totalPrice:(NSDecimalNumberHandler*)numberHandler;

@end

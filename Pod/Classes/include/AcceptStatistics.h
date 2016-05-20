//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptStatsEntry
 *  @discussion Statistics entry
 **/
@interface AcceptStatsEntry : NSObject
/**
 */
@property (nonatomic, strong) NSDate * date;
/**
 */
@property (nonatomic) double value;
@end

/**
 *  @class AcceptStatsNestedEntry
 *  @discussion Statistics entry nested (with subcategories for the transaction statuses)
 **/
@interface AcceptStatsNestedEntry : NSObject
/**
 */
@property (nonatomic, strong) NSDate * date;
/**
 */
@property (nonatomic, strong) NSDictionary *nestedStatuses;
@end

/**
 *  @class AcceptStatistics
 *  @discussion Complete statistics class
 **/
@interface AcceptStatistics : NSObject
/**
 */
@property (nonatomic, strong) NSString * currency;
/**
 */
@property (nonatomic, strong) NSArray * turnover;
/**
 */
@property (nonatomic, strong) NSArray * average;
/**
 */
@property (nonatomic, strong) NSArray * count;
/**
 */
@property (nonatomic, strong) NSArray * max;
/**
 */
@property (nonatomic, strong) NSArray * min;
/**
 */
@property (nonatomic) NSUInteger approvedCount;
/**
 */
@property (nonatomic) NSUInteger rejectedCount;
/**
 */
@property (nonatomic) NSUInteger reverseredCount;
/**
 */
@property (nonatomic) NSUInteger refundedCount;
/**
 */
@property (nonatomic) NSUInteger authorizedCount;
/**
 */
@property (nonatomic) NSUInteger preauthorizedCount;
@end


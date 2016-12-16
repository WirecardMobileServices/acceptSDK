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
/// Statistics date
@property (nonatomic, strong) NSDate * date;
/// Statistics value
@property (nonatomic) double value;
@end

/**
 *  @class AcceptStatsNestedEntry
 *  @discussion Statistics entry nested (with subcategories for the transaction statuses)
 **/
@interface AcceptStatsNestedEntry : NSObject
/// Statistics Date
@property (nonatomic, strong) NSDate * date;
/// NEsted statuses
@property (nonatomic, strong) NSDictionary *nestedStatuses;
@end

/**
 *  @class AcceptStatistics
 *  @discussion Complete statistics class
 **/
@interface AcceptStatistics : NSObject
/// Currency
@property (nonatomic, strong) NSString * currency;
/// Turnover for the period specified
@property (nonatomic, strong) NSArray * turnover;
/// Average
@property (nonatomic, strong) NSArray * average;
/// Transaction Count
@property (nonatomic, strong) NSArray * count;
/// Max amount
@property (nonatomic, strong) NSArray * max;
/// Min amount
@property (nonatomic, strong) NSArray * min;
/// Approved transaction count
@property (nonatomic) NSUInteger approvedCount;
/// Rejected transaction count
@property (nonatomic) NSUInteger rejectedCount;
/// Reversed transaction count
@property (nonatomic) NSUInteger reverseredCount;
/// Refunded transaction count
@property (nonatomic) NSUInteger refundedCount;
/// Authorized transaction count
@property (nonatomic) NSUInteger authorizedCount;
/// Preauthorized transaction count
@property (nonatomic) NSUInteger preauthorizedCount;
@end


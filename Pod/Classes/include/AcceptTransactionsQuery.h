//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/** typedef enum AcceptTransactionsQueryOrder
 */
typedef enum {
    /**
     */
    AcceptTransactionsQueryOrderAscending=0,
    /**
     */
    AcceptTransactionsQueryOrderDescending
} AcceptTransactionsQueryOrder;

/** typedef enum AcceptTransactionsQueryOrderBy
 */
typedef enum {
    /**
     */
    AcceptTransactionsQueryOrderByCreatedAt=0,
    /**
     */
    AcceptTransactionsQueryOrderByAmount,
    /**
     */
    AcceptTransactionsQueryOrderByName
} AcceptTransactionsQueryOrderBy;

/**
 *  @class AcceptTransactionsQuery
 *  @discussion Transaction query class used in payment searches
 **/
@interface AcceptTransactionsQuery : NSObject
/**
 */
@property (nonatomic) NSUInteger page;
/**
 */
@property (nonatomic) NSUInteger pageSize;
/**
 */
@property (nonatomic, strong) NSString * queryPhrase;
/**
 */
@property (nonatomic, strong) NSSet * statuses;
/**
 */
@property (nonatomic) AcceptTransactionsQueryOrder orderSort;
/**
 */
@property (nonatomic) AcceptTransactionsQueryOrderBy orderBy;
@end


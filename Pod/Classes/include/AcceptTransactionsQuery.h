//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/** typedef enum AcceptTransactionsQueryOrder
 */
typedef enum {
    ///Ascending order
    AcceptTransactionsQueryOrderAscending=0,
    /// Descending order
    AcceptTransactionsQueryOrderDescending
} AcceptTransactionsQueryOrder;

/** typedef enum AcceptTransactionsQueryOrderBy
 */
typedef enum {
    /// Ordered by creation date
    AcceptTransactionsQueryOrderByCreatedAt=0,
    /// Order by amount
    AcceptTransactionsQueryOrderByAmount,
    /// Order by name
    AcceptTransactionsQueryOrderByName
} AcceptTransactionsQueryOrderBy;

/**
 *  @class AcceptTransactionsQuery
 *  @discussion Transaction query class used in payment searches
 **/
@interface AcceptTransactionsQuery : NSObject
/// Page
@property (nonatomic) NSUInteger page;
/// Page size
@property (nonatomic) NSUInteger pageSize;
/// Query phrase
@property (nonatomic, strong) NSString * queryPhrase;
/// Statuses
@property (nonatomic, strong) NSSet * statuses;
/// Sort order
@property (nonatomic) AcceptTransactionsQueryOrder orderSort;
/// Order by
@property (nonatomic) AcceptTransactionsQueryOrderBy orderBy;
@end


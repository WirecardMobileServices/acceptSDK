//
//  RequestViewController.m
//  Accept Demo
//
//  Created by Fortes, Francisco on 12/9/14.
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import "RequestViewController.h"

#import "Utils.h"

@interface RequestViewController ()

@property (nonatomic, weak) IBOutlet UITextField *searchTf;
@property (nonatomic, weak) IBOutlet UISegmentedControl *mainSC;
@property (nonatomic, weak) IBOutlet UISegmentedControl *secondarySC;
@property (nonatomic, weak) IBOutlet UIButton *requestB;
@property (nonatomic, weak) IBOutlet UITextView *textV;
@property (nonatomic, weak) Accept *accept;
@property (strong, nonatomic) NSTimer *searchTimer;

typedef enum {
    EnumSearch = 0, EnumStatistics
} EnumMainSegment;
typedef enum {
    EnumApproved = 0, EnumRejected, EnumReversed, EnumAll
} EnumSecondarySearchSegment;
typedef enum {
    EnumWeekly = 0, EnumMonthly, EnumQuaterly, EnumYearly
} EnumSecondaryStatsSegment;

@end

@implementation RequestViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.accept = [[Utils sharedInstance] accept];
    [self.mainSC setSelectedSegmentIndex:0];
    [self.secondarySC setSelectedSegmentIndex:3];
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(tokenDidExpire)
                                                 name:kTokenTimerNotificationName
                                               object:nil];
    
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(applicationEnteredForeground:)
                                                 name:UIApplicationWillEnterForegroundNotification
                                               object:nil];
    
    [self.textV setEditable:NO];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];

}

#pragma mark - General Methods (TextField, SegmentedControler, etc)

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
    NSLog(@">>> RequestViewController - textFieldShouldReturn");
    [self onTapBackground:nil];
    return YES;
}

-(IBAction)onTapBackground:(id)sender
{
    NSLog(@">>> RequestViewController - onTapBackground");
    [self.searchTf resignFirstResponder];
}

-(IBAction)segmentChanged:(id)sender
{
    NSLog(@">>> RequestViewController - segmentChanged");
    switch (self.mainSC.selectedSegmentIndex)
    {
        case EnumSearch:
            [self.searchTf setEnabled:YES];
            [self.secondarySC setTitle:@"Approved" forSegmentAtIndex:EnumApproved];
            [self.secondarySC setTitle:@"Rejected" forSegmentAtIndex:EnumRejected];
            [self.secondarySC setTitle:@"Reversed" forSegmentAtIndex:EnumReversed];
            [self.secondarySC setTitle:@"All" forSegmentAtIndex:EnumAll];
            break;
            
        case EnumStatistics:
            [self.searchTf setEnabled:NO];
            [self.secondarySC setTitle:@"Weekly" forSegmentAtIndex:EnumWeekly];
            [self.secondarySC setTitle:@"Monthly" forSegmentAtIndex:EnumMonthly];
            [self.secondarySC setTitle:@"Quaterly" forSegmentAtIndex:EnumQuaterly];
            [self.secondarySC setTitle:@"Yearly" forSegmentAtIndex:EnumYearly];
            break;
            
        default:
            break;
    }
}

-(IBAction)opTapRequest:(id)sender
{
    NSLog(@">>> RequestViewController - opTapRequest");
    [self onTapBackground:nil];
    
    if ([[Utils sharedInstance] tokenExpired])
    {
        [Utils showAlertWithTitle:@"Error" andMessage:@"The token expired, please login again"];
        return;
    }
    
    switch (self.mainSC.selectedSegmentIndex)
    {
        case EnumSearch:
            [self doSearchRequest];
            break;
            
        case EnumStatistics:
            [self doStatisticsRequest];
            break;
        default:
            break;
    }
}

- (void)applicationEnteredForeground:(NSNotification *)notification
{
    NSLog(@">>> RequestViewController - Application Entered Foreground");
    [self.textV setTextColor:([[Utils sharedInstance] tokenIsValid])? [UIColor blackColor] : [UIColor redColor]];
    [self.textV setText:([[Utils sharedInstance] tokenIsValid])? @"Valid token" : @"Token expired or empty, please login"];
}

-(void)tokenDidExpire
{
    NSLog(@">>> RequestViewController - tokenDidExpire");
    [self.textV setTextColor:[UIColor redColor]];
    [self.textV setText:@"Token expired, please login again"];
}

#pragma mark Search Methods

-(void)doSearchRequest
{
    NSLog(@">>> RequestViewController - doSearchRequest");
    NSMutableDictionary *dict = [[NSMutableDictionary alloc] init];
    [dict setObject:[NSString stringWithFormat:@"%d", 1] forKey:@"page"]; //Increase value here to do paging
    [dict setObject:[NSString stringWithFormat:@"%d", 5] forKey:@"pageSize"]; //The value is up to you. It is recommended not to request more than 20
    [dict setObject:@"date" forKey:@"orderBy"];
    /*
     Other possible orders are:
     [dict setObject:@"name" forKey:@"orderBy"];
     [dict setObject:@"amount" forKey:@"orderBy"];
     */
    NSString *preparedQueryString = self.searchTf.text;
    if (preparedQueryString.length > 0 && [Utils isTheStringAnActualYear:self.searchTf.text]) //Is it a year?
    {
        preparedQueryString = [@"\"" stringByAppendingString:preparedQueryString];
        preparedQueryString = [preparedQueryString stringByAppendingString:@"/\""];//Backend accepts years only with format "2014/", and the quotation marks have to be added as well
    }
    else if (preparedQueryString.length > 0 && [Utils isTheString:self.searchTf.text ANumberWithSeparator:@".:-"]) //Is it a date or partial date?
    {
        //Prepare date string for backend
        preparedQueryString = [[Utils sharedInstance] stringDateForServerFromString:preparedQueryString];
    }
    else if (preparedQueryString.length > 0 && [Utils isTheString:self.searchTf.text ANumberWithSeparator:@","]) //Is it a number with decimals?
    {
        //Backend does not accept decimal separators
        preparedQueryString = [preparedQueryString stringByReplacingOccurrencesOfString:@"," withString:@""];
    }
    
    [dict setObject:@"0" forKey:@"ascending"];
    [dict setObject:preparedQueryString forKey:@"query"];
    
    if (self.secondarySC.selectedSegmentIndex != EnumAll)
    {
        switch (self.secondarySC.selectedSegmentIndex)
        {
            case EnumApproved:
                [dict setObject:@"approved" forKey:@"status"];
                break;
            case EnumRejected:
                [dict setObject:@"rejected" forKey:@"status"];
                break;
            case EnumReversed:
                [dict setObject:@"reversed" forKey:@"status"];
                break;
            /*There is another status, refunded, but its usage it is not recommended as it has extra cost:
                [dict setObject:@"refunded" forKey:@"status"];
            */
            default:
                break;
        }
    }
    
    [self.textV setTextColor:[UIColor blackColor]];
    [self.textV setText:@"Requesting search..."];
    
    if (self.searchTimer && [self.searchTimer isValid])
    {
        [self.searchTimer invalidate];
    }
    
    self.searchTimer = nil;
    self.searchTimer = [NSTimer scheduledTimerWithTimeInterval:kHistoryTimer target:self selector:@selector(historyTimerTimeout) userInfo:nil repeats:NO];
    
    void(^completionBlock)(NSArray *, NSError*) = ^(NSArray *arrResults, NSError *error)
    {
        if ([self.searchTimer isValid])
        {
            [self.searchTimer invalidate];
        }
        
        if (error)
        {
            [self.textV setTextColor:[UIColor redColor]];
            if (error.code == AcceptTransactionsQueryNoConnectionErrorCode)
            {
                [self.textV setText:@"Please check your internet connection"];
                return;
            }
            else if (error.code == AcceptTransactionsQueryTokenExpiredErrorCode)
            {
                [self.textV setText:@"Your session has expired. Please login again"];
                return;
            }
        }
        else
        {
            if ([arrResults count] == 0)
            {
                [self.textV setText:@"No data to show. Did you make a transaction with your user?"];
            }
            else
            {
                NSMutableString *summary = [NSMutableString stringWithString: @"Results:\n"];
                for (AcceptTransaction *transaction in arrResults)
                {
                    [summary appendString:[NSString stringWithFormat:@"Transaction uid:%@ amount:%d createdAt:%@ cardNumber:%@ by:%@ %@ \n\n", transaction.guwid, transaction.amount, transaction.createdAt, transaction.cardNumber, transaction.cardHolderFirstName, transaction.cardHolderLastName]];
                }
                [self.textV setTextColor:[UIColor blackColor]];
                [self.textV setText:summary];
            }
        }
    };
    
    AcceptTransactionsQuery *query = [[AcceptTransactionsQuery alloc] init];
    int page= [[dict valueForKey:@"page"] integerValue];
    query.page = page <= 0 ? 1 : page;
    query.pageSize = [[dict valueForKey:@"pageSize"] integerValue];
    NSString *orderBy = [dict valueForKey:@"orderBy"];
    query.orderSort = [[dict valueForKey:@"ascending"] intValue] == 1 ? AcceptTransactionsQueryOrderAscending : AcceptTransactionsQueryOrderDescending;
    
    if ( [orderBy isEqualToString:@"name"])
    {
        query.orderBy = AcceptTransactionsQueryOrderByName;
    }
    else if ( [orderBy isEqualToString:@"amount"])
    {
        query.orderBy = AcceptTransactionsQueryOrderByAmount;
    }
    else
    {
        query.orderBy = AcceptTransactionsQueryOrderByCreatedAt;
    }
    
    NSString *status = [dict valueForKey:@"status"];
    if (status.length >0) query.statuses = [NSSet setWithObject:status];
    NSString *strQuery = [dict valueForKey:@"query"];
    if (strQuery) query.queryPhrase = strQuery;

    [self.accept queryTransactions:[[Utils sharedInstance]accessToken] config:[[Utils sharedInstance] backendConfig] query:query completion:^(NSArray *arr, NSError *error)
    {
        completionBlock(arr, error);
    }];
}

-(void)historyTimerTimeout
{
    NSLog(@">>> RequestViewController - historyTimerTimeout");
    [self.textV setTextColor:[UIColor redColor]];
    [self.textV setText:@"Server is taken to long to respond. Timeout."];
}

#pragma Statistics Methods

-(void)doStatisticsRequest
{
    NSLog(@">>> RequestViewController - doStatisticsRequest");
    AcceptStatisticsGroupBy accessGroupBy;
    
    switch (self.secondarySC.selectedSegmentIndex)
    {
        case EnumWeekly:
            accessGroupBy = AcceptStatisticsGroupByDay;
            break;
        case EnumMonthly:
            accessGroupBy = AcceptStatisticsGroupByMonth;
            break;
        case EnumQuaterly:
            accessGroupBy = AcceptStatisticsGroupByQuarter;
            break;
        case EnumYearly:
        default:
            accessGroupBy = AcceptStatisticsGroupByYear;
            break;
    }
    
    if (self.searchTimer && [self.searchTimer isValid])
    {
        [self.searchTimer invalidate];
    }
    self.searchTimer = nil;
    self.searchTimer = [NSTimer scheduledTimerWithTimeInterval:kHistoryTimer target:self selector:@selector(historyTimerTimeout) userInfo:nil repeats:NO];
    
    void(^completionBlock)(AcceptStatistics *, NSError *) = ^(AcceptStatistics *results, NSError *error)
    {
        if ([self.searchTimer isValid])
        {
            [self.searchTimer invalidate];
        }
        
        if (error)
        {
            [self.textV setTextColor:[UIColor redColor]];
            if (error.code == AcceptTransactionsQueryNoConnectionErrorCode)
            {
                [self.textV setText:@"Please check your internet connection"];
                return;
            }
            else if (error.code == AcceptTransactionsQueryTokenExpiredErrorCode)
            {
                [self.textV setText:@"Your session has expired. Please login again"];
                return;
            }
        }
        else
        {
            if (!results || results.turnover.count == 0)
            {
                [self.textV setText:@"No data to show. Did you make a transaction with your user?"];
            }
            else
            {
                NSMutableString *summary = [NSMutableString stringWithString:@"Result turnover\n"];
                if (results.turnover)
                {
                    for (AcceptStatsNestedEntry *entry in results.turnover)
                    {
                        if (entry.nestedStatuses && entry.nestedStatuses.allKeys.count > 0)
                        {
                            [summary appendString:[NSString stringWithFormat:@"%@ %@\n", [[Utils sharedInstance].dateFormatter stringFromDate:entry.date], entry.nestedStatuses]];
                        }
                    }
                }
                [summary appendString:@"\n\nResults average:\n"];
                if (results.average)
                {
                    for (AcceptStatsNestedEntry *entry in results.average)
                    {
                        if (entry.nestedStatuses && entry.nestedStatuses.allKeys.count > 0)
                        {
                            [summary appendString:[NSString stringWithFormat:@"%@ %@\n", [[Utils sharedInstance].dateFormatter stringFromDate:entry.date], entry.nestedStatuses]];
                        }
                    }
                }
                [summary appendString:@"\n\nResults min:\n"];
                if (results.average)
                {
                    for (AcceptStatsNestedEntry *entry in results.min)
                    {
                        if (entry.nestedStatuses && entry.nestedStatuses.allKeys.count > 0)
                        {
                            [summary appendString:[NSString stringWithFormat:@"%@ %@\n", [[Utils sharedInstance].dateFormatter stringFromDate:entry.date], entry.nestedStatuses]];
                        }
                    }
                }
                [summary appendString:@"\n\nResults max:\n"];
                if (results.average)
                {
                    for (AcceptStatsNestedEntry *entry in results.max)
                    {
                        if (entry.nestedStatuses && entry.nestedStatuses.allKeys.count > 0)
                        {
                            [summary appendString:[NSString stringWithFormat:@"%@ %@\n", [[Utils sharedInstance].dateFormatter stringFromDate:entry.date], entry.nestedStatuses]];
                        }
                    }
                }
                
                [self.textV setTextColor:[UIColor blackColor]];
                [self.textV setText:summary];
            }
        }
    };

    [self.accept queryStatistics:[[Utils sharedInstance] accessToken] config:[[Utils sharedInstance] backendConfig]
                            from:[NSDate dateWithTimeInterval:-1036800 sinceDate:[NSDate date]] //one year ago
                              to:[NSDate date]
                         groupBy:accessGroupBy
                    resultsGroup:@[@(AcceptStatisticsOnlyMaxMin),@(AcceptStatisticsOnlyAverage),@(AcceptStatisticsOnlyTurnover)]
                   statusNesting:YES //set to NO for a simpler response
                      completion:^(AcceptStatistics *dict, NSError *error)
                     {
                          completionBlock(dict, error);
                      }];
}

@end

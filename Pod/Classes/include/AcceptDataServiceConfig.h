//
//  Accept for iOS
//
//  Created by Damian Kolakowski on 11/02/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptDataServiceConfig
 *  @discussion Configuration of the backend connection
 **/
@interface AcceptDataServiceConfig : NSObject
/**
 */
@property (nonatomic, strong) NSString * url;
/**
 * Where should the response from the web service be sent to
 */
@property (nonatomic, strong) NSString * callbackUrl;
/**
 */
@property (nonatomic, strong) NSString * clientId;
/**
 */
@property (nonatomic, strong) NSString * clientSecret;
@end

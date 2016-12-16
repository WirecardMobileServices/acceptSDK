//
//  Accept for iOS
//
//  Created by Radoslav Danko and Francisco Fortes
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 *  @class AcceptDataServiceConfig
 *  @discussion Configuration of the backend connection
 **/
@interface AcceptDataServiceConfig : NSObject
/// URL for the data service
@property (nonatomic, strong) NSString * url;
/**
 * Where should the response from the web service be sent to
 */
@property (nonatomic, strong) NSString * callbackUrl;
/// OAUTH Client ID
@property (nonatomic, strong) NSString * clientId;
/// OAUTH Client secret
@property (nonatomic, strong) NSString * clientSecret;
@end

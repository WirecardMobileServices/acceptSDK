//
//  Accept for iOS
//
//  Created by Radoslav Danko on 05/08/14.
//  Copyright (c) 2014 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Accept.h"
#import "AcceptExtensionPrinterInfo.h"

@interface AcceptPrinterExtension : NSObject

- (void) discoverDevices:(void (^)(NSArray *, NSError*))completionBlock;

- (void) startPrint:(AcceptPrinterConfig*)config
       completion:(void (^)(BOOL, NSError*))completion
         progress:(void (^)(AcceptPrinterStateUpdate))progress;

- (void) cancelPrint;

- (void) openDrawer:(void (^)(BOOL, NSError*))completion;
- (void) connectBarScanner:(void (^)(BOOL, NSError*))completion andDataReceived:(void (^)(NSData*))barcodeDataReceived;

+ (NSError*) discoveryError:(AcceptCommonErrorCode)errorCode description:(NSString*)description;
+ (NSError*) discoveryError:(AcceptCommonErrorCode)errorCode underlyingError:(NSError*)error;

+ (NSError*) printError:(AcceptPrintErrorCode)errorCode description:(NSString*)description;
+ (NSError*) printError:(AcceptPrintErrorCode)errorCode underlyingError:(NSError*)error;

@end

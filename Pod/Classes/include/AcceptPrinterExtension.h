//
//  Accept for iOS
//
//  Created by Radoslav Danko on 05/08/14.
//  Copyright (c) 2016 Wirecard. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Accept.h"
#import "AcceptExtensionPrinterInfo.h"

/**
 *  @class AcceptPrinterExtension
 *  @discussion Printer extension
 **/
@interface AcceptPrinterExtension : NSObject

/**
 * Discover available printers
 * @param completionBlock the completion for the discover method
 **/
- (void) discoverDevices:(void (^)(NSArray *, NSError*))completionBlock;


/**
 * @brief Start printing on the device
 * @param completion the completion for the printing
 * @param progress the progress of the printing
 **/
- (void) startPrint:(AcceptPrinterConfig*)config
       completion:(void (^)(BOOL, NSError*))completion
         progress:(void (^)(AcceptPrinterStateUpdate))progress;

/**
 * @discussion Cancel printing on the device
 * @note The printing process will be canceled only if device allows it
 **/
- (void) cancelPrint;

/**
 * @discussion Open the cash drawer
 * @param Completion for the cash drawer opening
 **/
- (void) openDrawer:(void (^)(BOOL, NSError*))completion;

/**
 * @discussion Connect to barcode scanner
 * @param Completion for the bar code scanner connection
 * @param barcodeDataReceived the barcode data that was read by the scanner
 **/
- (void) connectBarScanner:(void (^)(BOOL, NSError*))completion
           andDataReceived:(void (^)(NSData*))barcodeDataReceived;

/**
 * @discussion Helper function to construct the error
 * @param errorCode error code
 * @param description error description
 **/
+ (NSError*) discoveryError:(AcceptCommonErrorCode)errorCode description:(NSString*)description;
/**
 * @discussion Helper function to construct the error
 * @param errorCode error code
 * @param underlyingError  underlying error
 **/
+ (NSError*) discoveryError:(AcceptCommonErrorCode)errorCode underlyingError:(NSError*)error;
/**
 * @discussion Helper function to construct the printing error
 * @param erroCode error code
 * @param description error description
 **/
+ (NSError*) printError:(AcceptPrintErrorCode)errorCode description:(NSString*)description;
/**
 * @discussion Helper function to construct the printing error
 * @param erroCode error code
 * @param underlyingError  underlying error
 **/
+ (NSError*) printError:(AcceptPrintErrorCode)errorCode underlyingError:(NSError*)error;

@end

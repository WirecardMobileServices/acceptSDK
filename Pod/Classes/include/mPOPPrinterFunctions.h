//
//  PrinterFunctions.h
//  mPOP SDK
//
//  Created by Yuji on 2015/06/10.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "StarIoExt.h"

/**
 *  @class PrinterFunctions
 *  @discussion Stario MPOP printer functions
 **/
@interface PrinterFunctions : NSObject

/**
 *  @brief Example command line receipt
 *  @return data for command line receipt
 **/
+ (NSData *)commandLineModeReceipt;
/**
 *  @brief Example raster  receipt
 *  @return data for raster receipt
 **/
+ (NSData *)commandRasterModeReceipt:(NSInteger)width;
/**
 *  @brief Example raster  receipt
 *  @param bothsScale scaling for receipt
 *  @return data for raster receipt
 **/
+ (NSData *)commandRasterModeReceipt:(NSInteger)width andBothScale:(BOOL)bothScale;
/**
 *  @brief Example raster  receipt
 *  @param rotation rotation for receipt
 *  @param image image receipt
 *  @return data for raster receipt
 **/
+ (NSData *)commandRasterModeCoupon:(NSInteger)width andRotation:(SCBBitmapConverterRotation)rotation andUIImage:(UIImage*)image;
/**
 *  @brief open cash drawer
 *  @param number command type
 *  @return data for command to open the cash drawer
 **/
+ (NSData *)commandOpenCashDrawer:(NSUInteger)number;

@end

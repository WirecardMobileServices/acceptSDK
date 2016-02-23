//
//  PrinterFunctions.h
//  mPOP SDK
//
//  Created by Yuji on 2015/06/10.
//  Copyright (c) 2015年 Star Micronics. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "StarIoExt.h"

@interface PrinterFunctions : NSObject

+ (NSData *)commandLineModeReceipt;

+ (NSData *)commandRasterModeReceipt:(NSInteger)width;
+ (NSData *)commandRasterModeReceipt:(NSInteger)width andBothScale:(BOOL)bothScale;

+ (NSData *)commandRasterModeCoupon:(NSInteger)width andRotation:(SCBBitmapConverterRotation)rotation andUIImage:(UIImage*)image;

+ (NSData *)commandOpenCashDrawer:(NSUInteger)number;

@end

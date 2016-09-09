//
//  BarCodeScannerIOS.h
//
//  Created by Danko, Radoslav on 07/03/16.
//  Copyright © 2016 andromeda. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@protocol BarCodeScannerIOSDelegate
-(void)finishedBarcodeScan:(NSString *)barcodeData canceled:(BOOL)canceled;
@end

@interface BarCodeScannerIOS : UIView
-(instancetype)initWithView:(UIView *)parentView ;
@property (nonatomic,weak) id delegate;
@end

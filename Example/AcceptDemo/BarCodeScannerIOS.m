//
//  BarCodeScannerIOS.m
//
//  Created by Danko, Radoslav on 07/03/16.
//  Copyright © 2016 andromeda. All rights reserved.
//

#import "BarCodeScannerIOS.h"
#import <ImageIO/CGImageProperties.h>
#import <AVFoundation/AVFoundation.h>
#import "Utils.h"

@interface BarCodeScannerIOS ()<AVCaptureMetadataOutputObjectsDelegate>
{
    AVCaptureSession *_session;
    AVCaptureDevice *_device;
    AVCaptureDeviceInput *_input;
    AVCaptureMetadataOutput *_output;
    AVCaptureStillImageOutput *_stillOutput;
    AVCaptureVideoPreviewLayer *_prevLayer;
    NSString *detectionString;
 }

@end

@implementation BarCodeScannerIOS

#pragma mark - Custom Methods
-(instancetype)initWithView:(UIView *)parentView{
    
    UIWindow *mainWindow = [[[UIApplication sharedApplication] windows] firstObject];
    
    self = [super initWithFrame:mainWindow.frame];
    
    if (self) {

        [mainWindow addSubview:self];
        
        [UIView animateWithDuration:0.5 animations:^{
            self.layer.backgroundColor = [[UIColor colorWithRed:0 green:0 blue:0 alpha:0.8] CGColor];
        } completion:^(BOOL finished) {
            dispatch_async(dispatch_get_main_queue(), ^{
                [self startCaptureIOS];
            });
            
        }];

        return self;
    }
    return nil;
}


-(void)startCaptureIOS{
    _session = [[AVCaptureSession alloc] init];
    _session.sessionPreset = AVCaptureSessionPresetMedium;
    
    _device = [AVCaptureDevice defaultDeviceWithMediaType:AVMediaTypeVideo];
    NSError *error = nil;
    
    _input = [AVCaptureDeviceInput deviceInputWithDevice:_device error:&error];
    if (_input) {
        [_session addInput:_input];
    } else {
        NSLog(@"Error: %@", error);
    }
    
    //live video output
    _output = [[AVCaptureMetadataOutput alloc] init];
    [_output setMetadataObjectsDelegate:self queue:dispatch_get_main_queue()];
    [_session addOutput:_output];
    
    _output.metadataObjectTypes = [_output availableMetadataObjectTypes];

    //add Label
    UILabel *scanLabel = [[UILabel alloc] initWithFrame:CGRectMake(0, ((self.frame.size.height-300)/2)-30, self.frame.size.width, 30)];
    scanLabel.textColor = [UIColor whiteColor];
    scanLabel.textAlignment = NSTextAlignmentCenter;
    scanLabel.font = [UIFont systemFontOfSize:22];
    scanLabel.tag = 1234;
    scanLabel.text = NSLocalizedString(@"Hold up to a barcode to scan", @"Hold up to a barcode to scan");
    [self addSubview:scanLabel];
    
    //add Cancel
    UIButton *btnCancel = [[UIButton alloc] initWithFrame:CGRectMake(0, self.frame.size.height-50, self.frame.size.width, 50)];

    [btnCancel setTitle:NSLocalizedString(@"Cancel", @"Cancel") forState:UIControlStateNormal];
    [btnCancel addTarget:self action:@selector(onTapCancel:) forControlEvents:UIControlEventTouchUpInside];

    [self addSubview:btnCancel];
    
    _prevLayer = [AVCaptureVideoPreviewLayer layerWithSession:_session];
    CGRect rect = CGRectMake((self.frame.size.width-300)/2, (self.frame.size.height-300)/2, 300, 300);
    
    _prevLayer.frame = rect;
    _prevLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;
    [self.layer addSublayer:_prevLayer];
    
    //still image output
    _stillOutput = [[AVCaptureStillImageOutput alloc] init];
    NSDictionary *outputSettings = [[NSDictionary alloc] initWithObjectsAndKeys: AVVideoCodecJPEG, AVVideoCodecKey, nil];
    [_stillOutput setOutputSettings:outputSettings];
    
    [_session addOutput:_stillOutput];
    
    [_session startRunning];
    
}

-(IBAction)onTapCancel:(id)sender{
    [self stopCaptureIOS];
    detectionString = nil;
    [self dismiss:YES];

}

-(void)stopCaptureIOS{
    
    
    [_session stopRunning];
    [_prevLayer removeFromSuperlayer ];
    _session = nil;
    _prevLayer = nil;
    _stillOutput = nil;
    _output = nil;
    _device = nil;
    _input = nil;
}

-(void)dismiss:(BOOL)byTapping{
    [UIView animateWithDuration:0.5 animations:^{
        self.alpha = 0.0;
    } completion:^(BOOL finished) {
        [self removeFromSuperview];
        [self.delegate finishedBarcodeScan:detectionString canceled:byTapping];
    }];
}

- (void)captureOutput:(AVCaptureOutput *)captureOutput didOutputMetadataObjects:(NSArray *)metadataObjects fromConnection:(AVCaptureConnection *)connection
{
    CGRect highlightViewRect = CGRectZero;
    AVMetadataMachineReadableCodeObject *barCodeObject;
    
    NSArray *barCodeTypes ;
    
    if([[[UIDevice currentDevice] systemVersion] compare:@"8.0" options:NSNumericSearch] == NSOrderedAscending ){
        
        barCodeTypes = @[AVMetadataObjectTypeUPCECode, AVMetadataObjectTypeCode39Code, AVMetadataObjectTypeCode39Mod43Code,
                         AVMetadataObjectTypeEAN13Code, AVMetadataObjectTypeEAN8Code, AVMetadataObjectTypeCode93Code, AVMetadataObjectTypeCode128Code,
                         AVMetadataObjectTypePDF417Code, AVMetadataObjectTypeQRCode, AVMetadataObjectTypeAztecCode];
    }
    else{
        barCodeTypes = @[AVMetadataObjectTypeUPCECode, AVMetadataObjectTypeCode39Code, AVMetadataObjectTypeCode39Mod43Code,
                         AVMetadataObjectTypeEAN13Code, AVMetadataObjectTypeEAN8Code, AVMetadataObjectTypeCode93Code, AVMetadataObjectTypeCode128Code,
                         AVMetadataObjectTypePDF417Code, AVMetadataObjectTypeQRCode, AVMetadataObjectTypeAztecCode,AVMetadataObjectTypeITF14Code,AVMetadataObjectTypeDataMatrixCode];
        
    }
    
    for (AVMetadataObject *metadata in metadataObjects) {
        for (NSString *type in barCodeTypes) {
            if ([metadata.type isEqualToString:type])
            {
                barCodeObject = (AVMetadataMachineReadableCodeObject *)[_prevLayer transformedMetadataObjectForMetadataObject:(AVMetadataMachineReadableCodeObject *)metadata];
                highlightViewRect = barCodeObject.bounds;
                detectionString = [(AVMetadataMachineReadableCodeObject *)metadata stringValue];
                break;
            }
        }
        
        if (detectionString.length > 0) {
            [_session stopRunning];
        }
        break;
        
    }

    
    if (detectionString.length > 0) {
        [self stopCaptureIOS];
    }
    
    [self dismiss:NO];

}
@end

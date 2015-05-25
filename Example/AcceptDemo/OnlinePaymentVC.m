//
//  OnlinePayment.m
//  acceptSDK
//
//  Created by Danko, Radoslav on 22/05/15.
//  Copyright (c) 2015 radoslav.danko. All rights reserved.
//

#import "OnlinePaymentVC.h"
#import "Accept.h"
#import "Utils.h"

@interface OnlinePaymentVC ()
@property (weak, nonatomic) IBOutlet UITextField *tfAmount;
@property (weak, nonatomic) IBOutlet UITextField *tfCurrency;
@property (weak, nonatomic) IBOutlet UIButton *btnPay;
@property (weak, nonatomic) IBOutlet UITextView *tvInformation;

@end

@implementation OnlinePaymentVC

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

#pragma mark - Custom Methods
- (IBAction)onTapPayOnline:(id)sender {
    
    if (self.tfAmount.text.length == 0) {
        UIAlertView *a = [[UIAlertView alloc] initWithTitle:@"Amount" message:@"Amount is required" delegate:self cancelButtonTitle:nil otherButtonTitles:@"OK",nil];
        [a show];
        
        return;
    }
    
    void(^completion)(NSDictionary *, NSError *) = ^(NSDictionary *paymentResult, NSError *error){
        
        [self.tvInformation setText:[NSString stringWithFormat:@"result:%@\nerror:%@",paymentResult,error]];
         
    };
    
   Accept * accept = [[Utils sharedInstance] accept];
    
    [accept startCardPayment:[self.tfAmount.text intValue]  currency:self.tfCurrency.text locale:@"en" token:nil parentViewController:self completion:completion];
}

@end

//
//  Accept_DemoTests.m
//  Accept DemoTests
//
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>
#import "ZipArchive.h"
#ifdef ACCEPT_SDK_SOURCE_AVAILABLE
    #import <Accept/Accept.h>
#else
    #import <acceptSDK/Accept.h>
#endif

#import "Utils.h"

#define testUsername @"YOUR_USERNAME"
#define testPassword @"YOUR_PASSWORD"
#define MANUAL_TESTS  NO

@interface Accept_DemoTests : XCTestCase
@property (nonatomic, strong) Accept *accept;
@end

@implementation Accept_DemoTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
    self.accept = [[Accept alloc] init];
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
    self.accept = nil;
}
-(AcceptBasketItem *)addBasketItem:(NSInteger)quantity amount:(NSDecimalNumber *)amount note:(NSString *)note tax:(int)tax chargeType:(NSString*)chargeType
{
    
    AcceptBasketItem *basketItem= [[AcceptBasketItem alloc] init];
    basketItem.quantity = quantity;
    NSDecimalNumber *decAmount = amount;
    decAmount = [decAmount decimalNumberByDividingBy:[NSDecimalNumber decimalNumberWithString:@"100"]];
    basketItem.grossPrice =  decAmount;
    basketItem.note = note;
    NSDecimalNumber *decTax = [NSDecimalNumber decimalNumberWithString:[NSString stringWithFormat:@"%d",tax]];
    decTax = [decTax decimalNumberByDividingBy:[NSDecimalNumber decimalNumberWithString:@"10000"]];
    basketItem.taxRate = decTax ;
    if ([chargeType isEqualToString:CHARGE_TYPE_SERVICE])
    {
        basketItem.itemType = ACCEPT_ITEM_CHARGE_TYPE_SERVICE_CHARGE;
    }
    else if ([chargeType isEqualToString:CHARGE_TYPE_TIP])
    {
        basketItem.itemType = ACCEPT_ITEM_CHARGE_TYPE_TIP;
    }
    else
    {
        basketItem.itemType = ACCEPT_ITEM_CHARGE_TYPE_NORMAL;
    }
    return basketItem;
}
- (void)testDiscoverSupportedVendorsAndTerminals {
    
    //Check Vendors
    __weak XCTestExpectation *expectation = [self expectationWithDescription:@"Get supported Terminals"];
    __block NSArray <AcceptTerminalVendor*>* returnedArr;
    
    
    
    void (^completion)(NSArray *) = ^(NSArray *arr) {
        returnedArr = arr;
        [expectation fulfill];
    };
    
    [self.accept discoverSupportedVendors:completion];
    
    
    
    [self waitForExpectationsWithTimeout:15 handler:nil];
    
    for (AcceptTerminalVendor *item in returnedArr){
        NSLog(@"vendor: %@",item.displayName);
    }
    
    BOOL returnedObjectsAreAcceptTerminals = returnedArr.count > 0;
    
    XCTAssertTrue(returnedObjectsAreAcceptTerminals,
                  @"should return an array of AcceptTerminalVendor classes");
    
    
    //Check Printer Vendors
    expectation = [self expectationWithDescription:@"Get supported Printers "];
    
    __block NSArray <AcceptPrinterVendor*>* returnedPrinterVendorsArr;
    
    void (^completionPrinters)(NSArray *) = ^(NSArray *arr) {
        returnedPrinterVendorsArr = arr;
        [expectation fulfill];
    };
    
    [self.accept discoverSupportedPrinterVendors:completionPrinters];
    

    
    [self waitForExpectationsWithTimeout:15 handler:nil];
    
    for (AcceptPrinterVendor *item in returnedPrinterVendorsArr){
        NSLog(@"printer vendor: %@",item.displayName);
    }
    
    BOOL returnedObjectsAreAcceptPrinterVendors = returnedPrinterVendorsArr.count > 0;
    
    XCTAssertTrue(returnedObjectsAreAcceptPrinterVendors,
                  @"should return an array of AcceptPrinterVendor classes");
    
}

//- (void)testMultipleLogin {
//    
//    //Check Vendors
//    __weak XCTestExpectation *expectation = [self expectationWithDescription:@"Login"];
//    __block AcceptAccessToken* retToken;
//    __block NSError* retErr;
//    
//    int i = 0;
//    
//    void (^completion)(AcceptAccessToken*, NSError*) = ^(AcceptAccessToken* token, NSError* error) {
//        retToken = token;
//        retErr = error;
//        if (i == 9) {
//            [expectation fulfill];
//        }
//        
//    };
//    
//    for (i = 0; i< 10; i++) {
//        [self.accept requestAccessToken:@"" password:@"" config:nil completion:completion];
//    }
//    
//    
//    
//    
//    [self waitForExpectationsWithTimeout:55 handler:nil];
//    
//    
//    BOOL returnedTokenIsValid = retToken.accessToken.length > 0;
//    
//    XCTAssertTrue(returnedTokenIsValid,
//                  @"should return access token");
//    
//    
//}

- (void)testSpireTerminalUpdate {

    if (MANUAL_TESTS == NO) {
        NSLog(@"Test to be run only in manual mode - with device attached and terminal paired");
        XCTAssertTrue(YES,
                      @"run only in manual mode");
        return ;
    }
    //Check Vendors
    __weak XCTestExpectation *expectation = [self expectationWithDescription:@"Update Terminal"];
    __block AcceptAccessToken* retToken;
    __block NSError* retErr;
    __block AcceptConfigFilesStatus updateStatus = AcceptConfigFilesStatusTerminalNotReady;

    AcceptTerminalVendor *vendor = [AcceptTerminalVendor new];
    vendor.displayName = @"Spire";
    vendor.uuid = @"PosMateExtension";
    
    void (^completion)(AcceptAccessToken*, NSError*) = ^(AcceptAccessToken* tokenObj, NSError* error) {
        retToken = tokenObj;
        retErr = error;
        
        [self.accept discoverTerminalsForVendor:vendor.uuid completion:^(NSArray *discoveredTerminals, NSError *error)
         {
             if (error)
             {
                 [expectation fulfill];
                 NSLog(@"Error discovering terminals %@", error.description);
             }
             else if (discoveredTerminals.count > 0  )
             {
                 void (^completion)(AcceptConfigFilesStatus , NSError* ) = ^(AcceptConfigFilesStatus status, NSError* error)
                 {
                     updateStatus = status;
                         if (status == AcceptConfigFilesStatusSuccess)
                         {
                             NSLog(@"Terminal configuration updated sucessfully");
                         }
                         else if(status == AcceptConfigFilesStatusUnnecessary){
                             NSLog(@"Terminal configuration update not needed");
                         }
                         else{
                             NSLog(@"Terminal configuration update status:%ld",(long)status);
                         }
                     
                     [expectation fulfill];
                     
                 };
                 
                 void(^progress)(AcceptConfigFilesProgress) = ^(AcceptConfigFilesProgress progress){
                     NSLog(@"Terminal configuration update progress:%ld",(long)progress);
                 };
                 
                 [self.accept  updateTerminal:[discoveredTerminals firstObject] vendor:vendor token:tokenObj.accessToken  config:nil progress:progress completion:completion];
             }
             else{
                 updateStatus = AcceptConfigFilesStatusTerminalNotReady;
                 NSLog(@"No terminals found");
                 [expectation fulfill];
                 
             }
         }];
        
    
    };
    

    [self.accept requestAccessToken:testUsername  password:testPassword config:nil completion:completion];
    
    [self waitForExpectationsWithTimeout:180 handler:nil];
    
    BOOL updateRunOK = updateStatus == AcceptConfigFilesStatusSuccess || updateStatus ==AcceptConfigFilesStatusUnnecessary;

    

    XCTAssertTrue(updateRunOK,
                  @"should return access token");


}

- (void)testSpireTerminalFirmwareUpdate {
    
    if (MANUAL_TESTS == NO) {
        NSLog(@"Test to be run only in manual mode - with device attached and terminal paired");
        XCTAssertTrue(YES,
                      @"run only in manual mode");
        return ;
    }
    //Check Vendors
    __weak XCTestExpectation *expectation = [self expectationWithDescription:@"Update Terminal Firmware"];
    __block AcceptAccessToken* retToken;
    __block NSError* retErr;
    __block AcceptConfigFilesStatus updateStatus;
    
    AcceptTerminalVendor *vendor = [AcceptTerminalVendor new];
    vendor.displayName = @"Spire";
    vendor.uuid = @"PosMateExtension";
    
    void (^completion)(AcceptAccessToken*, NSError*) = ^(AcceptAccessToken* tokenObj, NSError* error) {
        retToken = tokenObj;
        retErr = error;
        
        [self.accept discoverTerminalsForVendor:vendor.uuid completion:^(NSArray *discoveredTerminals, NSError *error)
         {
             if (error)
             {
                 [expectation fulfill];
                 NSLog(@"Error discovering terminals %@", error.description);
             }
             else if (discoveredTerminals.count > 0  )
             {
                 void (^completion)(AcceptConfigFilesStatus , NSError* ) = ^(AcceptConfigFilesStatus status, NSError* error)
                 {
                     updateStatus = status;
                     if (status == AcceptConfigFilesStatusSuccess)
                     {
                         NSLog(@"Terminal firmware updated sucessfully");
                     }
                     else if(status == AcceptConfigFilesStatusUnnecessary){
                         NSLog(@"Terminal firmware update not needed");
                     }
                     else{
                         NSLog(@"Terminal firmware update status:%ld",(long)status);
                     }
                     
                     [expectation fulfill];
                     
                 };
                 
                 void(^progress)(AcceptConfigFilesProgress) = ^(AcceptConfigFilesProgress progress){
                     NSLog(@"Terminal firmware update progress:%ld",(long)progress);
                 };
                 
                 [self.accept  updateTerminalFirmware:[discoveredTerminals firstObject] vendor:vendor token:tokenObj.accessToken  config:nil progress:progress completion:completion];
             }
             else{
                 updateStatus = AcceptConfigFilesStatusTerminalNotReady;
                 NSLog(@"No terminals found");
                 [expectation fulfill];
                 
             }
         }];
        
        
    };

    
    [self.accept requestAccessToken:testUsername password:testPassword config:nil completion:completion];
    
    [self waitForExpectationsWithTimeout:280 handler:nil];
    
    BOOL updateRunOK = updateStatus == AcceptConfigFilesStatusSuccess || updateStatus ==AcceptConfigFilesStatusUnnecessary;
    
    
    XCTAssertTrue(updateRunOK,
                  @"should return access token");
    
    
}

- (void)testSpirePayment {
    
    if (MANUAL_TESTS == NO) {
        NSLog(@"Test to be run only in manual mode - with device attached and terminal paired");
        XCTAssertTrue(YES,
                      @"run only in manual mode");
        return ;
    }
    //Check Vendors
    __weak XCTestExpectation *expectation = [self expectationWithDescription:@"Spire Payment"];
    __block AcceptAccessToken* retToken;
    __block NSError* retErr;
    __block AcceptConfigFilesStatus updateStatus = AcceptConfigFilesStatusTerminalNotReady;
    
    AcceptTerminalVendor *vendor = [AcceptTerminalVendor new];
    vendor.displayName = @"Spire";
    vendor.uuid = @"PosMateExtension";
    
    void (^completion)(AcceptAccessToken*, NSError*) = ^(AcceptAccessToken* tokenObj, NSError* error) {
        retToken = tokenObj;
        retErr = error;
        
        [self.accept discoverTerminalsForVendor:vendor.uuid completion:^(NSArray *discoveredTerminals, NSError *error)
         {
             if (error)
             {
                 [expectation fulfill];
                 NSLog(@"Error discovering terminals %@", error.description);
             }
             else if (discoveredTerminals.count > 0  )
             {
                 void (^completion)(AcceptTransaction*, NSError*) = ^(AcceptTransaction *transaction, NSError *error)
                 {
                     if (error || !transaction)
                     {
                         NSLog(@"Payment failure:%@",error);
                         
                     }
                     else
                     {
                         if ([transaction.state isEqualToString:@"approved"]|| [transaction.state isEqualToString:@"authorized"]) {
                          NSLog(@"Success");
                         
                         }
                         else{
                              NSLog(@"Payment failure:%@",transaction.technicalMessage);
                         }
                         
                     }
                 };
                 
                 void(^progress)(AcceptStateUpdate) = ^(AcceptStateUpdate update)
                 {
                     NSLog(@"Payment progress:%ld",(long)update);
                 };
                 
                 
                 void(^signature)(AcceptSignatureRequest * ) = ^(AcceptSignatureRequest *  signatureRequest)
                 {
                     NSLog(@">>> PaymentViewController - requestSignature");
                     //NOTE: Here is expected to open a view for manually inserting a signature. Demo app fakes the proccess sending a PNG file with it. It is also recommendable that the picture file does not excceed 4-6 kb in size
                     NSURL *imgPath = [[NSBundle mainBundle] URLForResource:@"signature_sample" withExtension:@"png"];
                     NSString*stringPath = [imgPath absoluteString];
                     NSData *data = [NSData dataWithContentsOfURL:[NSURL URLWithString:stringPath]];
                     UIImage *signatureImage = [[UIImage alloc] initWithData:data];
                     signatureRequest.signatureCallback(signatureImage, nil);
                 };
                 
                 void (^signatureVerification)(AcceptTransaction*, AcceptSignatureVerificationResultCallback,NSError*) = ^(AcceptTransaction *transaction,AcceptSignatureVerificationResultCallback signatureVerificationCallbackMerchantResponse, NSError *error)
                 {
                     
                     if (signatureVerificationCallbackMerchantResponse) {
                         //implement the confirmation for the signature Approval/Rejection and call signatureVerificationCallbackMerchantResponse with Approved or Rejected accordingly
                         signatureVerificationCallbackMerchantResponse(AcceptSignatureVerificationResultApproved);
                     }
                     else{
                         if (error || !transaction) {
                             
                             NSLog(@"Signature verification error:%@",error);
                         }
                         else{
                              NSLog(@"Signature approved - Payment Success");
                             //            [weakSelf paymentSuccess:transaction];
                         }
                     }
                     
                 };
                 
                 void(^appSelection)(AcceptAppSelectionRequest * ) = ^(AcceptAppSelectionRequest * appSelectionRequest)
                 {
                     appSelectionRequest.appSelectionCallback(0,nil); //select first app in the list
                     
                 };
                 
                 AcceptTerminal *terminal = [discoveredTerminals firstObject];
                 
                 AcceptPaymentConfig* paymentConfig = [[AcceptPaymentConfig alloc] init];
                 
                 
                 paymentConfig.vendorUUID = vendor.uuid;
                 paymentConfig.eaaSerialNumber = terminal.eaaSerialNumber;
                 paymentConfig.allowGratuity = NO; //Gratuity is an optional feature for the payment
                 paymentConfig.transactionType = AcceptTransactionTypePurchase;
                 //Initializing the basket
                 AcceptBasket *basket = [[AcceptBasket alloc] init];
                 basket.currencyAsISO4217Code = @"EUR";
                 basket.netTaxation = [NSNumber numberWithInt:1] ; //Set to 0 for tax inclusive
                                                                   //Note: Basket has the option for setting latitude and longitude, in case the need the location in the payment info
                                                                   //basket.lat, basket.lng
                 
                 //Adding the payment item to the basket
                 AcceptBasketItem *basketItem =
                 [self addBasketItem:1 //This is the number of items. We could have more than one with the same price
                              amount:[NSDecimalNumber decimalNumberWithString:@"1000"] //10 EUR
                                note:@"Here we can add some description of the payment"
                                 tax:0 //value indicating the tax % (note: 7% is indicated by 700; 7 would be 0.07%)
                          chargeType:@"NONE"/*there are 4 types of charge: NONE, NORMAL, TIP and SERVICE_CHARGE*/];
                 
                 [basket.items addObject:basketItem]; //Note that a basket could include many items on it repeating the precious lines for each payment item
                 paymentConfig.basket = basket;
                 
                 //We execute the payment
                 [self.accept startPay:paymentConfig completion:completion progress:progress signature:signature signatureVerification:signatureVerification appSelection:appSelection];
                 
                 
             }
             else{
                 updateStatus = AcceptConfigFilesStatusTerminalNotReady;
                 NSLog(@"No terminals found");
                 [expectation fulfill];
                 
             }
         }];
        
        
    };
    
    
    [self.accept requestAccessToken:testUsername  password:testPassword config:nil completion:completion];
    
    [self waitForExpectationsWithTimeout:180 handler:nil];
    
    BOOL updateRunOK = updateStatus == AcceptConfigFilesStatusSuccess || updateStatus ==AcceptConfigFilesStatusUnnecessary;
    
    
    
    XCTAssertTrue(updateRunOK,
                  @"should return access token");
    
    
}

-(void)testZip{
    
    //test zip
    NSDictionary *dict1 = @{@"test1":@"this1"};

    NSString *strDir  = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject];
    [dict1 writeToFile:[strDir stringByAppendingPathComponent:@"test-zip1.plist"] atomically:YES];

    NSDictionary *dict2 = @{@"test2":@"this2"};
    [dict2 writeToFile:[strDir stringByAppendingPathComponent:@"test-zip2.plist"] atomically:YES];

    NSArray *arrFiles = @[[strDir stringByAppendingPathComponent:@"test-zip1.plist"],[strDir stringByAppendingPathComponent:@"test-zip2.plist"]];


    [[NSFileManager defaultManager] createDirectoryAtPath:[strDir stringByAppendingPathComponent:@"testZip"] withIntermediateDirectories:YES attributes:nil error:nil];

    ZipArchive *zipArchive = [[ZipArchive alloc] init];
    
    if ([zipArchive CreateZipFile2:[strDir stringByAppendingPathComponent:@"test.zip"]]) {
        
        for (NSString *filePath in arrFiles) {

            if (![zipArchive addFileToZip:filePath newname:[filePath lastPathComponent] ]) {
                [zipArchive CloseZipFile2];
                XCTAssert(YES , @"Failed to add file to the archive");

                
            };
        }
        
    }
    else{
        XCTAssert(YES , @"Failed to create the archive");
        
    }
    
    if (![zipArchive CloseZipFile2]) {
        XCTAssert(YES , @"Failed to close the archive");
    }
    
    ZipArchive *zipArchive1 = [[ZipArchive alloc] init];
    if (![zipArchive1 UnzipOpenFile: [strDir stringByAppendingPathComponent:@"test.zip"]]){
        XCTAssert(YES , @"ZipArchive cannot open zipped file.");
    }
    if (![zipArchive1 UnzipFileTo:[strDir stringByAppendingPathComponent:@"testZip"] overWrite:YES]){
            XCTAssert(YES , @"ZipArchive cannot unzip zipped file.");

    };

    if(![zipArchive1 UnzipCloseFile]){
        XCTAssert(YES , @"ZipArchive failed to close the zip file.");
    }
    
    NSDictionary *dictUnzipped1 = [[NSDictionary alloc] initWithContentsOfFile:[[strDir stringByAppendingPathComponent:@"testZip"] stringByAppendingPathComponent:@"test-zip1.plist"]];

    NSDictionary *dictUnzipped2 = [[NSDictionary alloc] initWithContentsOfFile:[[strDir stringByAppendingPathComponent:@"testZip"] stringByAppendingPathComponent:@"test-zip2.plist"]];
    
    BOOL mismatchDict1 = YES;

    for (NSString *key in [dict1 allKeys]) {
        if (![[dictUnzipped1 valueForKey:key] isEqualToString:[dict1 valueForKey:key]]) {
            mismatchDict1 = YES;
            break;
        }
        else{
            mismatchDict1 = NO;
        }
    }

    BOOL mismatchDict2 = YES;

    for (NSString *key in [dict2 allKeys]) {
        if (![[dictUnzipped2 valueForKey:key] isEqualToString:[dict2 valueForKey:key]]) {
            mismatchDict2 = YES;
            break;
        }
        else{
            mismatchDict2 = NO;
        }
    }
    
    XCTAssert(!mismatchDict1 || !mismatchDict2 , @"Files are not identical after zip and unzip.");
    

}


@end

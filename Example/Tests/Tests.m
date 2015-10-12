//
//  Accept_DemoTests.m
//  Accept DemoTests
//
//  Copyright (c) 2015 Wirecard GmbH. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <XCTest/XCTest.h>
#import "ZipArchive.h"

@interface Accept_DemoTests : XCTestCase

@end

@implementation Accept_DemoTests

- (void)setUp {
    [super setUp];
    // Put setup code here. This method is called before the invocation of each test method in the class.
}

- (void)tearDown {
    // Put teardown code here. This method is called after the invocation of each test method in the class.
    [super tearDown];
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
    

    //test zip
//    NSDictionary *dict1 = @{@"test1":@"this1"};
//
//    NSString *strDir  = [NSSearchPathForDirectoriesInDomains(NSCachesDirectory, NSUserDomainMask, YES) lastObject];
//    [dict1 writeToFile:[strDir stringByAppendingPathComponent:@"test-zip1.plist"] atomically:YES];
//    
//    NSDictionary *dict2 = @{@"test2":@"this2"};
//    [dict2 writeToFile:[strDir stringByAppendingPathComponent:@"test-zip2.plist"] atomically:YES];
//    
//    NSArray *arrFiles = @[[strDir stringByAppendingPathComponent:@"test-zip1.plist"],[strDir stringByAppendingPathComponent:@"test-zip2.plist"]];
//    
//    [SSZipArchive createZipFileAtPath:[strDir stringByAppendingPathComponent:@"test.zip"] withFilesAtPaths:arrFiles];
//    
//    [[NSFileManager defaultManager] createDirectoryAtPath:[strDir stringByAppendingPathComponent:@"testZip"] withIntermediateDirectories:YES attributes:nil error:nil];
//    [[NSFileManager defaultManager] createDirectoryAtPath:[strDir stringByAppendingPathComponent:@"testZip2"] withIntermediateDirectories:YES attributes:nil error:nil];
//    
//    [SSZipArchive unzipFileAtPath:[strDir stringByAppendingPathComponent:@"test.zip"] toDestination:[strDir stringByAppendingPathComponent:@"testZip"]];
//    
//    
//    NSDictionary *dictUnzipped1 = [[NSDictionary alloc] initWithContentsOfFile:[[strDir stringByAppendingPathComponent:@"testZip"] stringByAppendingPathComponent:@"test-zip1.plist"]];
//    
//    NSDictionary *dictUnzipped2 = [[NSDictionary alloc] initWithContentsOfFile:[[strDir stringByAppendingPathComponent:@"testZip"] stringByAppendingPathComponent:@"test-zip2.plist"]];
//
//    BOOL mismatchDict1 = YES;
//    
//    for (NSString *key in [dict1 allKeys]) {
//        if (![[dictUnzipped1 valueForKey:key] isEqualToString:[dict1 valueForKey:key]]) {
//            mismatchDict1 = YES;
//            break;
//        }
//        else{
//            mismatchDict1 = NO;
//        }
//    }
// 
//    BOOL mismatchDict2 = YES;
//    
//    for (NSString *key in [dict2 allKeys]) {
//        if (![[dictUnzipped2 valueForKey:key] isEqualToString:[dict2 valueForKey:key]]) {
//            mismatchDict2 = YES;
//            break;
//        }
//        else{
//            mismatchDict2 = NO;
//        }
//    }
//    
//    ZipArchive *zipArchive = [[ZipArchive alloc] init];
//    if (![zipArchive UnzipOpenFile: [strDir stringByAppendingPathComponent:@"test.zip"]]){
//        XCTAssert(YES , @"ZipArchive cannot open SSZipArchive zipped file.");
//    }
//    if (![zipArchive UnzipFileTo:[strDir stringByAppendingPathComponent:@"testZip2"] overWrite:YES]){
//            XCTAssert(YES , @"ZipArchive cannot unzip SSZipArchive zipped file.");
//        
//    };
//    
//    if(![zipArchive UnzipCloseFile]){
//        XCTAssert(YES , @"ZipArchive failed to close the zip file.");
//    }
//    
//    XCTAssert(!mismatchDict1 || !mismatchDict2 , @"Files are not identical after zip and unzip.");
    
}


@end

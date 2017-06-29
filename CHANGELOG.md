# Change Log
All notable changes to acceptSDK will be documented in this file.

## [1.6.205] - 2017-06-29
### Added
- Payment Custom Data - Custom Fields and Sub Merchant

## [1.6.204] - 2017-06-16
### Fixed
- Cancel Payment - pay completion crash

## [1.6.203] - 2017-06-14
### Fixed
- Receipt Description amounts

## [1.6.202] - 2017-06-12
### Fixed
- Missing TID in the Contactless flow
- Terminal configuration update - fix for B/T communication

## [1.6.200] - 2017-05-11
### Fixed
- Proper handling of the terminals in the case more than one terminal of the same type is paired and being used
 
## [1.6.199] - 2017-04-18
### Added
- ATrust functionality for Austria

### Fixed
- Double completion in updateTerminalFirmware

## [1.6.198] - 2017-03-27
### Added
- SSL certificates for backends
- Request DEP report for Austria

### Fixed
- Error object populated in the case of terminated transaction
- Spire terminal reverts to Standby after payment flow completion


## [1.6.195] - 2016-12-16
### Added
- SSL certificates for backends
- AMEX support

### Fixed
- AirPrint printing
- BBPOS unexpected unplugging crash

## [1.6.194] - 2016-10-07
### Added
- New methods for terminal configuration and firmware updates

### Fixed
- Incomplete backend configuration details
- Keychain -34018 issue - missing entitlements Apple bug
- Loss of EAAccessory connection

## [1.6.193] - 2016-09-09
### Added
- Capture, Authorize card payment methods and Alipay examples

## [1.6.192] - 2016-09-02
### Changed
- Example app using Alipay and barcode scanning
- SSL certificate for the integration backend

## [1.6.190] - 2016-07-29
### Added
- Alipay and Cash payment sections in the Integration Guide

### Fixed
- Exclusive tax calculation
- Discount item calculation

## [1.6.189] - 2016-05-20
### Added
- SEPA transaction type
- Alternative payment methods - Alipay

## [1.6.184] - 2016-03-22
### Added
- Alipay support in backend API

### Changed
- Contactless support disabled by default

## [1.6.182] - 2016-02-23
### Added
- App transport security settings
- Contactless support for SPm2
- StarIO mPOP extension

## [1.6.170] - 2015-11-02
### Added
- iOS 9 support
- Spire SPm2 extension
- Transaction reversals by backend based on Application cryptogram

### Fixed
- Posmate signature verification flow

## [1.6.150] - 2015-08-05
### Added
- Image printing for Datecs DPP 250
- Cash payment

## [1.6.106] - 2015-04-29
### Added
- Payment flow logs for Posmate and BBPOS

## [1.6.104] -  2015-04-28 "RELEASE CANDIDATE"
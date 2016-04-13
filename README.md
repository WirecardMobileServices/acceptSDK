
# acceptSDK

<img src="https://raw.githubusercontent.com/mposSVK/acceptSDK/master/docs/logo.png" alt="acceptSDK" width=240 height=95>

[![CI Status](http://img.shields.io/travis/mposSVK/acceptSDK.svg?style=flat)](https://travis-ci.org/mposSVK/acceptSDK)
[![Version](https://img.shields.io/cocoapods/v/acceptSDK.svg?style=flat)](http://cocoapods.org/pods/acceptSDK)
[![License](https://img.shields.io/cocoapods/l/acceptSDK.svg?style=flat)](http://cocoapods.org/pods/acceptSDK)
[![Platform](https://img.shields.io/cocoapods/p/acceptSDK.svg?style=flat)](http://cocoapods.org/pods/acceptSDK)

## Overview
The library enables cashless payment processing with selected mPOS terminals (magStripe and Chip and PIN) via the fully-licensed Wirecard Bank, Wirecard Retail Services which allows acceptance of many different cards, including Visa, MasterCard and American Express.

Check out the applications using the **acceptSDK** and created as **re-branding** of **Wirecard Whitelabel solution** 

accept.|Pay Way|Lexware pay|Accept SGP|M1 pay|
-------|-------|-----------|-------|------|
[<img src="http://a3.mzstatic.com/us/r30/Purple3/v4/84/40/96/844096f6-04c3-1b74-81fc-ed6b82ab51bb/icon175x175.jpeg" alt="accept." style="border-radius:25px; !important"  width=100 height=100 class="roundedEdgesImage"> ](https://itunes.apple.com/us/app/accept-ger/id935572605?ls=1&mt=8 "accept.")|[<img src="http://a3.mzstatic.com/us/r30/Purple3/v4/44/76/9d/44769d4a-721a-d771-de52-4389163821c6/icon175x175.png" style="border-radius: 25px; !important" width=100 height=100 alt="Pay Way"  class="roundedEdgesImage">](https://itunes.apple.com/us/app/pay-way-by-payment-gateway-ltd/id982176916?ls=1&mt=8 "Pay Way")|[<img src="http://a3.mzstatic.com/eu/r30/Purple3/v4/d4/e5/6d/d4e56ddf-fcb1-367a-aaa3-7b5dd52235c8/icon175x175.png" style="border-radius: 25px; !important"  width=100 height=100 alt="Lexware Pay"  class="roundedEdgesImage">](https://itunes.apple.com/de/app/lexware-pay/id794986995?l=en&mt=8 "Lexware pay")|[<img  src="http://a3.mzstatic.com/us/r30/Purple1/v4/d8/57/ee/d857eebd-3f7f-a74a-30b2-a43febc78d89/icon175x175.png" style="border-radius: 25px; !important"  width=100 height=100 alt="Accept SGP"  class="roundedEdgesImage">](https://itunes.apple.com/us/app/accept-sgp/id953080653?ls=1&mt=8 "Accept SGP")|[<img src="http://a3.mzstatic.com/eu/r30/Purple7/v4/f3/f8/b0/f3f8b0a0-aee4-c61e-b468-6b660fb527c7/icon175x175.jpeg" style="border-radius: 25px; !important"  width=100 height=100 alt="M1 mPOS">](https://itunes.apple.com/de/app/m1-mpos/id1001499598?l=en&mt=8 "M1 mPOS")|

##Whitelabel solution
Wirecard Technologies is using the acceptSDK in their Whitelabel application which is fully integrated professional mPOS solution. The **Whitelabel** app is **VISA and Mastercard certified** and utilises the Wirecard infrastructure for card payment processing.

[<img src="https://raw.githubusercontent.com/mposSVK/acceptSDK/master/docs/SDK_arch.jpg" alt="Whitelabel architecture" width=274 height=515>](./docs/SDK_arch.jpg "Whitelabel Architecture")

*Overview of Whitelabel app functions and SDK architecture*

## Installation

There are two ways how to install the SDK.

1. Clone from GitHub and integrate the library as per the  [Integration Guide document](./docs/Integration Guide Accept SDK.pdf" "Integration Guide")
2. acceptSDK is available through [CocoaPods](http://cocoapods.org). To install
it, simply add the following line to your Podfile:

```
pod "acceptSDK"
```
It is possible to use acceptSDK with core functionality and one of supported terminal extension.
E.g. to use acceptSDK and Spire PosMate smart terminal please modify your podfile as follows:

```
pod "acceptSDK/Core"
pod "acceptSDK/Spire"
```


Read more about integrating the acceptSDK into your application in the attached documentation.

## Contact

Get in touch with [acceptSDK development team](mailto://mpos-svk@wirecard.com/ "acceptSDK") for acceptSDK support and mPOS Whitelabel solution

Get in touch with [Wirecard mPOS retail team](mailto://retail.mpos@wirecard.com/ "mpor Retails") for Wirecard payment processing services


## Documentation

All the necessary documents are available in the ./docs subfolder.

Refer to "Intergration Guide Accept SDK.pdf" for the details on how to use acceptSDK.

If using accepdSDK pod the all the required libraries are taken care of by the pod.

API reference documentation is available in ./docs/Reference Documentation subfolder

## Requirements

* Computer running OSX
* XCode > 6.0
* Device running iOS > 7.1
* One of Wirecard approved terminals and handheld printers
	* IDTech [Unimag Pro](http://www.idtechproducts.com/products/mobile-readers/126.html "Unimag Pro")
	* BBPOS [uEMV Swiper - Chipper](http://bbpos.com/en/solutions/hardware/ "Chipper")
	* Spire [PosMate](http://www.spirepayments.com/product/posmate/ "PosMate")
	* Spire [SPm2](http://www.spirepayments.com/product/spm2/ "SPm2")
	* Datecs printer [DPP-250](http://www.datecs.bg/en/products/DPP-250/2/175 "DPP-250")
	

## Authors

   Wirecard Technologies Slovakia,  mpos-svk@wirecard.com 
   
   radoslav.danko, radoslav.danko@wirecard.com
   
   francisco.fortes, francisco.fortes@wirecard.com
   
   damian.kolakowski, damian.kolakowski@partner.wirecard.com

## License

acceptSDK is available under the MIT license. See the LICENSE file for more info.

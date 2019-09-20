Pod::Spec.new do |s|

  s.name          = "acceptSDK"
  s.version       = "1.6.218"
  s.summary       = "Accept Payment Platform"
  s.homepage      = "http://www.wirecard.com/e-commerce/"
  s.license       = { :type => 'Commercial', :file => 'LICENSE' }
  s.authors       = {"Wirecard mPOS SDK" => "sdk.mpos@wirecard.com", "Radoslav Danko" => "radoslav.danko@wirecard.com","Francisco Fortes" => "francisco.fortes@wirecard.com", "Damian Kołakowski" => "damian.kolakowski@up-next.com"}
  s.platform      = :ios, '9.0'
  s.swift_version = '4.2'
  s.source        = { :git => "ssh://git@stash.up-next.com:7999/as/accept-sdk-pod.git", :tag => "#{s.version}" }
  
   ### Subspecs

    s.subspec 'Core' do |s|
        s.source_files = 'Accept/*.{h,m}' , 'Accept/Backend/**/*.{h,m}', 'Accept/Basket/**/*.{h,m}', 'Accept/Cards/**/*.{h,m}' , 'Accept/EMV/*.{h,m}', 'Accept/config/**/*', 'Accept/Vendors/*.{h,m}', 'Accept/Printers/*.{h,m}'
        s.preserve_paths      = ['Accept/Vendors/**/*.h', 'Accept/Vendors/**/*.a', 'Accept/Printers/**/*.a', 'Accept/Printers/**/*.h']
        s.resources = ['Accept/Cards/*.json', 'Accept/*.xml', 'Accept/hpp/*.xib', 'Accept/ElasticEngine/*.xib', 'Accept/ElasticEngine/*.xml', 'Accept/Cards/images/*.png']
        s.xcconfig     = { 'HEADER_SEARCH_PATHS' => '"$(SDKROOT)/usr/include/libxml2"' , 'GCC_PREPROCESSOR_DEFINITIONS' => 'ACCEPT_SDK_SOURCE_AVAILABLE=1' }
        s.frameworks    = 'Foundation', 'SystemConfiguration', 'MediaPlayer', 'AVFoundation', 'AudioToolbox', 'CoreAudio', 'ExternalAccessory'
        s.requires_arc  = true
        s.libraries = 'c++' ,'z.1'
		s.dependency 'ZipArchive', '~> 1.4'
	    s.dependency 'KissXML' 
    end
    
   s.subspec 'DUKPT' do |dukpt|
	 dukpt.source_files   = 'Accept/DUKPT/*.{h,m}'
     dukpt.dependency 'Accept/Core'
   end
       
   s.subspec 'BBPOS' do |bbpos|  
	 bbpos.source_files   = 'Accept/Vendors/BBPOS/*.{h,m}', 'Accept/Vendors/BBPOS/SDK/*.{h}'  
     bbpos.vendored_libraries  = 'Accept/Vendors/BBPOS/**/*.a'
   end
   
   s.subspec 'DATECSLIB' do |datecslib|  
     datecslib.source_files   =  'Accept/Vendors/DATECS/SDK/*.{h}'
     datecslib.vendored_libraries  = 'Accept/Vendors/DATECS/SDK/*.{a}'
     datecslib.dependency 'Accept/Core'
   end
   
   s.subspec 'MPOP' do |mpop|
      mpop.source_files   =  'Accept/Vendors/STARIO/*.{h,m}','Accept/Vendors/STARIO/mPOP frameworks/*.{h}', 'Accept/Vendors/STARIO/mPOP frameworks/other/*.{h}', 'Accept/Vendors/STARIO/mPOP frameworks/starmicronics/*.{h}'
      mpop.vendored_libraries  = 'Accept/Vendors/STARIO/mPOP frameworks/*.{a}'
      mpop.dependency 'Accept/Core'
    end

#    s.subspec 'DATECS' do |datecs|  
#      datecs.dependency 'Accept/DATECSLIB'
# 	 datecs.source_files   = 'Accept/Vendors/DATECS/*.{h,m}'
# #      datecs.vendored_libraries  = 'Accept/Vendors/DATECS/**/*.{a}'
#    end

#  s.subspec 'IDTECH' do |idtech|  
#	 idtech.source_files   = 'Accept/Vendors/IDTECH/*.{h,m}', 'Accept/Vendors/IDTECH/SDK/*.{h}'  
#     idtech.vendored_libraries  = 'Accept/Vendors/IDTECH/**/*.a'
#   end

   s.subspec 'SPIRE' do |spire|  
	 spire.source_files   = 'Accept/Vendors/SPIRE/*.{h,m}'  
     spire.vendored_libraries  = 'Accept/Vendors/SPIRE/**/*.a'
     spire.dependency 'Accept/Core'
   end

#   s.subspec 'VERIFONE' do |veri|  
#	 veri.source_files   = 'Accept/Vendors/VERIFONE/*.{h,m}', 'Accept/Vendors/VERIFONE/iJack/*.{h,m}', 'Accept/Vendors/VERIFONE/libs/*.{h}'  
#     veri.vendored_libraries  = 'Accept/Vendors/VERIFONE/libs/*.{a}'
#   end
  
   s.subspec 'PRTDATECS' do |prtdatecs|  
     prtdatecs.dependency 'Accept/DATECSLIB'
	 prtdatecs.source_files   =  'Accept/Printers/DATECS/*.{h,m}'
   end
  
end

Pod::Spec.new do |s|
  s.name             = "acceptSDK"
  s.version          = "1.6.167"
  s.summary          = "Accept Payment Platform SDK - credit card payments, Chip and PIN, magstripe"
  s.description      = <<-DESC
                       The library extends the point of sale to modern mobile environment. 
                       Major Credit and Debit Card payment processing (Master, Visa, American Express)
                       
                       Fully integrated with licensed Wirecard Payment infrastructure.
                       
                       Set of Wirecard approved terminals is supported (more to come):
                       * IDTech Unimag Pro
                       * BBPOS uEMVSwiper *Chipper
                       * Spire PosMate
                       * Spire SPm2
                       * Datecs DPP-250
                       DESC
  s.homepage         = "https://github.com/mposSVK/acceptSDK"
  s.license          = 'MIT'
  s.authors           = { "Radoslav Danko" => "radoslav.danko@wirecard.com","Francisco Fortes" => "francisco.fortes@wirecard.com","Damian Kołakowski" => "damian.kolakowski@up-next.com" }
  s.source           = { :git => "https://github.com/mposSVK/acceptSDK.git", :tag => s.version.to_s }
  s.platform     = :ios, '7.0'
  s.requires_arc = true
  s.xcconfig     = { 'HEADER_SEARCH_PATHS' => '$(SDKROOT)/usr/include/libxml2' }
  s.libraries = 'stdc++.6', 'z.1', 'xml2'
  s.frameworks    = 'Foundation', 'SystemConfiguration', 'MediaPlayer', 'AVFoundation', 'AudioToolbox', 'CoreAudio', 'ExternalAccessory'

  s.subspec 'Core' do |ss|
    ss.vendored_libraries  = 'Pod/Classes/lib/libPodsSDK.a'
    ss.source_files = 'Pod/Classes/include/*.{h}'
    ss.public_header_files = '**/*.{h}'    
    ss.resource = ['Pod/Assets/*.xml', 'Pod/Classes/lib/acceptResources.bundle']
    ss.dependency 'ZipArchive', '~> 1.4'
    ss.dependency 'KissXML', '~> 5.0'    
  end  
   
  s.subspec 'IDTech' do |ss|
    ss.vendored_libraries  = 'Pod/Classes/lib/libUnimagSDK.a'
    ss.dependency     'acceptSDK/Core'
  end  

  s.subspec 'BBPOS' do |ss|
    ss.vendored_libraries  = 'Pod/Classes/lib/libEmvSwipeBBPOSSDK.a'
    ss.dependency     'acceptSDK/Core'    
  end  

  s.subspec 'Spire' do |ss|
    ss.vendored_libraries  = 'Pod/Classes/lib/libPosmateSDK.a'
    ss.dependency     'acceptSDK/Core'    
  end  

  s.subspec 'Datecs' do |ss|
    ss.vendored_libraries  = 'Pod/Classes/lib/libDatecsPrinterSDK.a'
   ss.dependency     'acceptSDK/Core' 
  end  

end

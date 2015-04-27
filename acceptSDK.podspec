Pod::Spec.new do |s|
  s.name             = "acceptSDK"
  s.version          = "1.6.104"
  s.summary          = "Accept Payment Platform SDK"
  s.description      = <<-DESC
                       The library extends the point of sale to modern mobile environment. 
                       
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
  s.author           = { "radoslav.danko" => "radoslav.danko@wirecard.com","francisco.fortes" => "francisco.fortes@wirecard.com","Damian Kołakowski" => "damian.kolakowski@up-next.com" }
  s.source           = { :git => "https://github.com/mposSVK/acceptSDK.git", :tag => s.version.to_s }
  s.platform     = :ios, '7.0'
  s.requires_arc = true
  s.xcconfig     = { 'HEADER_SEARCH_PATHS' => '$(SDKROOT)/usr/include/libxml2' }
  s.libraries = 'stdc++.6', 'z.1', 'xml2'
  s.frameworks    = 'Foundation', 'SystemConfiguration', 'MediaPlayer', 'AVFoundation', 'AudioToolbox', 'CoreAudio', 'ExternalAccessory'
  s.source_files = 'Pod/Classes/include/*.{h}'
  s.public_header_files = '**/*.{h}'
  s.vendored_libraries  = 'Pod/Classes/lib/*.{a}'
  s.resource = ['Pod/Assets/*.xml']


end

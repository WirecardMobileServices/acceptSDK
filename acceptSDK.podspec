#
# Be sure to run `pod lib lint acceptSDK.podspec' to ensure this is a
# valid spec and remove all comments before submitting the spec.
#
# Any lines starting with a # are optional, but encouraged
#
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = "acceptSDK"
  s.version          = "1.0.0"
  s.summary          = "Accept Payment Platform SDK"
  s.description      = <<-DESC
                       An optional longer description of acceptSDK

                       * Markdown format.
                       * Don't worry about the indent, we strip it!
                       DESC
  s.homepage         = "https://github.com/mposSVK/acceptSDK"
  # s.screenshots     = "www.example.com/screenshots_1", "www.example.com/screenshots_2"
  s.license          = 'MIT'
  s.author           = { "radoslav.danko" => "radoslav.danko@wirecard.com","francisco.fortes" => "francisco.fortes@wirecard.com","Damian Kołakowski" => "damian.kolakowski@up-next.com" }
  s.source           = { :git => "https://github.com/mposSVK/acceptSDK.git", :tag => s.version.to_s }
  # s.social_media_url = 'https://twitter.com/<TWITTER_USERNAME>'

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

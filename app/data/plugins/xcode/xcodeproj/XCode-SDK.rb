#!/usr/bin/ruby
# -*- coding: UTF-8 -*-

require 'xcodeproj'

# ./xcodelib/*.rb
Dir[File.dirname(__FILE__) + '/xcodelib/*.rb'].each { |file| require file }

# open xcodeproj
project = Xcodeproj::Project.open("../../build_ios/XCode-SDK.xcodeproj")
# project = Xcodeproj::Workspace.open("../../iOS/XCode_Project.xcworkspace")

# get targets
xcproj = XCodeProj.new(project)
target_sdk = xcproj.get_target("XCode-SDK")

# add libMNN.a to XCode-SDK
xcode_bp = XCodeBuildPhases.new(project, target_sdk)

# add libMNN.a to Link Binary With Libraries
# lib_path = Dir::pwd + "/../../iOS/XCodeSDK/libs/libMNN.a"
# xcode_bp.add_lib_link_ref_to_target("libMNN.a", lib_path.to_s)
# add *.h to Copy Files
pbx_copy_files_fras = xcode_bp.find_copy_files_from_target("XCode-SDK", "include/XCodeSDK")
xcode_bp.add_copy_files_to_target(pbx_copy_files_fras, "iOS/XCodeSDK/XCode-SDK.h")
xcode_bp.add_copy_files_to_target(pbx_copy_files_fras, "iOS/XCodeSDK/SDKType.h")

pbx_copy_files_fras_sub = xcode_bp.find_copy_files_from_target("XCode-SDK-Sub", "include/XCodeSDK/sdk_wrapper")
xcode_bp.add_copy_files_to_target(pbx_copy_files_fras_sub, "iOS/XCodeSDK/sdk_wrapper/SDKWrapper.h")

# ZERO_CHECK && ALL_BUILD
xcode_cm = XCodeCMake.new(project)
xcode_cm.fix_build_setting()

# save xcodeproj 
project.save

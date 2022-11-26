#!/usr/bin/ruby
# -*- coding: UTF-8 -*-

require 'xcodeproj'

class XCodeCMake
    def initialize(project)
        @project = project
    end

    def fix_build_setting()
        xcproj = XCodeProj.new(@project)

        # ZERO_CHECK
        target_zc = xcproj.get_target("ZERO_CHECK")
        xcode_bs = XCodeBuildSettings.new(xcproj, target_zc)
        xcode_bs.set_config("ARCHS", "arm64")
        xcode_bs.set_config("SDKROOT", "iphoneos")

        # ALL_BUILD
        target_ab = xcproj.get_target("ALL_BUILD")
        xcode_bs.set_target(target_ab)
        xcode_bs.set_config("ARCHS", "arm64")
        xcode_bs.set_config("SDKROOT", "iphoneos")
    end
end
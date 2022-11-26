#!/usr/bin/ruby
# -*- coding: UTF-8 -*-

require 'xcodeproj'

class XCodeBuildSettings
    def initialize(project, target)
        @project = project
        set_target(target)
    end

    def set_target(target)
        @target = target
    end

    def set_config(name, params)
        @target.build_configurations.each do |config|
            config.build_settings[name] = [params]
        end
        # #设置索引 FRAMEWORK_SEARCH_PATHS
        # @target.build_configurations.each do |config|
        #     config.build_settings["LIBRARY_SEARCH_PATHS"] = [
        #         "$(inherited)",
        #         "$(PROJECT_DIR)/framework/**",
        #     ]
        # end

        # @target.build_configurations.each do |config|
        #     config.build_settings["ARCHS"] = [
        #         "$(inherited)",
        #         "$(PROJECT_DIR)/framework/**",
        #     ]
        # end
    end
    
end
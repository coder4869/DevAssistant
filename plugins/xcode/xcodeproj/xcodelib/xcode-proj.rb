#!/usr/bin/ruby
# -*- coding: UTF-8 -*-

require 'xcodeproj'

class XCodeProj
    def initialize(project)
        @project = project
    end

    def get_target(name) 
        # search by iterator, find dest <target>
        targetIndex = 0
        list = @project.targets
        list.each_with_index do |target, idx|
            if target.name == name
                targetIndex = idx
                puts target.name
            end
        end
        target = list[targetIndex]
        return target
    end

end
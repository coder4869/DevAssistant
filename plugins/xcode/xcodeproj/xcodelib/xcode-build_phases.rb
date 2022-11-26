#!/usr/bin/ruby
# -*- coding: UTF-8 -*-

require 'xcodeproj'

class XCodeBuildPhases
    def initialize(project, target)
        @project = project
        set_target(target)
    end

    def set_target(target)
        @target = target
    end

    # Dependencies

    # Headers

    # Compile Sources

    # Link Binary With Libraries
    def add_lib_link_ref_to_target(libName, libPath)
        ref_list = @target.frameworks_build_phases.files_references
        puts ref_list.to_s
        isLibExist = 0
        ref_list.each_with_index do |file, index|
            if file.name == libName
                puts file.path
                puts "#{libName} already exist in `Link Binary With Libraries` !"
                isLibExist = 1
                break
            end
        end

        if isLibExist == 0
            puts "add #{libName} to `Link Binary With Libraries` !"
            lib_ref = @project.frameworks_group.new_file(libPath)
            @target.frameworks_build_phases.add_file_reference(lib_ref)
        end
    end

    # Copy Bundle Resources

    # Copy Files
    def find_copy_files_from_target(groupName, dstPath)
        dstGroup = nil
        # search by iterator, find dest <groupName>
        for pbx_copy_files in @target.copy_files_build_phases.each
            if pbx_copy_files.name == groupName
                puts "Find copy_files Group #{pbx_copy_files.name} !"
                dstGroup = pbx_copy_files
                break
            end
        end

        if dstGroup == nil
            dstGroup = @target.new_copy_files_build_phase(groupName)
        end

        # set Destination for `Copy-Files` 
        # dstSubfolderSpec：10-Frameworks, 16-Products Directory
        dstGroup.dst_subfolder_spec = "16"
        # dstPath：Subpath
        dstGroup.dst_path = dstPath

        return dstGroup
    end

    def add_copy_files_to_target(copy_files_group, filePath)
        # check if file exist or not
        isFileExist = 0
        copy_files_group.files_references.each do | file |
            # puts file.real_path
            # puts file.path
            # puts file.name
            if file.path == filePath
                puts "#{file.path} already exist in `Copy Files` !"
                isFileExist = 1
                break
            end
        end
        
        if isFileExist == 0
            puts "add #{filePath} to `Copy Files` !"
            file_ref = @project.frameworks_group.new_file(filePath)
            copy_files_group.add_file_reference(file_ref)
        end

        # set all select `Code Sign On Copy`
        for file in copy_files_group.files
            file.settings = Hash.new
            file.settings["ATTRIBUTES"] = ["CodeSignOnCopy"]
        end
    end
    
end
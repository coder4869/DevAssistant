# MIT License
# 
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#!/bin/bash

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${script_dir}

VERSION=0.7.1
function download() {
    wget https://github.com/google/glog/archive/refs/tags/v${VERSION}.tar.gz -O glog-${VERSION}.tar.gz
    tar -zxvf glog-${VERSION}.tar.gz
}

function build_mac() {
    cd ${script_dir}/glog-${VERSION}
    BUILD_DIR=build_mac

    # build mac
    rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}
    cmake -S . -B ${BUILD_DIR} -G "Xcode" 
    xcodebuild -project ${BUILD_DIR}/glog.xcodeproj -scheme glog -destination 'generic/platform=macOS' -configuration Release archive -UseModernBuildSystem=NO

    # copy to output
    mkdir -p output/include && cp -r src/glog output/include/
    mkdir -p output/libs/mac && cp -r ${BUILD_DIR}/Release/* output/libs/mac/
}

function build_ios() {
    cd ${script_dir}/glog-${VERSION}
    BUILD_DIR=build_ios

    # build ios
    rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}
    # echo "set_target_properties( glog PROPERTIES XCODE_ATTRIBUTE_EXECUTABLE_SUFFIX \".a\")" >> CMakeLists.txt
    cmake -S . -B ${BUILD_DIR} -G "Xcode" \
        -DCMAKE_TOOLCHAIN_FILE=${script_dir}/../scripts/cmake/cmake-apple/ios.toolchain.cmake -DPLATFORM=OS64 \
        -DCMAKE_XCODE_ATTRIBUTE_SDKROOT="iphoneos"
        # -DCMAKE_XCODE_ATTRIBUTE_MACH_O_TYPE=staticlib -DCMAKE_XCODE_ATTRIBUTE_SDKROOT="iphoneos"
    # xcodebuild -list -project ${BUILD_DIR}/glog.xcodeproj
    xcodebuild -project ${BUILD_DIR}/glog.xcodeproj -scheme glog -destination 'generic/platform=iOS' -configuration Release archive -UseModernBuildSystem=NO

    # copy to output
    mkdir -p output/include && cp -r src/glog output/include/
    mkdir -p output/libs/ios && cp -r ${BUILD_DIR}/Release-iphoneos/* output/libs/ios/
}

# download
# build_mac
build_ios

# cd ${script_dir}/glog-${VERSION}
# BUILD_DIR=build_ios
# xcodebuild -project ${BUILD_DIR}/glog.xcodeproj -scheme glog -destination 'generic/platform=iOS' -configuration Release archive -UseModernBuildSystem=NO

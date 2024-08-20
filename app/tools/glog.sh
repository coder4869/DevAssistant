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

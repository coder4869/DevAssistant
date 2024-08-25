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
# https://github.com/gabime/spdlog

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${script_dir}

VERSION=1.14.1
function download() {
    wget https://github.com/gabime/spdlog/archive/refs/tags/v${VERSION}.tar.gz -O spdlog-${VERSION}.tar.gz
    tar -zxvf spdlog-${VERSION}.tar.gz
}

function build_mac() {
    cd ${script_dir}/spdlog-${VERSION}
    BUILD_DIR=build_mac

    # build mac
    rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}
    # echo "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++11 -O1\")"  >> ../CMakeLists.txt
    cmake -S . -B ${BUILD_DIR} -G "Xcode" 
    xcodebuild -project ${BUILD_DIR}/spdlog.xcodeproj -scheme spdlog -destination 'generic/platform=macOS' -configuration Release archive -UseModernBuildSystem=NO

    # copy to output
    mkdir -p output/include && cp -r include/ output/include/
    mkdir -p output/libs/mac && cp -r ${BUILD_DIR}/Release/* output/libs/mac/
}

function build_ios() {
    cd ${script_dir}/spdlog-${VERSION}
    BUILD_DIR=build_ios

    # build ios
    rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}
    # echo "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++11 -O1\")"  >> ../CMakeLists.txt
    cmake -S . -B ${BUILD_DIR} -G "Xcode" \
        -DCMAKE_TOOLCHAIN_FILE=${script_dir}/../scripts/cmake/cmake-apple/ios.toolchain.cmake -DPLATFORM=OS64 \
        -DCMAKE_XCODE_ATTRIBUTE_SDKROOT="iphoneos"
    # xcodebuild -list -project ${BUILD_DIR}/spdlog.xcodeproj
    xcodebuild -project ${BUILD_DIR}/spdlog.xcodeproj -scheme spdlog -destination 'generic/platform=iOS' -configuration Release archive -UseModernBuildSystem=NO

    # copy to output
    mkdir -p output/include && cp -r include/ output/include/
    mkdir -p output/libs/ios && cp -r ${BUILD_DIR}/Release-iphoneos/* output/libs/ios/
}

build_android() {
    NDK_PATH=$HOME/Desktop/workspace/android_sdk/ndk/25.1.8937393
    export TOOLCHAIN_PATH=$NDK_PATH/toolchains/llvm/prebuilt/darwin-x86_64 
 
    cd ${script_dir}/spdlog-${VERSION}
    BUILD_DIR=build_android

    # build ios
    rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR} && cd ${BUILD_DIR}
    echo "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++11 -O1\")"  >> ../CMakeLists.txt
    cmake -S .. -B . \
        -DCMAKE_TOOLCHAIN_FILE=$NDK_PATH/build/cmake/android.toolchain.cmake \
        -DANDROID_ABI="arm64-v8a" \
        -DANDROID_NATIVE_API_LEVEL=21 \
        -DANDROID_TOOLCHAIN="clang" \
        -DANDROID_STL="c++_shared"
    make

    cd -
    # copy to output
    mkdir -p output/include && cp -r include/ output/include/
    mkdir -p output/libs/android/arm64-v8a && cp -r ${BUILD_DIR}/libspdlog.a output/libs/android/arm64-v8a/
}

# download
# build_mac
# build_ios
build_android

tree ${script_dir}/spdlog-${VERSION}/output
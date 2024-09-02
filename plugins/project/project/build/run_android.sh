#!/bin/bash
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

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${script_dir}

# set var
PROJ_NAME=_PROJ_NAME_

ROOT_DIR=${script_dir}/../..
BUILD_DIR=${ROOT_DIR}/build_android
BIN_DIR=${ROOT_DIR}/bin64
ANDROID_SDK_HOME=$HOME/Desktop/workspace/android_sdk
ANDROID_NDK_HOME=$ANDROID_SDK_HOME/ndk/26.1.10909125
ANDROID_CMAKE_BIN=$ANDROID_SDK_HOME/cmake/3.22.1/bin

function do_mkdir() {
    if [[ -d ${BUILD_DIR} ]]; then
        rm -rf ${BUILD_DIR}
    fi
    mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}

    if [[ -d ${BIN_DIR} ]]; then
        rm -rf ${BIN_DIR}
    fi
}

function do_gen {
    ANDROID_ABI=arm64-v8a
    ANDROID_API=21

    $ANDROID_CMAKE_BIN/cmake -Wno-dev ${ROOT_DIR} -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
        -DEXECUTABLE_OUTPUT_PATH=$BIN_DIR \
        -DWITH_QT=OFF -DWITH_PY=OFF \
        -DPROJECT_NAME=${PROJ_NAME} -DANDROID=ON -H$ROOT_DIR -B$BUILD_DIR \
        -DANDROID_ABI=$ANDROID_ABI -DANDROID_NDK=$ANDROID_NDK_HOME \
        -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
        -DANDROID_NATIVE_API_LEVEL=$ANDROID_API -DANDROID_TOOLCHAIN=clang -DCMAKE_GENERATOR="Ninja" \
        -DCMAKE_MAKE_PROGRAM=$ANDROID_CMAKE_BIN/ninja

    $ANDROID_CMAKE_BIN/ninja

    mkdir $BUILD_DIR/${ANDROID_ABI} && cp -rf $BUILD_DIR/*.so $BUILD_DIR/${ANDROID_ABI}/
}

function walk_dir() {
    rm -rf $1/.DS_Store
    rm -rf $1/__pycache__
    for child in `ls $1`
    do
        if [ -d $1"/"$child ]; then
            walk_dir $1"/"$child
        fi
    done
}

function clean_plugins() {
    PLIGUN_DIR=${ROOT_DIR}/../plugins
    if [[ -d $PLIGUN_DIR ]]; then
        walk_dir $PLIGUN_DIR
    fi
}


if [[ `uname` == "Darwin" ]]; then
    do_mkdir
    clean_plugins
    do_gen
fi


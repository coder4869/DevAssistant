#!/bin/bash
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

# 1-MacOS:
#   sh /opt/shared_dir/DevAssistant/app/run_android.sh
# 2-Linux:
# Setup-env: 
#   bash /opt/shared_dir/DevAssistant/tools/env-apt.sh
# Run way1:
#   sed -i 's/\r//' /opt/shared_dir/DevAssistant/app/run_android.sh && bash /opt/shared_dir/DevAssistant/app/run_android.sh
# Run way2:
#   sudo apt-get install -y dos2unix && dos2unix /opt/shared_dir/DevAssistant/app/run_android.sh && bash /opt/shared_dir/DevAssistant/app/run_android.sh

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd $script_dir

# set var
PROJ_NAME=DevAssistant

ROOT_DIR=$script_dir
BUILD_DIR=$ROOT_DIR/build_android
BIN_DIR=$ROOT_DIR/bin64
ANDROID_SDK_HOME=$HOME/Desktop/workspace/android_sdk # Darwin(MacOS)
if [[ `uname` == "Linux" ]]; then
    ANDROID_SDK_HOME=/usr/lib/android-sdk
fi
ANDROID_NDK_HOME=$ANDROID_SDK_HOME/ndk/26.1.10909125
ANDROID_CMAKE_BIN=$ANDROID_SDK_HOME/cmake/3.22.1/bin # Darwin(MacOS)
ANDROID_ABI=arm64-v8a
ANDROID_API=21

function do_mkdir() {
    if [[ -d $BUILD_DIR ]]; then
        rm -rf $BUILD_DIR
    fi
    mkdir -p $BUILD_DIR && cd $BUILD_DIR

    if [[ -d $BIN_DIR ]]; then
        rm -rf $BIN_DIR
    fi
}

function do_ninja_build {
if [[ `uname` == "Darwin" ]]; then # macOS
    $ANDROID_CMAKE_BIN/cmake -Wno-dev $ROOT_DIR -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
        -DEXECUTABLE_OUTPUT_PATH=$BIN_DIR \
        -DWITH_QT=OFF -DWITH_PY=OFF \
        -DPROJECT_NAME=$PROJ_NAME -DANDROID=ON -H$ROOT_DIR -B$BUILD_DIR \
        -DANDROID_ABI=$ANDROID_ABI -DANDROID_NDK=$ANDROID_NDK_HOME \
        -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
        -DANDROID_NATIVE_API_LEVEL=$ANDROID_API -DANDROID_TOOLCHAIN=clang -DCMAKE_GENERATOR="Ninja" \
        -DCMAKE_MAKE_PROGRAM=$ANDROID_CMAKE_BIN/ninja

    $ANDROID_CMAKE_BIN/ninja
    $ANDROID_CMAKE_BIN/ninja install
else # Linux
    cmake -Wno-dev $ROOT_DIR -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
        -DEXECUTABLE_OUTPUT_PATH=$BIN_DIR \
        -DWITH_QT=OFF -DWITH_PY=OFF \
        -DPROJECT_NAME=$PROJ_NAME -DANDROID=ON -H$ROOT_DIR -B$BUILD_DIR \
        -DANDROID_ABI=$ANDROID_ABI -DANDROID_NDK=$ANDROID_NDK_HOME \
        -DCMAKE_TOOLCHAIN_FILE=$ANDROID_NDK_HOME/build/cmake/android.toolchain.cmake \
        -DANDROID_NATIVE_API_LEVEL=$ANDROID_API -DANDROID_TOOLCHAIN=clang -G "Ninja"
    
    ninja
    ninja install
fi
    mkdir $BUILD_DIR/$ANDROID_ABI && cp -rf $BUILD_DIR/*.so $BUILD_DIR/$ANDROID_ABI/
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
    PLIGUN_DIR=$ROOT_DIR/../plugins
    if [[ -d $PLIGUN_DIR ]]; then
        walk_dir $PLIGUN_DIR
    fi
}


do_mkdir
clean_plugins
do_ninja_build
                                                                                               
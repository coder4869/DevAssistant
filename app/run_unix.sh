#!/bin/bash
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd ${script_dir}

# set var
PROJ_NAME=DevAssistant
QT_INSTALL_DIR="$HOME/Qt5.14.2/5.14.2/clang_64/"
PY_INSTALL_DIR="/Applications/Xcode.app/Contents/Developer/Library"

ROOT_DIR=${script_dir}
BUILD_DIR=${ROOT_DIR}/build_unix
BIN_DIR=${ROOT_DIR}/bin64

function do_mkdir() {
    if [[ -d ${BUILD_DIR} ]]; then
        rm -rf ${BUILD_DIR}
    fi
    mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}

    if [[ -d ${BIN_DIR} ]]; then
        rm -rf ${BIN_DIR}
    fi
}

function do_build {
if [[ `uname` == "Darwin" ]]; then  # MacOS
    cmake -Wno-dev ${ROOT_DIR} -GXcode -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
        -DEXECUTABLE_OUTPUT_PATH=$BIN_DIR \
        -DQT_INSTALL_DIR=${QT_INSTALL_DIR} \
        -DPY_INSTALL_DIR=${PY_INSTALL_DIR} \
        -DPROJECT_NAME=${PROJ_NAME} -DOSX=ON -H$ROOT_DIR -B$BUILD_DIR

    if [[ "$1" == "build" ]]; then
        # xcodebuild -project ${BUILD_DIR}/${PROJ_NAME}.xcodeproj -scheme install -configuration Release build
        # xcodebuild -project ${BUILD_DIR}/${PROJ_NAME}.xcodeproj -scheme install -destination 'generic/platform=macOS' -configuration Release archive -UseModernBuildSystem=NO
        xcodebuild -project ${BUILD_DIR}/${PROJ_NAME}.xcodeproj -scheme install -destination 'generic/platform=macOS' -configuration Release build -UseModernBuildSystem=NO
    else
        open ${BUILD_DIR}/${PROJ_NAME}.xcodeproj
    fi

else # Linux
    LINUX_OS=""
    if [[ `uname` == "Linux" ]]; then
        if [[ -f "/etc/redhat-release" ]]; then # Redhat / CentOS
            LINUX_OS="CentOS"
        elif [[ -f "/etc/lsb-release" ]]; then # Ubuntu / Debian
            LINUX_OS="Ubuntu"
        fi
    fi
    cmake -Wno-dev ${ROOT_DIR} -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
        -DEXECUTABLE_OUTPUT_PATH=$BIN_DIR \
        -DQT_INSTALL_DIR=${QT_INSTALL_DIR} \
        -DPY_INSTALL_DIR=${PY_INSTALL_DIR} \
        -DLINUX_OS=${LINUX_OS} \
        -DWITH_QT=ON \
        -DWITH_PY=OFF \
        -DPROJECT_NAME=${PROJ_NAME} -DLINUX=ON -H$ROOT_DIR -B$BUILD_DIR
    make
    make install
fi
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

do_mkdir
clean_plugins
do_build $1
                                                                               
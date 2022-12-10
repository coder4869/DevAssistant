#!/bin/bash
script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${script_dir}
# set var
APP_NAME=DevAssistant
QT_DIR="$HOME/Qt5.14.2/"
QT_INSTALL_DIR="$QT_DIR/5.14.2/clang_64/"

ROOT_DIR=${script_dir}/../..
BUILD_DIR=${ROOT_DIR}/build_unix

function do_mkdir() {
    if [[ -d ${BUILD_DIR} ]]; then
        rm -rf ${BUILD_DIR}
    fi
    mkdir -p ${BUILD_DIR} && cd ${BUILD_DIR}
}

function do_gen {
    # Unix Makefiles, Xcode
    generator=-G"Unix Makefiles"
    platform=LINUX
    if [[ `uname` == "Darwin" ]]; then
        generator="-GXcode"
        platform="OSX"
    fi

    cmake -Wno-dev ${ROOT_DIR} ${generator} -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$BUILD_DIR -DQT_INSTALL_DIR=${QT_INSTALL_DIR} \
        -DPROJECT_NAME=${APP_NAME} -D${platform}=ON -H$ROOT_DIR -B$BUILD_DIR
}

function do_open() {
    if [[ `uname` == "Darwin" ]]; then
        open ${BUILD_DIR}/${APP_NAME}.xcodeproj
    else
        make
        make install
    fi
}


do_mkdir
do_gen
do_open

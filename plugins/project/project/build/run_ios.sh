#!/bin/bash
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

cd ${script_dir}

# set var
PROJ_NAME=_PROJ_NAME_

ROOT_DIR=${script_dir}
BUILD_DIR=${ROOT_DIR}/build_ios
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

function do_gen {
    cmake -Wno-dev ${ROOT_DIR} -GXcode -DCMAKE_BUILD_TYPE=Release \
        -DCMAKE_INSTALL_PREFIX=$BUILD_DIR \
        -DEXECUTABLE_OUTPUT_PATH=$BIN_DIR \
        -DWITH_QT=OFF \
        -DWITH_PY=OFF \
        -DPROJECT_NAME=${PROJ_NAME} -DIOS=ON -H$ROOT_DIR -B$BUILD_DIR
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

function do_open() {
    open ${BUILD_DIR}/${PROJ_NAME}.xcodeproj
}

function do_build() {
    # xcodebuild -project ${BUILD_DIR}/${PROJ_NAME}.xcodeproj -scheme install -configuration Release build
    # xcodebuild -project ${BUILD_DIR}/${PROJ_NAME}.xcodeproj -scheme install -destination 'generic/platform=iOS' -configuration Release archive -UseModernBuildSystem=NO
    xcodebuild -project ${BUILD_DIR}/${PROJ_NAME}.xcodeproj -scheme install -destination 'generic/platform=iOS' -configuration Release build -UseModernBuildSystem=NO
}

if [[ `uname` == "Darwin" ]]; then
    do_mkdir
    clean_plugins
    do_gen
    if [[ "$1" == "build" ]]; then
        do_build
    else
        do_open
    fi
fi


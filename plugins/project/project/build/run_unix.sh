#!/bin/bash
# MIT License

# Copyright (c) 2021~2022 [coder4869](https://github.com/coder4869)

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

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
APP_NAME=PROJ_NAME
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

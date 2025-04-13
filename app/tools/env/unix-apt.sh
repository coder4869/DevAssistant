#!/bin/bash
# Support OS: ubuntu/OpenKylin2.0
# start docker:
# Windows: docker run -it -d --shm-size=2g --network=host -v D:\Research:/opt/shared_dir ubuntu2204:v1.0 /bin/bash
# Linux: docker run -it -d --shm-size=2g --network=host -v $HOME/dockers/shared_dir:/opt/shared_dir ubuntu2204-dev-v1.0 --privileged ubuntu2204:v1.0 /bin/bash
# docker exec -it a3822da6accba9625129bc63c9fe0001367a7282a7eda0d50783ab90e75c7513 /bin/bash
# 
# bash /opt/shared_dir/DevAssistant/tools/env-apt.sh

# ls -al /bin/sh && dpkg-reconfigure dash => no
# sh /opt/shared_dir/DevAssistant/tools/env-apt.sh

# echo color: https://www.cnblogs.com/unclemac/p/12783387.html

# vmware load shared dir: 
# temp: sudo mkdir /mnt/hgfs && sudo mount -t fuse.vmhgfs-fuse .host:/ /mnt/hgfs -o allow_other
# forever: vim /etc/fstab 
# add info: .host:/ /mnt/hgfs fuse.vmhgfs-fuse allow_other, defaults 0 0

OS=`uname`
ANDROID_SDK_HOME="/usr/lib/android-sdk"
ANDROID_NDK_HOME="$ANDROID_SDK_HOME/ndk"

# check user is root or not
SUDO_CMD=sudo
if [[ `whoami` == "root" ]]; then
    SUDO_CMD=
fi

# setup functions
function setup_source() {
    # [ubuntu清华源](https://mirrors.tuna.tsinghua.edu.cn/help/ubuntu/) 替换指令 for 16.04
    ${SUDO_CMD} sed -i "s@http://.*archive.ubuntu.com@http://mirrors.tuna.tsinghua.edu.cn@g" /etc/apt/sources.list
    ${SUDO_CMD} sed -i "s@http://.*security.ubuntu.com@http://mirrors.tuna.tsinghua.edu.cn@g" /etc/apt/sources.list
    ${SUDO_CMD} apt-get update
    echo -e "\e[42m updated /etc/apt/sources.list"
    cat /etc/apt/sources.list
    echo -e "\e[0m"

}

function setup_cert() {
    # [Certificate verification failed: The certificate is NOT trusted.](https://blog.csdn.net/qq_41554005/article/details/124140839)
    ${SUDO_CMD} apt-get install --reinstall ca-certificates
    ${SUDO_CMD} sed -i "s@http://mirrors.tuna.tsinghua.edu.cn@https://mirrors.tuna.tsinghua.edu.cn@g" /etc/apt/sources.list
    ${SUDO_CMD} apt-get update
    ${SUDO_CMD} apt-get install -y git vim net-tools
}

function setup_soft() {
    ${SUDO_CMD} apt-get install -y tree wget unzip cmake ninja-build dos2unix build-essential
    # Qt
    ${SUDO_CMD} apt-get install -y qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools qtdeclarative5-dev
    ${SUDO_CMD} apt-get install -y libqt5charts5* libqt5multimedia5* libqt5quickcontrols2-5 libqt5opengl5* 

    dpkg -l | grep qt5charts
    dpkg -l | grep qt5multimedia
}

function setup_pip() {
    ${SUDO_CMD} apt-get install -y pip
    pip install numpy pandas torch dgl
}

function java_env() {
    ${SUDO_CMD} apt search openjdk-17
    ${SUDO_CMD} apt-get install -y openjdk-17-jdk
    # ${SUDO_CMD} apt-get install python-software-properties
    # ${SUDO_CMD} add-apt-repository ppa:webupd8team/java
    # ${SUDO_CMD} apt-get update
}

function android_sdk() {
    # mkdir -p $ANDROID_SDK_HOME
    # android-sdk
    echo -e "\e[42m $OS: install android-sdk \e[0m"
    ${SUDO_CMD} apt search android-sdk 
    ${SUDO_CMD} apt-get install -y android-sdk
    whereis adb
    ls $ANDROID_SDK_HOME

    # adb
    echo -e "\e[42m $OS: install android-tools-adb \e[0m"
    ${SUDO_CMD} apt search adb
    ${SUDO_CMD} apt-get install -y adb
    whereis adb

    # fastboot
    echo -e "\e[42m $OS: install android-tools-fastboot \e[0m"
    ${SUDO_CMD} apt search fastboot
    ${SUDO_CMD} apt-get install -y fastboot
    whereis fastboot
}

# https://developer.android.google.cn/ndk/downloads/revision_history?hl=zh-cn
function android_ndk() {
    mkdir -p $ANDROID_NDK_HOME
    echo "$OS: install android ndk to $ANDROID_NDK_HOME"
    wget -c https://dl.google.com/android/repository/android-ndk-r26b-linux.zip
    ${SUDO_CMD} unzip -d $ANDROID_NDK_HOME android-ndk-r26b-linux.zip
    ${SUDO_CMD} mv $ANDROID_NDK_HOME/android-ndk-r26b $ANDROID_NDK_HOME/26.1.10909125
    # ${SUDO_CMD} tar -C $ANDROID_NDK_HOME -xvf android-ndk64-r10b-linux-x86_64.tar.bz2
    echo -e """\e[42m
    ${SUDO_CMD} gedit ~/.bashrc
    export ANDROID_SDK="$ANDROID_SDK_HOME"
    export ANDROID_NDK="$ANDROID_NDK_HOME/26.1.10909125"
    export PATH=$ANDROID_SDK_HOME:$ANDROID_NDK_HOME/26.1.10909125:$PATH
    source ~/.bashrc
    ndk-build
    \e[0m"""
}

setup_source
setup_cert
setup_soft
# setup_pip
java_env
android_sdk
android_ndk

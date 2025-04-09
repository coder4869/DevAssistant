#!/bin/bash
#~/rpmbuild/
#   ├── SOURCES/       # 存放源代码和配置文件
#   │   ├── bin64
#   │   ├── conf
#   │   ├── logs
#   │   └── data
#   ├── SPECS/         # 存放 SPEC 文件
#   │   └── app.spec
#   ├── RPMS/          # xxx.rpm installers
#   └── SRPMS/         # 生成的源码 RPM 包存放目录

script_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"

PROJ_NAME=_PROJ_NAME_

# clean caches
cd ~/rpmbuild 
rm -rf SOURCES/*
rm -rf SPECS/*
rm -rf RPMS/*
rm -rf SRPMS/*

cp -r ${script_dir}/build_unix/lib/*.so ${script_dir}/bin64/
cp -r ${script_dir}/bin64 SOURCES/ 
cp -r ${script_dir}/conf  SOURCES/ 
cp -r ${script_dir}/data  SOURCES/ 
cp -r ${script_dir}/scripts/pkg-rpm/app-desktop SOURCES/$PROJ_NAME.desktop
cp -r ${script_dir}/scripts/pkg-rpm/app_loader  SOURCES/${PROJ_NAME}_loader
cp -r ${script_dir}/scripts/pkg-rpm/app-action.xml SOURCES/$PROJ_NAME-action.xml
ls SOURCES

cp -r ${script_dir}/scripts/pkg-rpm/SPECS/app.spec SPECS/$PROJ_NAME.spec

rpmbuild -ba SPECS/$PROJ_NAME.spec

# install
cp ~/rpmbuild/RPMS/aarch64/$PROJ_NAME-*.rpm ${script_dir}/
echo "install"
echo "sudo rpm -ivh ~/rpmbuild/RPMS/aarch64/$PROJ_NAME-xxx.rpm"
#sudo rpm -ivh ~/rpmbuild/RPMS/aarch64/$PROJ_NAME-xxx.rpm
ls ${script_dir} | grep $PROJ_NAME

# uninstall
echo "uninstall"
echo "sudo rpm -e $PROJ_NAME"

# sudo rpm -e $PROJ_NAME


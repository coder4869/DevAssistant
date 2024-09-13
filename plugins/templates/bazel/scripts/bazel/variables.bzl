# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

# Compile options
COPTS = ["-std=c++17 -v"]

CC_VISIBILITY = [ "//visibility:public" ]
CC_LINK_OPTS = ["-lstdc++"]

XC_BUILD_OS     = "ios" # ios / macos
XC_COPTS = [
    "-arch", "armv7", "arm64", "i386", "x86_64"
]
PROJECT_VERSION = "1.0.0"
OC_LINK_OPTS    = [ "-ObjC" ] # , "-fembed-bitcode" default_platforms

# IOS Data
IOS_UI_LAUNCH   = "Resources/ios/Main.storyboard"
IOS_INFO_PLIST  = [ "Resources/Info.plist" ]
# IOS Config
IOS_FAMILY      = [ "iphone", "ipad" ]
IOS_MIN_VERSION = "11.0"
# IOS_CPU_ARCH  = ["armv7", "arm64", "i386", "x86_64"]
IOS_CPU_ARCH    = [ "arm64", "x86_64" ]

# Mac Config
MAC_MIN_VERSION = "10.13"

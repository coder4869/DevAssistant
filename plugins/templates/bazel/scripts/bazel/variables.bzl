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

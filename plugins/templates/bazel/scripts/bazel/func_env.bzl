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

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

############################# apple env #############################
### [Apple](https://bazel.google.cn/versions/6.0.0/start/ios-app)
# https://github.com/bazelbuild/rules_apple/blob/master/doc/frameworks.md
# https://github.com/bazelbuild/rules_apple/blob/master/doc/tutorials/ios-app.md
# https://github.com/bazel-ios/rules_ios

def apple_env():
    git_repository(
        name = "build_bazel_rules_apple",
        remote = "https://github.com/bazelbuild/rules_apple.git",
        tag = "3.5.1",
    )
    # load("@build_bazel_rules_apple//apple:repositories.bzl", "apple_rules_dependencies")
    # apple_rules_dependencies()

    git_repository(
        name = "build_bazel_apple_support",
        remote = "https://github.com/bazelbuild/apple_support.git",
        tag = "1.15.1",
    )
    # load("@build_bazel_apple_support//lib:repositories.bzl", "apple_support_dependencies")
    # apple_support_dependencies()

    git_repository(
        name = "build_bazel_rules_swift",
        remote = "https://github.com/bazelbuild/rules_swift.git",
        tag = "1.18.0",
    )
    # load("@build_bazel_rules_swift//swift:repositories.bzl", "swift_rules_dependencies")
    # swift_rules_dependencies()
    # load("@build_bazel_rules_swift//swift:extras.bzl", "swift_rules_extra_dependencies")
    # swift_rules_extra_dependencies()

    git_repository(
        name = "build_bazel_rules_ios",
        remote = "https://github.com/bazel-ios/rules_ios.git",
        tag = "4.7.1",
    )
    # load("@build_bazel_rules_ios//rules:repositories.bzl", "rules_ios_dependencies")
    # rules_ios_dependencies()

    # https://github.com/bazelbuild/rules_apple/blob/master/doc/tutorials/ios-app.md
    git_repository(
        name = "rules_xcodeproj",
        remote = "https://github.com/MobileNativeFoundation/rules_xcodeproj.git",
        tag = "2.5.1",
    )
    # load("@rules_xcodeproj//xcodeproj:repositories.bzl", "xcodeproj_rules_dependencies")    
    # xcodeproj_rules_dependencies()
    # load("@rules_xcodeproj//xcodeproj:defs.bzl", "top_level_target", "xcodeproj")
    # load("@bazel_features//:deps.bzl", "bazel_features_deps")
    # bazel_features_deps()

    # git_repository(
    #     name = "xchammer",
    #     remote = "https://github.com/bazel-xcode/xchammer.git",
    #     tag = "v3.4.3.3",
    # )
    # load("@xchammer//:BazelExtensions/xcodeproject.bzl", "xcode_project")
    # xcode_project(
    #     name = "MyProject",
    #     targets = [ "//ios-app:ios-app" ],
    # )


############################# android env #############################
ANDROID_HOME="$HOME/Desktop/workspace/android_sdk"
ANDROID_NDK_HOME="$HOME/Desktop/workspace/android_sdk/ndk/26.1.10909125"

def android_env():
    git_repository(
        name = "rules_android",
        remote = "https://github.com/bazelbuild/rules_android.git",
        tag = "v0.1.1",
    )
    # load("@rules_android//rules:rules.bzl", "android_binary", "android_library")

    native.android_sdk_repository(
        name = "androidsdk",
        # path = ANDROID_HOME, # export ANDROID_HOME=$HOME/Desktop/workspace/android_sdk
        api_level = 34,
        build_tools_version = "30.0.3"
    )
    native.android_ndk_repository(
        name = "androidndk", 
        # path = ANDROID_NDK_HOME, # export ANDROID_NDK_HOME=$HOME/Desktop/workspace/android_sdk/ndk/26.1.10909125 
        api_level = 19
    )



############################# java env #############################

def java_env():
    git_repository(
        name = "rules_appengine",
        remote = "https://github.com/bazelbuild/rules_appengine.git",
        tag = "0.0.9",
    )
    # load("@rules_appengine//appengine:java_appengine.bzl", "java_appengine_repositories")
    # java_appengine_repositories()
    
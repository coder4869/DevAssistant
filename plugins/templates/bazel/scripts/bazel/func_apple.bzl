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

### [Apple](https://bazel.google.cn/versions/6.0.0/start/ios-app)
# https://github.com/bazelbuild/rules_apple/blob/master/doc/frameworks.md

load("//scripts/bazel:variables.bzl", 
    "COPTS", "OC_LINK_OPTS", "CC_VISIBILITY",
    "IOS_FAMILY",  "IOS_MIN_VERSION", "IOS_INFO_PLIST"
)

# ios section: ios_application() contains objc_library()
load("@build_bazel_rules_apple//apple:ios.bzl", "ios_application", "ios_framework")
# https://github.com/bazelbuild/rules_swift/blob/master/doc/rules.md#swift_library
# load("@build_bazel_rules_swift//swift:swift.bzl", "swift_library")
# load("@rules_xcodeproj//xcodeproj:defs.bzl", "top_level_target", "xcodeproj")

def oc_src():
    return native.glob(
        include = [ "**/*.c", "**/*.cc", "**/*.cpp", "**/*.h", "**/*.hpp" ],
        exclude = [ "**/test/**", "**/unused/**" ]
    )

def oc_hdrs():
    return native.glob(
        include = [ "**/*.h", "**/*.hpp"],
        exclude = [ "**/test/**", "**/unused/**" ]
    )

def oc_src_test():
    return native.glob(
        include = [ "**/test/*.c", "**/test/*.cc", "**/test/*.cpp", "**/test/*.h", "**/test/*.hpp" ],
        exclude = [ "**/unused/**" ]
    )


# framework
def ios_fmwk(name, bundle_id, deps = []):
    ios_framework(
        name = name,
        bundle_id = bundle_id,
        deps = deps,

        families = IOS_FAMILY,
        minimum_os_version = IOS_MIN_VERSION,
        infoplists = IOS_INFO_PLIST,
        visibility = CC_VISIBILITY,
        linkopts = OC_LINK_OPTS,
    )

def ios_app(name, bundle_id, deps = []):
    return ios_application(
        name = name,
        bundle_id = bundle_id,
        deps = deps,

        families = IOS_FAMILY,
        minimum_os_version = IOS_MIN_VERSION,
        infoplists = IOS_INFO_PLIST,
        visibility = CC_VISIBILITY,
        linkopts = OC_LINK_OPTS,
        # provisioning_profile = "<profile_name>.mobileprovision",
    )

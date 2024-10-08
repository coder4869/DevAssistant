# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

########################      Apple      ########################
# https://github.com/bazelbuild/rules_apple/tree/master/examples
# https://bazel.google.cn/versions/6.0.0/start/ios-app
# https://github.com/bazelbuild/rules_apple/blob/master/doc/tutorials/ios-app.md
# https://github.com/bazelbuild/rules_apple/blob/master/doc/frameworks.md
# https://github.com/bazel-xcode/xchammer

load("//scripts/bazel:variables.bzl", 
    "PROJECT_VERSION", "XC_BUILD_OS",
    "COPTS", "CC_VISIBILITY", "OC_LINK_OPTS", 
    "IOS_UI_LAUNCH", "IOS_INFO_PLIST",                  # IOS Data
    "IOS_FAMILY", "IOS_MIN_VERSION", "IOS_CPU_ARCH",    # IOS Config
    "MAC_MIN_VERSION"
)

load("@build_bazel_rules_apple//apple:apple_binary.bzl", "apple_binary")

# ios section: ios_application() contains objc_library()
load("@build_bazel_rules_apple//apple:ios.bzl", "ios_application", "ios_framework")
load("@build_bazel_rules_apple//apple:macos.bzl", "macos_application")
load("@build_bazel_rules_apple//apple:xcarchive.bzl", "xcarchive")
load("@build_bazel_rules_apple//apple:versioning.bzl", "apple_bundle_version")
# https://github.com/bazelbuild/rules_swift/blob/master/doc/rules.md#swift_library
# load("@build_bazel_rules_swift//swift:swift.bzl", "swift_library")
load("@rules_xcodeproj//xcodeproj:defs.bzl", "top_level_target", "xcodeproj")

def oc_src():
    return native.glob(
        include = [ "**/*.m", "**/*.mm", "**/*.c", "**/*.cc", "**/*.cpp", "**/*.h", "**/*.hpp" ],
        exclude = [ "**/test/**", "**/unused/**" ]
    )

def oc_hdrs():
    return native.glob(
        include = [ "**/*.h", "**/*.hpp"],
        exclude = [ "**/test/**", "**/unused/**" ]
    )

def oc_src_test():
    return native.glob(
        include = [ "**/test/*.m", "**/test/*.mm", "**/test/*.c", "**/test/*.cc", "**/test/*.cpp", "**/test/*.h", "**/test/*.hpp" ],
        exclude = [ "**/unused/**" ]
    )

def oc_storyboard():
    if XC_BUILD_OS == "ios" : # ios or macos
        return native.glob([ "Resources/ios/*.storyboard" ])
    return native.glob([ "Resources/mac/*.storyboard" ])

def app_icons():
    return native.glob(["Resources/Assets.xcassets/AppIcon.appiconset/*.png",
                        "Resources/Assets.xcassets/AppIcon.appiconset/*.json"])

# https://bazel.google.cn/configure/attributes?hl=en
# data = select({
#     "ios" : native.glob([ "Resources/ios/*.storyboard" ]),
#     "macos" : native.glob([ "Resources/mac/*.storyboard" ])
# }),
def oc_lib(name, deps = []):
    native.objc_library(
        name = name,
        srcs = oc_src(),
        hdrs = oc_hdrs(),
        data = oc_storyboard(),
        # linkstatic = 1,
        linkopts = OC_LINK_OPTS,
        # ios_multi_cpus = IOS_CPU_ARCH,
        copts = [  
            "-arch", "x86_64"
        ],  
        deps = deps,
        tags = [ "manual" ],
        visibility = CC_VISIBILITY,
    )

def ios_bin(name, deps = []):
    return apple_binary(
        name = name,
        deps = deps,

        # copts = COPTS,
        platform_type = "ios", # ios, macos
        minimum_os_version = IOS_MIN_VERSION,
        visibility = CC_VISIBILITY,
        linkopts = OC_LINK_OPTS,
    )

# framework
def ios_fmwk(name, bundle_id, deps = []):
    ios_framework(
        name = name,
        bundle_id = bundle_id,
        deps = deps,

        # IOS Data
        infoplists = IOS_INFO_PLIST,

        # IOS Config
        families = IOS_FAMILY,
        minimum_os_version = IOS_MIN_VERSION,
        visibility = CC_VISIBILITY,
        linkopts = OC_LINK_OPTS,
        # ios_multi_cpus = IOS_CPU_ARCH
    )

def ios_app(name, bundle_id, deps = []):
    apple_bundle_version(
        name = name + "Version",
        build_version = PROJECT_VERSION,
    )
    xcarchive(
        name = name + ".xcarchive",
        bundle = ":" + name,
    )
    ios_application(
        name = name,
        bundle_id = bundle_id,
        deps = deps,

        # IOS Data
        launch_storyboard  = IOS_UI_LAUNCH,
        app_icons   = app_icons(),
        infoplists  = IOS_INFO_PLIST,
        # provisioning_profile = "<profile_name>.mobileprovision",

        # IOS Config
        version     = ":" + name + "Version",
        families    = IOS_FAMILY,
        minimum_os_version = IOS_MIN_VERSION,
        visibility  = CC_VISIBILITY,
        linkopts    = OC_LINK_OPTS,
    )

def mac_app(name, bundle_id, deps = []):
    apple_bundle_version(
        name = name + "Version",
        build_version = PROJECT_VERSION,
    )
    macos_application(
        name = name,
        bundle_id = bundle_id,

        # Mac Data
        app_icons  = app_icons(),
        infoplists = IOS_INFO_PLIST,

        # Mac Config
        version = ":" + name + "Version",
        minimum_os_version = MAC_MIN_VERSION,
        deps = deps,
    )

# https://github.com/MobileNativeFoundation/rules_xcodeproj/blob/main/docs/bazel.md#xcodeproj
def xcode_proj(name, proj_name, top_level_targets):
    xcodeproj(
        name = name,
        build_mode = "bazel",
        project_name = proj_name,
        tags = ["manual"],
        visibility = CC_VISIBILITY,
        top_level_targets = top_level_targets,
    )
    
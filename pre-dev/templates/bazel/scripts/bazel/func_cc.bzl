# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

# Notes: 
# 1. glob() take BUILD.bazel dir as current root dir
# 2. glob() will ignore files in sub-dir which contains BUILD.bazel

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary", "cc_test")
load("//scripts/bazel:variables.bzl", "COPTS", "CC_LINK_OPTS", "CC_VISIBILITY")

def src_core():
    return native.glob(
        include = [ "**/*.c", "**/*.cc", "**/*.cpp", "**/*.h", "**/*.hpp" ],
        exclude = [ "**/test/**", "**/unused/**" ]
    )

def hdrs_core():
    return native.glob(
        include = [ "**/*.h", "**/*.hpp"],
        exclude = [ "**/test/**", "**/unused/**" ]
    )

def src_test():
    return native.glob(
        include = [ "**/test/*.c", "**/test/*.cc", "**/test/*.cpp", "**/test/*.h", "**/test/*.hpp" ],
        exclude = [ "**/unused/**" ]
    )

# static_lib
def cc_lib(name, deps = [], includes = [ "." ] ):
    cc_library(
        name = name,
        srcs = src_core(),
        hdrs = hdrs_core(),
        deps = deps,
        includes = includes,
        copts = COPTS,
        visibility = CC_VISIBILITY,
        linkopts = CC_LINK_OPTS,
        linkstatic = 1,
        # alwayslink = 1,
    )

# binary or shared lib
def cc_bin(name, deps = [], includes = [ "." ], shared=0):
    cc_binary(
        name = name,
        srcs = src_core(),
        deps = deps,
        includes = includes,
        copts = COPTS,
        visibility = CC_VISIBILITY,
        linkopts = CC_LINK_OPTS,
        # linkstatic = 1,
        linkshared = shared,
    )

# test_bin
def cc_bin_test(name, deps = [], includes = [ "." ]):
    cc_test(
        name = name,
        srcs = src_test(),
        deps = deps,
        includes = includes,
        copts = COPTS,
        size = "small",
        visibility = CC_VISIBILITY,
        linkopts = CC_LINK_OPTS,
    )

    # deps = [
    #     # ":hello-world",   # lib hello-world in current .bazel
    #     "//lib:extra_lib",  # local lib
    #     "@extra//lib/xxx:extra_lib"
    # ]
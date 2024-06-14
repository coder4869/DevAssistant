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

# Notes: 
# 1. glob() take BUILD.bazel dir as current root dir
# 2. glob() will ignore files in sub-dir which contains BUILD.bazel

load("@rules_cc//cc:defs.bzl", "cc_library", "cc_binary", "cc_test")

load("//scripts/bazel:variables.bzl", "COPTS")

VISIBILITY = [ "//visibility:public" ]
LINK_OPTS = ["-lstdc++"]

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
        visibility = VISIBILITY,
        linkopts = LINK_OPTS,
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
        visibility = VISIBILITY,
        linkopts = LINK_OPTS,
        # linkstatic = 1,
        linkshared = shared,
    )

# test_lib
def cc_lib_test(name, deps = [], includes = [ "." ]):
    cc_test(
        name = name,
        srcs = src_test(),
        deps = deps,
        includes = includes,
        copts = COPTS,
        size = "small",
        visibility = VISIBILITY,
        linkopts = LINK_OPTS,
    )

    # deps = [
    #     # ":hello-world",   # lib hello-world in current .bazel
    #     "//lib:extra_lib",  # local lib
    #     "@extra//lib/xxx:extra_lib"
    # ]
# Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

def gtest():
    git_repository(
        name = "com_google_googletest",
        remote = "https://github.com/google/googletest.git",
        # branch = "v1.14.0",
        # tag = "v1.14.0",
        commit = "f8d7d77c06936315286eb55f8de22cd23c188571",
    )

    # load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
    # protobuf_deps()

def spdlog():
    http_archive(  
        name = "spdlog",  
        urls = ["https://github.com/gabime/spdlog/archive/refs/tags/v1.14.1.tar.gz"],
        strip_prefix = "spdlog-1.14.1", 
        # build_file = "spdlog.BUILD",  
        # build_file = "//scripts/third_party:spdlog.BUILD",  
    )
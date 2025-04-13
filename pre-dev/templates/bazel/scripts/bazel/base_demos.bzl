
# [git](https://bazel.google.cn/rules/lib/repo/git)
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
git_repository(
    name = "com_github_grpc_grpc",                  # repo_name
    remote = "https://github.com/grpc/grpc.git",
    # branch = "v1.61.x",                           # branch_name
    tag = "v1.61.2",                                # tag_name
    # commit = "Commit_ID",
)
# load("@com_github_grpc_grpc//bazel:grpc_deps.bzl", "grpc_deps")
# grpc_deps()

# load("@com_github_grpc_grpc//bazel:grpc_extra_deps.bzl", "grpc_extra_deps")
# grpc_extra_deps()
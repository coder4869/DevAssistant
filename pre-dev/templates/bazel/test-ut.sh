#/bin/bash

cp WORKSPACE.bazel-unix WORKSPACE.bazel

echo "Mac/Linux test: reset bazel env"
# bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/
echo ""
echo ""

echo "Mac/Linux test: build and run all"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut
echo ""
echo ""

echo "Mac/Linux test: for parameter --platform UNIX"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut --platform 0
echo ""
echo ""

echo "Mac/Linux test: for parameter --gtest_filter TestDemo.*"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.*"
echo ""
echo ""

echo "Mac/Linux test: for parameter --gtest_filter TestDemo.Skip"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.Skip"
echo ""
echo ""

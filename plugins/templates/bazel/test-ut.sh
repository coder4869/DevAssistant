#/bin/bash

echo "Reset bazel env"
# bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/
echo ""

echo "Test all"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut
echo ""

echo "Test --platform UNIX"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut --platform 0
echo ""

echo "Test --gtest_filter TestDemo.*"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.*"
echo ""

echo "Test --gtest_filter TestDemo.Skip"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/test/ut-cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.Skip"
echo ""

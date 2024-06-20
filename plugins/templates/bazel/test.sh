#/bin/bash

echo "Reset bazel env"
bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/
echo ""

echo "Build src/cc:cc_static"
bazel build src/cc:cc_static && ls -al bazel-bin/src/cc | grep cc_static
echo ""

echo "Build src/cc:cc_shared"
bazel build src/cc:cc_shared && ls -al bazel-bin/src/cc | grep cc_shared
echo ""

echo "Build and run src/cc:cc_bin"
bazel build src/cc:cc_bin && ls -al bazel-bin/src/cc | grep cc_bin && bazel-bin/src/cc/cc_bin
echo ""
echo ""


echo "Build src/ios:oc_static"
bazel build src/ios:oc_static && ls -al bazel-bin/src/ios | grep oc_static
echo ""

echo "Build src/ios:oc_shared"
bazel build src/ios:oc_shared && ls -al bazel-bin/src/ios | grep oc_shared
echo ""

echo "Build src/ios:ios-app"
bazel build src/ios:ios-app && ls -al bazel-bin/src/ios
echo ""
echo ""


echo "Test all"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut
echo ""

echo "Test --platform UNIX"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut
echo ""

echo "Test --platform UNIX"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.*"
echo ""

echo "Test --platform UNIX"
bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.Skip"
echo ""

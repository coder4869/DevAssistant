#/bin/bash

echo "Reset bazel env"
# bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/
echo ""

echo "Build src/ios:oc_static"
# bazel build src/ios:oc_static && ls -al bazel-bin/src/ios
# bazel build src/ios:oc_static --ios_multi_cpus=armv7,arm64 && ls -al bazel-bin/src/ios
bazel build src/ios:oc_static --ios_multi_cpus=armv7,arm64 --xcode_version=14.0.1 && ls -al bazel-bin/src/ios && lipo -info bazel-bin/src/ios/liboc_static.a
echo ""

echo "Build src/ios:oc_shared"
bazel build src/ios:oc_shared && ls -al bazel-bin/src/ios && lipo -info bazel-bin/src/ios/oc_shared_bin
echo ""

echo "Build src/ios:Demo"
bazel build src/ios:Demo && ls -al bazel-bin/src/ios
echo ""

echo "Build src/ios:oc_bin"
bazel build src/ios:oc_bin && ls -al bazel-bin/src/ios && lipo -info bazel-bin/src/ios/oc_bin_bin 
echo ""

echo "Build src/ios:ios-app"
bazel build src/ios:ios-app && ls -al bazel-bin/src/ios
echo ""

echo "Build src/ios:mac-app"
bazel build src/ios:mac-app && ls -al bazel-bin/src/ios
echo ""
echo ""

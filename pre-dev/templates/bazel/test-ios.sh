#/bin/bash

cp WORKSPACE.bazel-unix WORKSPACE.bazel

echo "Apple demo: reset bazel env"
# bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/
echo ""
echo ""

echo "Apple library: build src/ios:oc_static"
# bazel build src/ios:oc_static && ls -al bazel-bin/src/ios
# bazel build src/ios:oc_static --ios_multi_cpus=armv7,arm64 && ls -al bazel-bin/src/ios
bazel build src/ios:oc_static --ios_multi_cpus=armv7,arm64 --xcode_version=14.0.1 && ls -al bazel-bin/src/ios && lipo -info bazel-bin/src/ios/liboc_static.a
echo ""
echo ""

echo "Apple framework: build src/ios:oc_fmwk"
# bazel build src/ios:oc_fmwk && ls -al bazel-bin/src/ios
# bazel build src/ios:oc_fmwk --ios_multi_cpus=armv7,arm64 && ls -al bazel-bin/src/ios
bazel build src/ios:oc_fmwk && ls -al bazel-bin/src/ios && lipo -info bazel-bin/src/ios/oc_fmwk_bin
echo ""
echo ""

echo "Apple binary: build src/ios:oc_bin"
# bazel build src/ios:oc_bin && ls -al bazel-bin/src/ios
# bazel build src/ios:oc_bin --ios_multi_cpus=armv7,arm64 && ls -al bazel-bin/src/ios  # invalid
bazel build src/ios:oc_bin && ls -al bazel-bin/src/ios && lipo -info bazel-bin/src/ios/oc_bin_bin
echo ""
echo ""

echo "Apple ios: build and run src/ios:ios-app"
# bazel build src/ios:ios-app && ls -al bazel-bin/src/ios 
# bazel build //src/ios:ios-app --ios_multi_cpus=arm6 # invalid
bazel run src/ios:ios-app
# bazel run src/ios:ios-app --ios_simulator_version=16.0
# bazel run src/ios:ios-app --ios_simulator_device="iPhone 14" --ios_simulator_version=16.0
echo ""
echo ""

echo "Apple mac: build and run src/ios:mac-app"
# bazel build src/ios:mac-app && ls -al bazel-bin/src/ios
echo ""
echo ""

echo "Apple Xcode: build and run src/ios:XCodeDemo"
# bazel build src/ios:XCodeDemo && ls -al bazel-bin/src/ios
# bazel run src/ios:XCodeDemo
echo ""
echo ""

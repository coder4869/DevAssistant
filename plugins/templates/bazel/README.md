## Introduce
- Clean: 
    * normal: `bazel clean --expunge`
    * async: 
        * mac: `bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/`
        * other: `bazel clean --expunge --async`

## C/C++(Mac/Linux)
- Build: 
    * static: `bazel build src/cc:cc_static && ls -al bazel-bin/src/cc | grep cc_static`
    * shared: `bazel build src/cc:cc_shared && ls -al bazel-bin/src/cc | grep cc_shared`
    * bin: `bazel build src/cc:cc_bin && ls -al bazel-bin/src/cc | grep cc_bin && bazel-bin/src/cc/cc_bin`

- Test:
    * default: 
        * `bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut`
        * `bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut --platform 0`
    * gtest: 
        * `bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.*"`
        * `bazel build test/ut-cc:cc_ut && ls -al bazel-bin/src/cc && bazel-bin/test/ut-cc/cc_ut --gtest_filter="TestDemo.Skip"`

## Apple(Mac)
- Build: 
    * static: `bazel build src/ios:oc_static && ls -al bazel-bin/src/ios`
    * framework: `bazel build src/ios:oc_shared && ls -al bazel-bin/src/ios`
    * app: 
        * `bazel build //src/ios:ios-app && ls -al bazel-bin/src/ios`
        * `bazel build //src/ios:ios-app --ios_multi_cpus=armv7,arm64` (invalid)

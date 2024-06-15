## Introduce
- Clean: 
    * normal: `bazel clean --expunge`
    * async: `bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/`

## C/C++
- Build: 
    * static: `bazel build src/cc:cc_static`
    * shared: `bazel build src/cc:cc_shared`
    * bin: `bazel build src/cc:cc_bin && bazel-bin/src/cc/cc_bin`

- Test:
    * default: `bazel build test/ut-cc:cc_ut && bazel-bin/test/ut-cc/cc_ut --platform 0`
    * use gtest: 
        * `bazel build test/ut-cc:cc_ut && bazel-bin/test/ut-cc/cc_ut --gtest_filter="BaseTest.*"`
        * `bazel build test/ut-cc:cc_ut && bazel-bin/test/ut-cc/cc_ut --gtest_filter="BaseTest.Demo"`

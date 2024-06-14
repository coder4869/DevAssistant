## Introduce

## Build
- Build: 
    * static: `bazel build src:cc_static`
    * shared: `bazel build src:cc_shared`
    * bin: `bazel build src:cc_bin && bazel-bin/src/cc_bin`

- Test:
    * default: `bazel build test/ut:cc_ut && bazel-bin/test/ut/cc_ut --platform 0`
    * use gtest: 
        * `bazel build test/ut:cc_ut && bazel-bin/test/ut/cc_ut --gtest_filter="BaseTest.*"`
        * `bazel build test/ut:cc_ut && bazel-bin/test/ut/cc_ut --gtest_filter="BaseTest.Demo"`

- Clean: `bazel clean --expunge`
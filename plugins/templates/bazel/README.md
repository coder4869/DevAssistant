## Introduce
- https://bazel.google.cn/versions/7.1.0/rules/lib/globals/workspace

- Clean: 
    * normal: `bazel clean --expunge`
    * async: 
        * mac: `bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/`
        * other: `bazel clean --expunge --async`

## C/C++
- Mac/Linux demo: 
    * build and run refer to script [test-cc.sh](./test-cc.sh) 
    * test refer to script [test-ut.sh](./test-ut.sh)

## Apple(Mac)
- Demo: refer to script [test-ios.sh](./test-ios.sh) 

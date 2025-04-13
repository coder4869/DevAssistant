## Introduce
- https://github.com/bazelbuild/bazel
- releases: https://github.com/bazelbuild/bazel/releases
- start: https://bazel.build/start

- Clean: 
    * normal: `bazel clean --expunge`
    * async: 
        * mac: `bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/`
        * other: `bazel clean --expunge --async`

## C/C++
- Mac/Linux demo: 
    * build and run refer to script [test-cc.sh](./test-cc.sh) 
    * test refer to script [test-ut.sh](./test-ut.sh)
    
- Windows demo: 
    * build and run refer to script [test-cc.bat](./test-cc.bat) 
    * test refer to script [test-ut.bat](./test-ut.bat)

## Apple(Mac)
- Demo: refer to script [test-ios.sh](./test-ios.sh) 

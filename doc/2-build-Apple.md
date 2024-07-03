## Apple

### ios.toolchain.cmake
- Source: https://github.com/leetal/ios-cmake

- Usage
    * `cmake -B build -G Xcode -DCMAKE_TOOLCHAIN_FILE=cmake/cmake-apple/ios.toolchain.cmake -DPLATFORM=OS64`
    * `cmake --build build --config Release`
    * `cmake --install build --config Release` Necessary to build combined library

- Platform flag options (-DPLATFORM=_flag_)
    * _OS_ - to build for iOS (armv7, armv7s, arm64) **DEPRECATED in favour of OS64**
    * _OS64_ - to build for iOS (arm64 only)
    * _OS64COMBINED_ - to build for iOS & iOS Simulator (FAT lib) (arm64, x86_64)
    * _SIMULATOR_ - to build for iOS simulator 32 bit (i386) **DEPRECATED**
    * _SIMULATOR64_ - to build for iOS simulator 64 bit (x86_64)
    * _SIMULATORARM64_ - to build for iOS simulator 64 bit (arm64)
    * _TVOS_ - to build for tvOS (arm64)
    * _TVOSCOMBINED_ - to build for tvOS & tvOS Simulator (arm64, x86_64)
    * _SIMULATOR_TVOS_ - to build for tvOS Simulator (x86_64)
    * _SIMULATORARM64_TVOS_ = to build for tvOS Simulator (arm64)
    * _WATCHOS_ - to build for watchOS (armv7k, arm64_32)
    * _WATCHOSCOMBINED_ - to build for watchOS & Simulator (armv7k, arm64_32, i386)
    * _SIMULATOR_WATCHOS_ - to build for watchOS Simulator (i386)
    * _SIMULATORARM64_WATCHOS_ = to build for watchOS Simulator (arm64)
    * _MAC_ - to build for macOS (x86_64)
    * _MAC_ARM64_ - to build for macOS on Apple Silicon (arm64)
    * _MAC_UNIVERSAL_ - to build for macOS on x86_64 and Apple Silicon (arm64) combined
    * _MAC_CATALYST_ - to build iOS for Mac (Catalyst, x86_64)
    * _MAC_CATALYST_ARM64_ - to build iOS for Mac on Apple Silicon (Catalyst, arm64)

- More Configs: https://github.com/leetal/ios-cmake/blob/master/README.md
    * `XCODE_VERSION` - Version number (not including Build version) of Xcode detected.
    * `SDK_VERSION` - Version of SDK being used.
    * `CMAKE_OSX_ARCHITECTURES` - Architectures being compiled for (generated from PLATFORM).
    * `APPLE_TARGET_TRIPLE` - Used by autoconf build systems.
    * `-DENABLE_BITCODE=(BOOL)` - Disabled by default, specify TRUE or 1 to enable bitcode
    * `-DENABLE_ARC=(BOOL)` - Enabled by default, specify FALSE or 0 to disable ARC
    * `-DENABLE_VISIBILITY=(BOOL)` - Disabled by default, specify TRUE or 1 to enable symbol visibility support
    * `-DENABLE_STRICT_TRY_COMPILE=(BOOL)` - Disabled by default, specify TRUE or 1 to enable strict compiler checks (will run linker on all compiler checks whenever needed)
    * `-DARCHS=(STRING)` - Valid values are: armv7, armv7s, arm64, i386, x86_64, armv7k, arm64_32. By default it will build for all valid architectures based on `-DPLATFORM` (see above)

### Issues
- xcode `Products` Dir not found
    * open `project.pbxproj` by vscode; use value of `mainGroup` replace value of `productRefGroup`
## Windows
### build
- check `QT_INSTALL_DIR` and `PY_INSTALL_DIR` in `run_win.bat`.
- run `run_win.bat` as Administrator by right-action.
- build generated vs-project.

### output
- build `CMakePredefinedTargets/INSTALL` target on generated vs-project.

- libs: `build_win/lib`
- include: `build_win/include`
- bin: `bin64`


## Linux and MacOS
### build
- check `QT_INSTALL_DIR` and `PY_INSTALL_DIR` in `run_unix.sh`.

- 1-MacOS:
    * `sh /opt/shared_dir/DevAssistant/app/run_unix.sh`
- 2-Linux:
    * Setup-env: `bash /opt/shared_dir/DevAssistant/tools/setup-env.sh`
    * Run way1:
        * `sed -i 's/\r//' /opt/shared_dir/DevAssistant/app/run_unix.sh && bash /opt/shared_dir/DevAssistant/app/run_unix.sh`
    * Run way2:
        * `sudo apt-get install -y dos2unix && dos2unix /opt/shared_dir/DevAssistant/app/run_unix.sh && bash /opt/shared_dir/DevAssistant/app/run_unix.sh`

### output
- libs: `build_unix/lib`
- include: `build_unix/include`
- bin: `bin64`


## Android
### build
- check `ANDROID_SDK_HOME`, `ANDROID_NDK_HOME`, `ANDROID_ABI`, `ANDROID_API` and `ANDROID_CMAKE_BIN` in `run_android.sh`.

- 1-MacOS:
    * `sh /opt/shared_dir/DevAssistant/app/run_android.sh`
- 2-Linux:
    * Setup-env: `bash /opt/shared_dir/DevAssistant/tools/setup-env.sh`
    * Run way1:
        * `sed -i 's/\r//' /opt/shared_dir/DevAssistant/app/run_android.sh && bash /opt/shared_dir/DevAssistant/app/run_android.sh`
    * Run way2:
        * `sudo apt-get install -y dos2unix && dos2unix /opt/shared_dir/DevAssistant/app/run_android.sh && bash /opt/shared_dir/DevAssistant/app/run_android.sh`
- 3-Windows:
    - run `run_android.bat` by double click.

### output
- libs: `build_android/arm64-v8a`
- include: `build_android/include`
- bin: `bin64`
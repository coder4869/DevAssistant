@REM Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

@echo off

::set var
SET PROJ_NAME=DevAssistant
SET ROOT_DIR=%~dp0
SET BUILD_DIR=%ROOT_DIR%\build_android
SET BIN_DIR=%ROOT_DIR%\bin64
SET ANDROID_SDK_HOME=F:\Android\android_sdk
SET ANDROID_NDK_HOME=%ANDROID_SDK_HOME%\ndk\26.1.10909125
SET ANDROID_CMAKE_BIN=%ANDROID_SDK_HOME%\cmake\3.22.1\bin

::echo var
echo PROJ_NAME = %PROJ_NAME%
echo ROOT_DIR = %ROOT_DIR%
echo BUILD_DIR = %BUILD_DIR%
echo BIN_DIR = %BIN_DIR%
echo ANDROID_SDK_HOME = %ANDROID_SDK_HOME%
echo ANDROID_NDK_HOME = %ANDROID_NDK_HOME%
echo ANDROID_CMAKE_BIN = %ANDROID_CMAKE_BIN%

:: make %BUILD_DIR% and cd %BUILD_DIR% 
:: cd %ROOT_DIR%
:: https://blog.csdn.net/xiaoerbuyu1233/article/details/108490963 RMDIR %BUILD_DIR% /S /Q
if exist %BUILD_DIR% rd /s /q %BUILD_DIR%
md %BUILD_DIR%
if exist %BIN_DIR% rd /s /q %BIN_DIR%

:: clean py cache
SET PLUGIN_DIR=%ROOT_DIR%\app\data\plugins
echo PLUGIN_DIR = %PLUGIN_DIR%
for /f "delims=" %%i in ('dir /ad/b/s "%PLUGIN_DIR%"') do (
    if exist %%i\.DS_Store rd /s /q %%i\.DS_Store
    if exist %%i\__pycache__ rd /s /q %%i\__pycache__
)

SET ANDROID_ABI=arm64-v8a
SET ANDROID_API=21

cd %BUILD_DIR%

%ANDROID_CMAKE_BIN%\cmake -Wno-dev %ROOT_DIR% -DCMAKE_BUILD_TYPE=Release ^
    -DCMAKE_INSTALL_PREFIX=%BUILD_DIR% ^
    -DEXECUTABLE_OUTPUT_PATH=%BIN_DIR% ^
    -DWITH_QT=OFF -DWITH_PY=OFF ^
    -DPROJECT_NAME=%PROJ_NAME% -DANDROID=ON -H%ROOT_DIR% -B%BUILD_DIR% ^
    -DANDROID_ABI=%ANDROID_ABI% -DANDROID_NDK=%ANDROID_NDK_HOME% ^
    -DCMAKE_TOOLCHAIN_FILE=%ANDROID_NDK_HOME%\build\cmake\android.toolchain.cmake ^
    -DANDROID_NATIVE_API_LEVEL=%ANDROID_API% -DANDROID_TOOLCHAIN=clang -DCMAKE_GENERATOR="Ninja" ^
    -DCMAKE_MAKE_PROGRAM=%ANDROID_CMAKE_BIN%\ninja.exe

%ANDROID_CMAKE_BIN%\ninja.exe
%ANDROID_CMAKE_BIN%\ninja.exe install

if not exist %BUILD_DIR%\%ANDROID_ABI% md %BUILD_DIR%\%ANDROID_ABI%
copy %BUILD_DIR%\*.so %BUILD_DIR%\%ANDROID_ABI%\

echo. & pause 
                                                                                                                      
@REM MIT License
@REM 
@REM Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)
@REM 
@REM Permission is hereby granted, free of charge, to any person obtaining a copy
@REM of this software and associated documentation files (the "Software"), to deal
@REM in the Software without restriction, including without limitation the rights
@REM to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
@REM copies of the Software, and to permit persons to whom the Software is
@REM furnished to do so, subject to the following conditions:
@REM 
@REM The above copyright notice and this permission notice shall be included in all
@REM copies or substantial portions of the Software.
@REM 
@REM THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
@REM IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
@REM FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
@REM AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
@REM LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
@REM OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
@REM SOFTWARE.
@REM 
@echo off

::set var
SET PROJ_NAME=DevAssistant
SET ROOT_DIR=%~dp0\..\..
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
SET PLUGIN_DIR=%ROOT_DIR%\..\plugins
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

if not exist %BUILD_DIR%\%ANDROID_ABI% md %BUILD_DIR%\%ANDROID_ABI%
copy %BUILD_DIR%\*.so %BUILD_DIR%\%ANDROID_ABI%\

echo. & pause 

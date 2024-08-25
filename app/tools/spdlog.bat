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

set ROOT_DIR=%~dp0
SET VERSION=1.14.1
SET PROJ_DIR=%ROOT_DIR%\spdlog-%VERSION%
SET BUILD_DIR=%PROJ_DIR%\build_win
:: https://www.cnblogs.com/doudougou/archive/2011/08/22/2148851.html
@REM REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\devenv.exe"
SET VS_EXE="C:\Program Files\Microsoft Visual Studio\2022\Community\Common7\IDE\devenv.exe"
SET VS_PROJ="%BUILD_DIR%\spdlog.sln"

cd %ROOT_DIR%

echo "start download spdlog"
curl -o spdlog-%VERSION%.tar.gz https://github.com/gabime/spdlog/archive/refs/tags/v%VERSION%.tar.gz
@REM PowerShell -Command "(New-Object System.Net.WebClient).DownloadFile('https://github.com/gabime/spdlog/archive/refs/tags/v%VERSION%.tar.gz', 'spdlog-%VERSION%.tar.gz')"
echo "finish download spdlog"

tar -zvxf spdlog-%VERSION%.tar.gz

@REM https://blog.csdn.net/xiaoerbuyu1233/article/details/108490963 RMDIR %BUILD_DIR% /S /Q
if exist %BUILD_DIR% rd /s /q %BUILD_DIR%
md %BUILD_DIR%

@REM build windows
@REM echo "set(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} -std=c++11 -O1\")"  >> ../CMakeLists.txt
:: run cmake: gen vs-project
:: -G"Visual Studio 15 2017"
:: -G"Visual Studio 16 2019"
:: -G"Visual Studio 17 2022"
cmake -Wno-dev -S %PROJ_DIR% -H%PROJ_DIR% -B%BUILD_DIR% -G"Visual Studio 17 2022" -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=%BUILD_DIR%
if exist %VS_PROJ% start %VS_EXE% %VS_PROJ%

echo. & pause 

SET BIN_DIR=%~dp0
SET CACHE_DIR=%BIN_DIR%\..\..\Cache

echo "BIN_DIR  =%BIN_DIR%"
echo "CACHE_DIR=%CACHE_DIR%"
cd %CACHE_DIR%

setlocal ENABLEDELAYEDEXPANSION
for /F "delims=" %%v in ('cmake --version') do (set CMAKE_VERSION=%%v)
if defined CMAKE_VERSION (
    echo "CMake installed!"
    echo !CMAKE_VERSION!
) else (
    echo "download cmake-3.28.1-amd64.exe"
    wget -O cmake-3.28.1-amd64.exe https://github.com/Kitware/CMake/releases/download/v3.28.1/cmake-3.28.1-windows-arm64.msi  
    echo "install cmake-3.28.1-amd64.exe"
    start /wait cmake-3.28.1-amd64.exe
)
@REM pause
@REM exit

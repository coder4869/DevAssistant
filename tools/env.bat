@REM Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

@echo off

@REM ::Set var
SET ROOT_DIR=%~dp0\..

@REM ::Install Python
echo "Check python Env"
start /wait %ROOT_DIR%\tools\python\install-py-3.11.bat

@REM ::Install CMake
echo "Check CMake Env"
@REM start /wait %ROOT_DIR%\tools\pkg_config\install-cmake.bat

@REM HKEY_LOCAL_MACHINE\SOFTWARE\Kitware\CMake\InstallDir
@REM C:\Program Files\CMake\

pause

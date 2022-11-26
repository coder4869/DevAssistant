@echo off

::set var
SET APP_NAME=PROJ_NAME
SET ROOT_DIR=%~dp0\..\..
SET BUILD_DIR=%ROOT_DIR%\build
SET VS_EXE="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\Common7\IDE\devenv.exe"
SET VS_PROJ="%BUILD_DIR%\%APP_NAME%.sln"
SET QT_INSTALL_DIR="C:/Qt/Qt5.14.2/5.14.2/msvc2017_64"

::echo var
echo APP_NAME = %APP_NAME%
echo ROOT_DIR = %ROOT_DIR%
echo BUILD_DIR = %BUILD_DIR%
echo VS_EXE = %VS_EXE%
echo VS_PROJ = %VS_PROJ%
echo QT_INSTALL_DIR = %QT_INSTALL_DIR%

:: make %BUILD_DIR% and cd %BUILD_DIR% 
:: cd %ROOT_DIR%
if exist %BUILD_DIR% rd /s /q %BUILD_DIR%
md %BUILD_DIR%
cd %BUILD_DIR%

:: run cmake: gen vs-project
cmake -Wno-dev %ROOT_DIR%  -G"Visual Studio 16 2019" -DCMAKE_BUILD_TYPE=Release -DPROJECT_NAME=%APP_NAME% -DCMAKE_PREFIX_PATH=%QT_INSTALL_DIR% -DQT_INSTALL_DIR=%QT_INSTALL_DIR%
if exist %VS_PROJ% start %VS_EXE% %VS_PROJ%

echo. & pause 
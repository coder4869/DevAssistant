@echo off
echo start packaging exe installer

::set var
SET PROJ_NAME=DevAssistant
SET ROOT_DIR=%~dp0
SET SCRIPT_DIR=%~dp0\scripts\pkg-win
SET BIN_DIR="%ROOT_DIR%\bin64\bin64"

::echo var
echo PROJ_NAME = %PROJ_NAME%
echo ROOT_DIR = %ROOT_DIR%
echo SCRIPT_DIR = %SCRIPT_DIR%
echo BIN_DIR = %BIN_DIR%
echo QT_HOME = %QT_HOME%

rd /s /q "%ROOT_DIR%\bin64\bin64"
@REM xcopy /E /I /s /y "%ROOT_DIR%\bin64\Debug" %BIN_DIR%
xcopy /E /I /s /y "%ROOT_DIR%\bin64\Release" %BIN_DIR%
start /wait %QT_HOME%\bin\windeployqt.exe -qmldir %QT_HOME%/qml %BIN_DIR%\%PROJ_NAME%.exe

call %SCRIPT_DIR%\vs-env.bat

set VERSION="1.1.1.0"
echo packaging %VERSION% for "x64"
makensis /INPUTCHARSET UTF8 /DPRODUCT_NAME=%PROJ_NAME% /DPRODUCT_VERSION=%VERSION% /DOS_ARCH="x64" %SCRIPT_DIR%/pkg-win-nsis.nsi
echo packaging %VERSION% for "x86"
makensis /INPUTCHARSET UTF8 /DPRODUCT_NAME=%PROJ_NAME% /DPRODUCT_VERSION=%VERSION% /DOS_ARCH="x86" %SCRIPT_DIR%/pkg-win-nsis.nsi
echo packaging %VERSION% for "arm64"
makensis /INPUTCHARSET UTF8 /DPRODUCT_NAME=%PROJ_NAME% /DPRODUCT_VERSION=%VERSION% /DOS_ARCH="arm64" %SCRIPT_DIR%/pkg-win-nsis.nsi

move "%SCRIPT_DIR%\%PROJ_NAME%*.exe" "%ROOT_DIR%"

echo. & pause 
@echo off
echo start packaging exe installer

::set var
SET PROJ_NAME=DevAssistant
SET ROOT_DIR=%~dp0\..\..
SET SCRIPT_DIR=%~dp0
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
xcopy /s /y "%SCRIPT_DIR%\killproc.bat" "%BIN_DIR%\"
start /wait %QT_HOME%\bin\windeployqt.exe -qmldir %QT_HOME%/qml %BIN_DIR%\%PROJ_NAME%.exe

call vs-env.bat

makensis /INPUTCHARSET UTF8 %SCRIPT_DIR%/pkg-win-nsis.nsi 
@REM -version="1.0.1.0"

echo. & pause 
echo. & pause 
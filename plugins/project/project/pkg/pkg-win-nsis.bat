@echo off
echo start

::set var
SET ROOT_DIR=%~dp0
makensis /INPUTCHARSET UTF8 %ROOT_DIR%/pkg-win-nsis.nsi

echo. & pause 
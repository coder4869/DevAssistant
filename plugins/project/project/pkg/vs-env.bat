
@echo off
setlocal enabledelayedexpansion
echo start check vc_redist 
set "vsPath="
set "vsHome="

for /f "tokens=2,*" %%a in ('REG QUERY "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\devenv.exe"') do (
    set vsPath=%%b
)
echo Visual Studio installation path: %vsPath%

if not defined vsPath (
    echo Visual Studio 2019 or newer not found.
    pause
    exit
) else (
    if exist %vsPath% (
        echo remove "\Common7\IDE\devenv.exe"
        set "vsHome=%vsPath:~1,-23%"
    ) else (
        echo %vsPath% not exist
        echo please check regedit "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\App Paths\devenv.exe"
        pause
        exit
    )
)
echo Visual Studio install home: %vsHome%

set MSVC_DIR=%vsHome%VC\Redist\MSVC
echo VC++ Redistributable path: %MSVC_DIR%

set DST_DIR=%~dp0\vc_redist\
if exist "%MSVC_DIR%\v142" (
    echo f | xcopy /s /y "%MSVC_DIR%\v142\vc_redist.*.exe" "%DST_DIR%"
) else if exist "%MSVC_DIR%\v143" (
    echo f | xcopy /s /y "%MSVC_DIR%\v143\vc_redist.*.exe" "%DST_DIR%"
) else (
    echo vc_redist for 2019 or newer not found.
    pause
    exit
)

@REM echo . & pause
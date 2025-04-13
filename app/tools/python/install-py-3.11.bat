
SET BIN_DIR=%~dp0
SET CACHE_DIR=%BIN_DIR%\..\..\Cache

echo "BIN_DIR  =%BIN_DIR%"
echo "CACHE_DIR=%CACHE_DIR%"
cd %CACHE_DIR%

setlocal ENABLEDELAYEDEXPANSION
for /F "delims=" %%v in ('python --version') do (set PY_VERSION=%%v)
if defined PY_VERSION (
    echo "python installed!"
    echo !PY_VERSION!
) else (
    echo "download python-3.11.6-amd64.exe"
    wget -O python-3.11.6-amd64.exe https://www.python.org/ftp/python/3.11.6/python-3.11.6-amd64.exe  
    echo "install python-3.11.6-amd64.exe"
    start /wait python-3.11.6-amd64.exe
    
    if exist %LOCALAPPDATA%\Programs\Python\Python311\python.exe (
        setx PATH "%PATH%;%LOCALAPPDATA%\Programs\Python\Python311;%LOCALAPPDATA%\Programs\Python\Python311\Scripts"
    ) else if exist %LOCALAPPDATA%\Programs\Python\Python311-32\python.exe (
        setx PATH "%PATH%;%LOCALAPPDATA%\Programs\Python\Python311-32;%LOCALAPPDATA%\Programs\Python\Python311-32\Scripts"
    )
)

@REM pause
@REM exit

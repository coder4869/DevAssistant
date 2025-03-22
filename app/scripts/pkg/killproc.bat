@echo start-kill-running-process

net session >nul 2>&1
if %errorLevel% neq 0 (
    echo 正在请求管理员权限... >> C:\Porter-bat.log
    powershell -Command "Start-Process cmd -ArgumentList '/c %~s0' -Verb RunAs"
    exit /b
)

set program="Porter.exe"
taskkill /F /IM "Porter.exe" /t 2>nul
if %errorLevel% equ 0 (
    echo [成功] 已终止进程：%program%   >> C:\Porter-bat.log
) else (
    echo [失败] 无法终止进程 %program%  >> C:\Porter-bat.log
    echo 可能原因：
    echo 1. 该进程不存在                       >> C:\Porter-bat.log
    echo 2. 没有终止权限（即使提权后仍可能失败） >> C:\Porter-bat.log
)

@REM pause >nul
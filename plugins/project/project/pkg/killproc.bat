@echo start-kill-running-process

net session >nul 2>&1
if %errorLevel% neq 0 (
    echo �����������ԱȨ��... >> C:\Porter-bat.log
    powershell -Command "Start-Process cmd -ArgumentList '/c %~s0' -Verb RunAs"
    exit /b
)

set program="Porter.exe"
taskkill /F /IM "Porter.exe" /t 2>nul
if %errorLevel% equ 0 (
    echo [�ɹ�] ����ֹ���̣�%program%   >> C:\Porter-bat.log
) else (
    echo [ʧ��] �޷���ֹ���� %program%  >> C:\Porter-bat.log
    echo ����ԭ��
    echo 1. �ý��̲�����                       >> C:\Porter-bat.log
    echo 2. û����ֹȨ�ޣ���ʹ��Ȩ���Կ���ʧ�ܣ� >> C:\Porter-bat.log
)

@REM pause >nul
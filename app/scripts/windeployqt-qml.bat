@REM Copyright (c) 2021~2024 [coder4869](https://github.com/coder4869)

set ROOT=%~dp0\..

start /wait %QT_HOME%\bin\windeployqt.exe -qmldir %QT_HOME%/qml %ROOT%\bin64\Debug\DevAssistant.exe
start /wait %QT_HOME%\bin\windeployqt.exe -qmldir %QT_HOME%/qml %ROOT%\bin64\Release\DevAssistant.exe

@REM Fix "QtQuick.Shapes" load failed issue
@REM xcopy /S /F /Y %QT_HOME%\bin\Qt5QuickShapes.dll %ROOT%\bin64\Release\Qt5QuickShapes.dll
@REM MD %ROOT%\bin64\QtQuick\Shapes
@REM xcopy /S /F /Y %QT_HOME%\qml\QtQuick\Shapes\* %ROOT%\bin64\Release\QtQuick\Shapes\

pause
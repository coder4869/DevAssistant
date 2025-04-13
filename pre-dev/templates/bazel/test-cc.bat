ROOT_DIR=%~dp0
echo "ROOT_DIR=%ROOT_DIR%"
cd "%ROOT_DIR%"

echo f | xcopy /f /y WORKSPACE.bazel-win WORKSPACE.bazel

echo "Windows C/C++: reset bazel env"
@REM .\tools\bazel_7.2.1.exe clean --expunge --async
echo ""
echo ""

echo "Windows C/C++: build src/cc:cc_static"
.\tools\bazel_7.2.1.exe build src/cc:cc_static 
dir bazel-bin\src\cc
echo " "
echo " "

echo "Windows C/C++: build src/cc:cc_shared"
.\tools\bazel_7.2.1.exe build src/cc:cc_shared
dir bazel-bin\src\cc
echo ""
echo ""

echo "Windows C/C++: build and run src/cc:cc_bin"
.\tools\bazel_7.2.1.exe build src/cc:cc_bin
dir bazel-bin\src\cc
.\bazel-bin\src\cc\cc_bin.exe
echo ""
echo ""

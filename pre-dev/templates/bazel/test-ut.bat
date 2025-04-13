ROOT_DIR=%~dp0
echo "ROOT_DIR=%ROOT_DIR%"
cd "%ROOT_DIR%"

echo f | xcopy /f /y WORKSPACE.bazel-win WORKSPACE.bazel

echo "Windows test: reset bazel env"
@REM .\tools\bazel_7.2.1.exe clean --expunge --async
echo ""
echo ""

echo "Windows test: build and run all"
.\tools\bazel_7.2.1.exe build test/ut-cc:cc_ut
dir bazel-bin\test\ut-cc
.\bazel-bin\test\ut-cc\cc_ut.exe
echo ""
echo ""

echo "Windows test: for parameter --platform UNIX"
.\tools\bazel_7.2.1.exe build test/ut-cc:cc_ut
dir bazel-bin\test\ut-cc 
.\bazel-bin\test\ut-cc\cc_ut.exe --platform 0
echo ""
echo ""

echo "Windows test: for parameter --gtest_filter TestDemo.*"
.\tools\bazel_7.2.1.exe build test/ut-cc:cc_ut
dir bazel-bin\test\ut-cc
.\bazel-bin\test\ut-cc\cc_ut.exe --gtest_filter="TestDemo.*"
echo ""
echo ""

echo "Windows test: for parameter --gtest_filter TestDemo.Skip"
.\tools\bazel_7.2.1.exe build test/ut-cc:cc_ut
dir bazel-bin\test\ut-cc
.\bazel-bin\test\ut-cc\cc_ut.exe --gtest_filter="TestDemo.Skip"
echo ""
echo ""

#/bin/bash

echo "Reset bazel env"
# bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/
echo ""

echo "Build src/cc:cc_static"
bazel build src/cc:cc_static && ls -al bazel-bin/src/cc | grep cc_static
echo ""

echo "Build src/cc:cc_shared"
bazel build src/cc:cc_shared && ls -al bazel-bin/src/cc | grep cc_shared
echo ""

echo "Build and run src/cc:cc_bin"
bazel build src/cc:cc_bin && ls -al bazel-bin/src/cc | grep cc_bin && bazel-bin/src/cc/cc_bin
echo ""
echo ""

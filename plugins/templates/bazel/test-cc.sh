#/bin/bash

cp WORKSPACE.bazel-unix WORKSPACE.bazel

echo "Mac/Linux C/C++: reset bazel env"
# bazel clean --expunge --async && rm -rf /private/var/tmp/_bazel_mac/
echo ""
echo ""

echo "Mac/Linux C/C++: build src/cc:cc_static"
bazel build src/cc:cc_static && ls -al bazel-bin/src/cc | grep cc_static
echo ""
echo ""

echo "Mac/Linux C/C++: build src/cc:cc_shared"
bazel build src/cc:cc_shared && ls -al bazel-bin/src/cc | grep cc_shared
echo ""
echo ""

echo "Mac/Linux C/C++: build and run src/cc:cc_bin"
bazel build src/cc:cc_bin && ls -al bazel-bin/src/cc | grep cc_bin && bazel-bin/src/cc/cc_bin
echo ""
echo ""

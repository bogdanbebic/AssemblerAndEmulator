#!/bin/bash

AS_DIR=$(realpath `git rev-parse --git-dir`/..)/assembler

echo "build assembler"
pushd $AS_DIR > /dev/null
make test
echo "assembler build successfull"
popd > /dev/null
echo "unit test assembler"
$AS_DIR/build/test_assembler "$@"

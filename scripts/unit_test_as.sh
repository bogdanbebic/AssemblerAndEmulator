#!/bin/bash

AS_DIR=$(realpath `git rev-parse --git-dir`/..)/assembler

echo "build assembler"
pushd $AS_DIR > /dev/null
make test
exit_code=$?
if [[ $exit_code -ne 0 ]] ; then
    echo "assembler build failed"
    popd > /dev/null
    exit $exit_code
fi

echo "assembler build successfull"
popd > /dev/null
echo "unit test assembler"
$AS_DIR/build/test_assembler "$@"
exit_code=$?

exit $exit_code

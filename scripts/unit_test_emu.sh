#!/bin/bash

EMU_DIR=$(realpath `git rev-parse --git-dir`/..)/emulator

echo "build emulator"
pushd $EMU_DIR > /dev/null
make test
exit_code=$?
if [[ $exit_code -ne 0 ]] ; then
    echo "emulator build failed"
    popd > /dev/null
    exit $exit_code
fi

echo "emulator build successfull"
popd > /dev/null
echo "unit test emulator"
$EMU_DIR/build/test_emulator "$@"
exit_code=$?

exit $exit_code

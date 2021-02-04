#!/bin/bash

EMU_DIR=$(realpath `git rev-parse --git-dir`/..)/emulator

echo build emulator
pushd $EMU_DIR > /dev/null
make
popd > /dev/null
echo emulator build successfull

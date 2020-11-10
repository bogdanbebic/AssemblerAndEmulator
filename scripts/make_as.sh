#!/bin/bash

AS_DIR=$(realpath `git rev-parse --git-dir`/..)/assembler

echo build assembler
pushd $AS_DIR > /dev/null
make
popd > /dev/null
echo assembler build successfull

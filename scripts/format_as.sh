#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

AS_DIR=$ROOT_DIR/assembler

echo format assembler
pushd $ROOT_DIR > /dev/null
clang-format -i $AS_DIR/source/* $AS_DIR/test/* $AS_DIR/include/*
popd > /dev/null

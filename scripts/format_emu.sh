#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

EMU_DIR=$ROOT_DIR/emulator

echo format emulator
pushd $ROOT_DIR > /dev/null
clang-format -i $EMU_DIR/source/* $EMU_DIR/include/*
popd > /dev/null

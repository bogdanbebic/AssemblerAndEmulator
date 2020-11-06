#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

# assembler paths
VS_EMULATOR_DIR=${ROOT_DIR}/VisualStudio/Emulator/Emulator
EMULATOR_DIR=${ROOT_DIR}/emulator

# copy assembler source files
cp ${VS_EMULATOR_DIR}/*.h ${EMULATOR_DIR}/include/
cp ${VS_EMULATOR_DIR}/*.cpp ${EMULATOR_DIR}/source/

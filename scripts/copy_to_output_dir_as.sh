#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

# assembler paths
VS_ASSEMBLER_DIR=${ROOT_DIR}/VisualStudio/Assembler/Assembler
ASSEMBLER_DIR=${ROOT_DIR}/assembler

# copy assembler source files
cp ${VS_ASSEMBLER_DIR}/*.h ${ASSEMBLER_DIR}/include/
cp ${VS_ASSEMBLER_DIR}/*.cpp ${ASSEMBLER_DIR}/source/

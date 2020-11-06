#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

# assembler paths
VS_ASSEMBLER_DIR=${ROOT_DIR}/VisualStudio/Assembler/Assembler
CODE_ASSEMBLER_DIR=${ROOT_DIR}/Code/Assembler

# copy assembler source files
cp ${VS_ASSEMBLER_DIR}/*.h ${CODE_ASSEMBLER_DIR}/include/
cp ${VS_ASSEMBLER_DIR}/*.cpp ${CODE_ASSEMBLER_DIR}/src/

# emulator paths
VS_EMULATOR_DIR=${ROOT_DIR}/VisualStudio/Emulator/Emulator
CODE_EMULATOR_DIR=${ROOT_DIR}/Code/Emulator

# copy emulator source files
cp ${VS_EMULATOR_DIR}/*.h ${CODE_EMULATOR_DIR}/include/
cp ${VS_EMULATOR_DIR}/*.cpp ${CODE_EMULATOR_DIR}/src/

#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

$ROOT_DIR/scripts/make_as.sh
$ROOT_DIR/scripts/make_emu.sh

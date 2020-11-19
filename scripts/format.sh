#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

$ROOT_DIR/scripts/format_as.sh
$ROOT_DIR/scripts/format_emu.sh

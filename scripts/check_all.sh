#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)

pushd $ROOT_DIR > /dev/null

./scripts/format.sh
./scripts/unit_test_as.sh
./scripts/run_behave_tests.sh -o /dev/null

popd > /dev/null

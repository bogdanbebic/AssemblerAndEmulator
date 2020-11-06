#!/bin/bash

ROOT_DIR=$(realpath `git rev-parse --git-dir`/..)
TESTS_DIR=${ROOT_DIR}/tests
FEATURES_DIR=${TESTS_DIR}/features
PYTHON_VENV_DIR=${ROOT_DIR}/venv

# activate python venv
source ${PYTHON_VENV_DIR}/bin/activate

# run tests
behave ${FEATURES_DIR} -k $@

# leave python venv
deactivate

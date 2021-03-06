# AssemblerAndEmulator
Implementation of a simple assembler and
emulator for a school assignment. The assembler
and emulator should run on Linux, but Windows
compatibility is somewhat implemented and should
be kept.

## Build
There are two parts of the repo:
- `assembler`
- `emulator`

Each is built by simply running `make`
in the appropriate folder.

## Documentation
There are two forms of documentation:
- `docs/pdf/` - the assembler and computer system
specifications - these documents describe the guidelines
of development (written in Serbian)
- `docs/html/` - documentation regarding the code itself - these
files are generated by running `doxygen` in the root
of the repo - it generates documentation regarding the
assembler and emulator source code

The source code should be documented using Doxygen format.
Qt format is the preffered format of the docs comments.

## Tests
There are some automated tests, but a lot of the testing
still has to be done manually. The automated tests can
be run simply from the root of the repo by calling:
``` bash
$ ./scripts/check_all.sh
```
### Dependencies
The `format` scripts require `clang-format` in the path.

The `unit_test` scripts and some `make` targets require
`BoostTest` with it's headers in the default include path.

The `run_behave_tests` script requries `python3` with libraries:
- `pexpect` 
- `behave`

The libraries can be installed by `pip`:
- `pip install pexpect`
- `pip install behave`

The script assumes a `python3` venv and these libraries in
a `venv/` folder in the root of the repo.

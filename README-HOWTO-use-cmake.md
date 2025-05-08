# HOWTO use cmake

`cmake` is the CLI of this project. The various targets allow to format the code, lint the code, generate documentation, compile and run the test runner, and generate the `compile_commands.json` to help IDE integration.

_Commands are given for a buid folder named `build`, and it is assumed that the current folder is the project root folder._

## Required

* A C++ toolchain
* [Cmake](https://cmake.org/)
* [compdb](https://github.com/Sarcasm/compdb)
* [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
* [clang-tidy-19](https://clang.llvm.org/extra/clang-tidy/)
* [doxygen](https://doxygen.nl/)
* The [Criterion unit testing framework](https://github.com/Snaipe/Criterion)

## Prepare the build folder and list the targets

Invoke :

* either `cmake -Bbuild` when the build folder does not exists.
* or `cmake -Bbuild --fresh` to rebuild the content of an already existing build folder.

_After this, one can check all the available targets with `cmake --build build -- help`_

## Pretty-print the source

Invoke :

* either `cmake --build build -- check-prettier` to see what will be reformatted.
* or `cmake --build build --clean-first -- prettier` to perform the reformat.

## Lint the source

Invoke `cmake --build build -- lint` to perform the linting.

## Generate the `compile_commands.json` file

Invoke `cmake --build build -- refresh-compile-db` to perform the linting.

## Generate the documentation

Invoke `cmake --build build -- refresh-compile-db` to perform the linting.

## Run the test suite

Invoke :

* either `cmake --build build -- verify` to build incrementally.
* or `cmake --build build --clean-first -- verify` to trigger a full rebuild.

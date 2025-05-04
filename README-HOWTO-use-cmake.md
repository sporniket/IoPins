# HOWTO use cmake

## Required

* [Cmake](https://cmake.org/)
* A C++ toolchain
* The [Criterion unit testing framework](https://github.com/Snaipe/Criterion)

## Prepare the build folder

_Commands are given for a buid folder named `build`_

* either `cmake -Bbuild` when the build folder does not exists.
* or `cmake -Bbuild --fresh` to rebuild the content of an already existing build folder.

_After this, one can check all the available targets with `cmake --build build -- help`_

## Pretty-print the source after editing

_Requires a build folder ; commands are given for a buid folder named `build`_

* either `cmake --build build -- check-prettier` to see what will be reformatted.
* or `cmake --build build --clean-first -- prettier` to perform the reformat.

## Run the test suite

_Requires a build folder ; commands are given for a buid folder named `build`_

* either `cmake --build build -- verify` to build incrementally.
* or `cmake --build build --clean-first -- verify` to trigger a full rebuild.

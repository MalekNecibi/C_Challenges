# C Language Challenges

The C\_Challenges suite is a set of assessments to evaluate and review ones knowledge in the C language.

They were devised by University of Missouri Professor Jim Ries to
encourage developers to dive deeper into understanding C development.

## Installation

CMake is used to build the tests for the challenge. To run all available tests, first clone the repository and run CMake (minimum version 3.5) to build. Then run the tests using CTest.

```bash
mkdir build  # create and enter build directory
cd build
cmake ..     # build environment
make
ctest -V     # run all tests
```

A helper script `tester.sh` is also available to simplify the testing process on UNIX systems.
To build and run all tests, simply run:
```bash
./tester.sh
```
or to test a specific challenge:
```bash
cd bitmap
../tester.sh
```
#### Note: Tester script will overwrite the contents of the ./build directory to ensure tests are .

## Dependencies
CMake >3.5, Make

Some challenges are inherently POSIX-specific and will not run correctly on non-POSIX machines or architectures. This is an instructional feature of the challenges, and serves as a reminder of non-conformity across different version of C.

## Testing Specific Challenges

If you would prefer to test challenges individually, the same build procedure can be run from within a challenge directory. The tester script can also be called from a child directory:
```bash
cd arrays
../tester.sh
```

## Challenges
- arrays
- strings
- system programming
- bits
- allocation
- debug
- error\_handling
- structures

##

Original challenges and tests courtesy of Professor Ries.

All C implementations, the `tester.sh` script, and CTest integration are my own work. If you would like to try any challenge for yourself, feel free to visit the `src/` sub-directories and replace my completed \*.c implementations with the provided \*.bkp.c starter code:
```bash
cp -i bitmap/src/bitmap.bkp.c bitmap/src/bitmap.c
```

**-Malek Necibi**

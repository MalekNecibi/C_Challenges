# Script for final testing within a brand-new environment
# Malek Necibi

# INSTRUCTIONS:
# enter one of the challenge directories        (`cd arrays`)
# run this script                               (`../tester.sh`)

CHALLENGE=${PWD##*/}    # current directory
TESTER_FILE="${CHALLENGE}_tester"

if [ ! -f "./CMakeLists.txt" ] ; then
    echo "ERROR: Couldn't locate CMake build instructions (CMakeLists.txt)"
    exit 1
fi

if [ -d "./build" ]; then
    echo
    echo Removing old build directory
    rm -r build/
fi

echo Creating build directory
mkdir -p build
cd build
INSIDE_BUILD_DIR=$?
if [ $INSIDE_BUILD_DIR -ne 0 ] ; then
    echo "ERROR: failed to create/enter working directory 'build'"
    exit 1
fi

echo
echo Building Test Environment...

cmake ..
echo
echo CMake Complete
echo CTest Environment Complete

echo
echo Building Make and GTest
make
echo
echo Make Complete


echo
echo Running Tests...
#./$TESTER_FILE
ctest -V --output-on-failure
TESTER_RESPONSE_CODE=$?

echo
if [ $TESTER_RESPONSE_CODE -ne 0 ] ; then
    echo "Testing Ended Unexpectedly (WARNING)"
else
    echo Testing Complete
fi

cd ..

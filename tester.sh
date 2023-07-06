# Script for final testing within a brand-new environment
# Malek Necibi

# INSTRUCTIONS:
# enter one of the challenge directories        (`cd arrays`)
# run this script                               (`../tester.sh`)


if [ ! -f "./CMakeLists.txt" ] ; then
    echo "ERROR: Couldn't locate CMake build instructions (CMakeLists.txt)"
    exit 1
fi

PATH_TO_DELETE=$(pwd)/build
if [ -d "${PATH_TO_DELETE}" ]; then
    echo
    
    # only delete after confirmation
    read -p "Overwrite directory '${PATH_TO_DELETE}'? [y/N] " yn

    if [ "${yn}" != 'y' ] ; then
        echo "Aborting..."
        exit 1
    fi
    
    echo Removing old build directory
    rm -rf "${PATH_TO_DELETE}"
    echo
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
ctest -V --output-on-failure
TESTER_RESPONSE_CODE=$?

echo
if [ $TESTER_RESPONSE_CODE -ne 0 ] ; then
    echo "Testing Ended Unexpectedly (WARNING)"
else
    echo Testing Complete!
fi

cd ..

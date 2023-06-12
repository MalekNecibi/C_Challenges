# Script for final testing within a brand-new environment
# Malek Necibi


CHALLENGE=${PWD##*/}    # current directory
TEST_FILE="${CHALLENGE}_test"

if [ ! -f "./CMakeLists.txt" ] ; then
    echo "ERROR: Couldn't locate CMake build instructions (CMakeLists.txt)"
    exit 1
fi

echo
echo Creating Build Directory
mkdir -p build
cd build
if [ ! $? -eq 0 ] ; then
    echo "ERROR: failed to create/enter working directory 'build'"
    exit 1
fi

echo
echo Removing old Build Environment
rm -r ./*

echo
echo Building Test Environment...
sleep 1
cmake ..
make

echo
echo Running Tests...
sleep 1
./$TEST_FILE

echo
echo Testing Complete!
cd ..

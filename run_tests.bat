cd tests
rm -rf build 
mkdir build
cd build
cmake ..
cmake --build .
Debug\playground_test.exe -r junit
cd ..
cd ..
exit
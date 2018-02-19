cd tests
rm -rf build 
mkdir build
cd build
cmake ..
cmake --build .
./chops_test -r junit
cd ..
rm -rf build 
cd ..
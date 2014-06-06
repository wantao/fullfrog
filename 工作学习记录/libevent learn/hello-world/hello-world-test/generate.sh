cd build
make clean
rm -rf *
cmake ..
make VERBOSE=1
cp src/hello-test.out ../
#cmake -DCMAKE_INSTALL_PREFIX=/usr ..
#make
#make install

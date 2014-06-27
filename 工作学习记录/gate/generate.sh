cd build
make clean
rm -rf *
cmake ..
make VERBOSE=1
#cmake -DCMAKE_INSTALL_PREFIX=/usr ..
#make
#make install

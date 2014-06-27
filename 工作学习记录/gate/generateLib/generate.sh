cd build
rm -rf *
cmake ..
make
cmake -DCMAKE_INSTALL_PREFIX=/home/wantao/Desktop/gate/ ..
make
make install

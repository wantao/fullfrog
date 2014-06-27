cd build
rm -rf *
cmake ..
make
cmake -DCMAKE_INSTALL_PREFIX=/usr/local ..
make
make install

yum install -y wget
cd /tmp
wget http://www.cmake.org/files/v2.8/cmake-2.8.10.2.tar.gz
tar -zxvf cmake-2.8.10.2.tar.gz
cd cmake-2.8.10.2
mkdir -p /usr/local/cmake
./bootstrap --prefix=/usr/local/cmake
gmake
gmake
cp  bin/cmake  /usr/bin/
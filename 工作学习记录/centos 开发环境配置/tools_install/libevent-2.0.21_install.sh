cd /tmp
wget http://cloud.github.com/downloads/libevent/libevent/libevent-2.0.21-stable.tar.gz
tar -zxvf libevent-2.0.21-stable.tar.gz
cd libevent-2.0.21-stable
./configure --prefix=/usr/lib
make
make install
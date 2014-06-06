chmod +x gcc_g++_install.sh cmake_install.sh libevent-2.0.21_install.sh
./gcc_g++_install.sh
./cmake_install.sh
./libevent-2.0.21_install.sh
echo "/usr/lib/lib/" >> /etc/ld.so.conf
ldconfig
yum install gdb -y
service iptables stop
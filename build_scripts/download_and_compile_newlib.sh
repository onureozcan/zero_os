#!/usr/bin/env bash

# This file is intended to run in docker container not in host environment
NEWLIB_VERSION="2.4.0"
NEWLIB_DIR="/newlib/newlib-${NEWLIB_VERSION}"
#download newlib
echo "downloading newlib"
if [[ -f "/newlib/newlib-${NEWLIB_VERSION}.tar.gz" ]]; then
        echo "newlib tar exist, skipping"
   else
        wget ftp://sourceware.org/pub/newlib/newlib-${NEWLIB_VERSION}.tar.gz -O /newlib/newlib-${NEWLIB_VERSION}.tar.gz
        cd /newlib && tar -xzf newlib-${NEWLIB_VERSION}.tar.gz
fi

echo "building newlib for zero_os"

echo "copying config.sub"
cp /project/src/newlib/config.sub $NEWLIB_DIR/config.sub
echo "copying configure.host"
cp /project/src/newlib/configure.host $NEWLIB_DIR/newlib/configure.host
echo "copying configure.in"
cp /project/src/newlib/libc/sys/configure.in $NEWLIB_DIR/newlib/libc/sys/configure.in
(cd $NEWLIB_DIR/newlib/libc/sys/ && autoconf)
echo "copying zero_os"
cp -r /project/src/newlib/libc/sys/zero_os $NEWLIB_DIR/newlib/libc/sys/
(cd $NEWLIB_DIR/newlib/libc/sys/ && autoconf)
(cd $NEWLIB_DIR/newlib/libc/sys/zero_os && autoreconf)

# followed the tutorial at: https://wiki.osdev.org/Porting_Newlib
# make symlinks (a bad hack) to make newlib work
cd /usr/local/cross/bin/ # this is where the bootstrapped generic cross compiler toolchain (i686-elf-xxx) is installed in,
                # change this based on your development environment.
ln i686-elf-ar i686-zero_os-ar
ln i686-elf-as i686-zero_os-as
ln i686-elf-gcc i686-zero_os-gcc
ln i686-elf-gcc i686-zero_os-cc
ln i686-elf-ranlib i686-zero_os-ranlib

cd $NEWLIB_DIR/..
mkdir build-newlib
cd build-newlib
../newlib-${NEWLIB_VERSION}/configure --prefix=/usr --target=i686-zero_os
make all
make DESTDIR=/newlib install



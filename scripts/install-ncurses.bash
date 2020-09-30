#!/bin/bash

# Install ncurses version 6.2

current_directory=$(pwd)

ncurses=$(pwd)/libs/ncurses
include=$(pwd)/libs/ncurses/include
binaries=$(pwd)/libs/ncurses/binaries
mkdir -p $ncurses

mkdir .tmp
cd .tmp

ncurses_archive=ncurses.tar.gz
ncurses_dl_url=https://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz
curl -o $ncurses_archive -L $ncurses_dl_url
tar -xf $ncurses_archive

cd ncurses-6.2

./configure --prefix=$ncurses --libdir=$binaries --enable-widec --without-ada --without-manpages --without-progs --without-tack --without-tests --with-normal
make
make install

cd ../..
rm -rf .tmp

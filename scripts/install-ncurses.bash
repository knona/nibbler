#!/bin/bash

# Install ncurses version 6.2

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/ncurses
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

ncurses=$(pwd)/libs/ncurses
include=$(pwd)/libs/ncurses/include
bin=$(pwd)/libs/ncurses/bin
mkdir -p $ncurses

cache=$(pwd)/.cache

mkdir -p $cache

ncurses_archive=$cache/ncurses.tar.gz
ncurses_dl_url=https://ftp.gnu.org/gnu/ncurses/ncurses-6.2.tar.gz

if [ ! -f "$ncurses_archive" ]
then
	curl -o $ncurses_archive -L $ncurses_dl_url
fi

mkdir .tmp
cd .tmp

tar -xf $ncurses_archive

cd ncurses-6.2

./configure --prefix=$ncurses --libdir=$bin --enable-widec --without-ada --without-manpages --without-tests --with-normal
make
make install

cd ../..
rm -rf .tmp

trap - EXIT

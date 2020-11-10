#!/bin/bash

# Install sdl2 version 2.0.12

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/sdl
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

sdl=$current_directory/libs/sdl/
mkdir -p $sdl

cache=$current_directory/.cache

mkdir -p $cache

sdl_archive=$cache/sdl.zip
sdl_dl_url=https://www.libsdl.org/release/SDL2-2.0.12.zip

if [ ! -f "$sdl_archive" ]
then
	curl -o $sdl_archive -L $sdl_dl_url
fi

mkdir .tmp
cd .tmp

unzip -qq $sdl_archive

cd SDL2-2.0.12

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$sdl -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DSDL_SHARED=n -DSDL_STATIC=y -DSDL_STATIC_PIC=y -DSDL_AUDIO=n -DSDL_RENDER=n -DSDL_TEST=n -DSDL_TIMERS=n -DSDL_POWER=n-DSDL_=n ..
make install

cd ../../..
rm -rf .tmp

trap - EXIT

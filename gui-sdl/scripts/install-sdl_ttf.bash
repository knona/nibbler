#!/bin/bash

# Install sdl2_ttf version 2.0.12

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/sdl
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

sdl=$current_directory/libs/sdl/

cache=$current_directory/.cache

mkdir -p $cache

sdl_ttf_archive=$cache/sdl_ttf.zip
sdl_ttf_dl_url=https://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.15.zip

if [ ! -f "$sdl_ttf_archive" ]
then
	curl -o $sdl_ttf_archive -L $sdl_ttf_dl_url
fi

mkdir .tmp
cd .tmp

unzip -qq $sdl_ttf_archive

cd SDL2_ttf-2.0.15

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

# ./configure --prefix=$sdl --enable-shared=n --disable-sdltest --with-pic=y

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$sdl -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_POSITION_INDEPENDENT_CODE=y ..
make install || true

cd ../../..
rm -rf .tmp

trap - EXIT

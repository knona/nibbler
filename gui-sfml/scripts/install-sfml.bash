#!/bin/bash

# Install sfml version 2.5.1

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/sfml
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

sfml=$current_directory/libs/sfml/
mkdir -p $sfml

cache=$current_directory/.cache

mkdir -p $cache

sfml_archive=$cache/sfml.zip
sfml_dl_url=https://www.sfml-dev.org/files/SFML-2.5.1-sources.zip

if [ ! -f "$sfml_archive" ]
then
	curl -o $sfml_archive -L $sfml_dl_url
fi

mkdir .tmp
cd .tmp

unzip -qq $sfml_archive

cd SFML-2.5.1

export CC=/usr/bin/clang
export CXX=/usr/bin/clang++

mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=$sfml -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_POSITION_INDEPENDENT_CODE=y -DBUILD_SHARED_LIBS=n -DSFML_PKGCONFIG_INSTALL_PREFIX=n -DSFML_BUILD_AUDIO=n -DSFML_BUILD_NETWORK=n ..
make install 

cd ../../..
rm -rf .tmp

trap - EXIT

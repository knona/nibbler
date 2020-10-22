#!/bin/bash

# Install boost version 1.74.0

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/boost
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

include=libs/boost/include
bin=libs/boost/bin
mkdir -p $include
mkdir -p $bin

cache=$(pwd)/.cache

mkdir -p $cache

boost_archive=$cache/boost.tar.gz
boost_dl_url=https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz

if [ ! -f "$boost_archive" ]
then
	curl -o $boost_archive -L $boost_dl_url
fi

mkdir .tmp
cd .tmp

tar -xf $boost_archive

cd boost_1_74_0

./bootstrap.sh --with-toolset=clang --libdir="$current_directory/$bin" --includedir="$current_directory/$include"
./b2 install --no-cmake-config --with-program_options toolset=clang link=static runtime-link=static

cd ../..
rm -rf .tmp

trap - EXIT

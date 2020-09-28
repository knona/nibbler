#!/bin/bash

# Install boost version 1.74.0

current_directory=$(pwd)

headers=boost/headers
binaries=boost/binaries
mkdir -p $headers
mkdir -p $binaries

mkdir .tmp
cd .tmp

boost_archive=boost.tar.bz2
boost_dl_url=https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.bz2
curl -o $boost_archive -L $boost_dl_url
tar -xf $boost_archive

cd boost_1_74_0

./bootstrap.sh --with-toolset=clang --libdir="$current_directory/$binaries" --includedir="$current_directory/$headers"
./b2 install --no-cmake-config --with-program_options toolset=clang link=static runtime-link=static

cd ../..
rm -rf .tmp

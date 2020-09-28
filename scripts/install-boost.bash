#!/bin/bash

# Install boost version 1.74.0

current_directory=$(pwd)

includes=libs/boost/includes
binaries=libs/boost/binaries
mkdir -p $includes
mkdir -p $binaries

mkdir .tmp
cd .tmp

boost_archive=boost.tar.gz
boost_dl_url=https://dl.bintray.com/boostorg/release/1.74.0/source/boost_1_74_0.tar.gz
curl -o $boost_archive -L $boost_dl_url
tar -xf $boost_archive

cd boost_1_74_0

./bootstrap.sh --with-toolset=clang --libdir="$current_directory/$binaries" --includedir="$current_directory/$includes"
./b2 install --no-cmake-config --with-program_options toolset=clang link=static runtime-link=static

cd ../..
rm -rf .tmp

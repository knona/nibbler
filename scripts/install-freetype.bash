#!/bin/bash

# Install freetype version 1.74.0

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/freetype
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

freetype=$current_directory/libs/freetype
cache=$current_directory/.cache

mkdir -p $freetype
mkdir -p $cache

freetype_archive=$cache/freetype.tar.gz
freetype_dl_url=https://download.savannah.gnu.org/releases/freetype/freetype-2.10.4.tar.gz

if [ ! -f "$freetype_archive" ]
then
	curl -o $freetype_archive -L $freetype_dl_url
fi

mkdir .tmp
cd .tmp

tar -xf $freetype_archive

cd freetype-2.10.4

./configure --prefix=$freetype --enable-static=no
make install

cd ../..
rm -rf .tmp

trap - EXIT

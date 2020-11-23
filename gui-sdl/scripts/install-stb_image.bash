#!/bin/bash

# Install stb_image @latest from master

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/stb_image
}

trap clean_before_exit EXIT

current_directory=$(pwd)

include=libs/stb_image/include
src=libs/stb_image/src
mkdir -p $include
mkdir -p $src

cache=$(pwd)/.cache

mkdir -p $cache
file=stb_image.h

if [ ! -f "$cache/$file" ]
then
	curl -o $cache/$file https://raw.githubusercontent.com/nothings/stb/e140649ccf40818781b7e408f6228a486f6d254b/stb_image.h
fi
	
cp $cache/$file $include/


echo "#define STB_IMAGE_IMPLEMENTATION" > $src/stb_image.c
echo "#include \"stb_image.h\"" >> $src/stb_image.c

trap - EXIT

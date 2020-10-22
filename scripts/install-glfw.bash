#!/bin/bash

# Install glfw version 3.3.2

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/glfw
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)
include=libs/glfw/include
bin=libs/glfw/bin
mkdir -p $include
mkdir -p $bin

cache=$(pwd)/.cache

mkdir -p $cache

glfw_archive=$cache/glfw.zip
glfw_dl_url=https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip

if [ ! -f "$glfw_archive" ]
then
	curl -o $glfw_archive -L $glfw_dl_url
fi

mkdir .tmp
cd .tmp

unzip -qq $glfw_archive

cd glfw-3.3.2
cmake .
make

mv src/libglfw3.a $current_directory/$bin
mv include/* $current_directory/$include

cd ../..
rm -rf .tmp

trap - EXIT

#!/bin/bash

# Install glfw version 3.3.2

current_directory=$(pwd)

include=libs/glfw/include
binaries=libs/glfw/binaries
mkdir -p $include
mkdir -p $binaries

mkdir .tmp
cd .tmp

glfw_archive=glfw.zip
glfw_dl_url=https://github.com/glfw/glfw/releases/download/3.3.2/glfw-3.3.2.zip
curl -o $glfw_archive -L $glfw_dl_url
unzip $glfw_archive

cd glfw-3.3.2
cmake .
make

mv src/libglfw3.a $current_directory/$binaries
mv include/* $current_directory/$include

cd ../..
rm -rf .tmp

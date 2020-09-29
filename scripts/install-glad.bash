#!/bin/bash

# Install glad

current_directory=$(pwd)

glad=libs/glad
mkdir -p $glad

mkdir .tmp
cd .tmp

glad_archive=glad.zip
glad_dl_url=https://github.com/Dav1dde/glad/archive/master.zip
curl -o $glad_archive -L $glad_dl_url
unzip $glad_archive

cd glad-master
python3 -m glad --generator c --no-loader --out-path $current_directory/$glad

cd ../..
rm -rf .tmp

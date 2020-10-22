#!/bin/bash

# Install glad

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/glad
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)
glad=libs/glad
mkdir -p $glad

cache=$(pwd)/.cache

mkdir -p $cache

glad_archive=$cache/glad.zip
glad_dl_url=https://github.com/Dav1dde/glad/archive/master.zip

if [ ! -f "$glad_archive" ]
then
	curl -o $glad_archive -L $glad_dl_url
fi

mkdir .tmp
cd .tmp

unzip -qq $glad_archive

cd glad-master
python3 -m glad --generator c --no-loader --out-path $current_directory/$glad

cd ../..
rm -rf .tmp

trap - EXIT

#!/bin/bash

# Install glm version 0.9.9.8

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/glm
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

glm=$current_directory/libs/glm/
mkdir -p $glm

cache=$current_directory/.cache

mkdir -p $cache

glm_archive=$cache/glm.zip
glm_dl_url=https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip

if [ ! -f "$glm_archive" ]
then
	curl -o $glm_archive -L $glm_dl_url
fi

mkdir .tmp
cd .tmp

unzip -qq $glm_archive

cd glm

cp -r glm $glm/include

cd ../..
rm -rf .tmp

trap - EXIT

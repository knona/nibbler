#!/bin/bash

# Install stb_image @latest from master

current_directory=$(pwd)

include=libs/stb_image/include
src=libs/stb_image/src
mkdir -p $include
mkdir -p $src

curl -o $include/stb_image.h https://raw.githubusercontent.com/nothings/stb/e140649ccf40818781b7e408f6228a486f6d254b/stb_image.h
echo "#define STB_IMAGE_IMPLEMENTATION" > $src/stb_image.c
echo "#include \"stb_image.h\"" >> $src/stb_image.c

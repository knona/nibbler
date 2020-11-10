#!/bin/bash

# Install allegro version 5.2.6.0

set -e

function clean_before_exit {
	rm -rf $current_directory/libs/allegro
	rm -rf $current_directory/.tmp
}

trap clean_before_exit EXIT

current_directory=$(pwd)

allegro=$current_directory/libs/allegro/
mkdir -p $allegro

cache=$current_directory/.cache

mkdir -p $cache

allegro_archive=$cache/allegro.zip
allegro_dl_url=https://github.com/liballeg/allegro5/releases/download/5.2.6.0/allegro-5.2.6.0.zip

if [ ! -f "$allegro_archive" ]
then
	curl -o $allegro_archive -L $allegro_dl_url
fi

mkdir .tmp
cd .tmp

unzip -qq $allegro_archive

cd allegro

mkdir build
cd build
cmake \
-DCMAKE_INSTALL_PREFIX=$allegro \
-DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ \
-DCMAKE_POSITION_INDEPENDENT_CODE=y \
-DSHARED=n \
-DWANT_TESTS=n \
-DWANT_ALLOW_SSE=y \
-DWANT_ALSA=n \
-DWANT_AQUEUE=n \
-DWANT_AUDIO=n \
-DWANT_COLOR=y \
-DWANT_CURL_EXAMPLE=n \
-DWANT_D3D=y \
-DWANT_D3D9EX=n \
-DWANT_DEMO=n \
-DWANT_DLL_TLS=n \
-DWANT_DOCS=n \
-DWANT_DOCS_HTML=n \
-DWANT_DOCS_INFO=n \
-DWANT_DOCS_MAN=n \
-DWANT_DOCS_PDF=n \
-DWANT_DOCS_PDF_PAPER=n \
-DWANT_DSOUND=n \
-DWANT_EMBED=n \
-DWANT_EXAMPLES=y \
-DWANT_FLAC=n \
-DWANT_FONT=y \
-DWANT_FRAMEWORKS=n \
-DWANT_GLES3=n \
-DWANT_IMAGE=y \
-DWANT_IMAGE_FREEIMAGE=n \
-DWANT_IMAGE_JPG=n \
-DWANT_IMAGE_PNG=n \
-DWANT_IMAGE_WEBP=n \
-DWANT_LUAJIT=n \
-DWANT_MEMFILE=n \
-DWANT_MODAUDIO=n \
-DWANT_MONOLITH=n \
-DWANT_MP3=n \
-DWANT_MUDFLAP=n \
-DWANT_NATIVE_DIALOG=y \
-DWANT_NATIVE_IMAGE_LOADER=y \
-DWANT_OGG_VIDEO=n \
-DWANT_OPENAL=y \
-DWANT_OPENGL=y \
-DWANT_OPENSL=y \
-DWANT_OPUS=n \
-DWANT_OSS=n \
-DWANT_PHYSFS=n \
-DWANT_POPUP_EXAMPLES=y \
-DWANT_PRIMITIVES=y \
-DWANT_PULSEAUDIO=n \
-DWANT_PYTHON_WRAPPER=n \
-DWANT_RELEASE_LOGGING=y \
-DWANT_SHADERS_D3D=y \
-DWANT_SHADERS_GL=y \
-DWANT_STATIC_RUNTIME=n \
-DWANT_TESTS=n \
-DWANT_TREMOR=n \
-DWANT_TTF=y \
-DWANT_VIDEO=n \
-DWANT_VORBIS=n \
..

make install

cd ../../..
rm -rf .tmp

trap - EXIT

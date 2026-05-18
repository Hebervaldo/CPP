#!/bin/bash

FILE="bcm2835-1.73"
FILE_COMPACTADO="$FILE.tar.gz"

if [ ! -f "$FILE_COMPACTADO" ]; then
	wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.73.tar.gz
fi

tar zxvf "$FILE_COMPACTADO"
cd "$FILE"
./configure
make
make check
make install
cd ..

#!/bin/bash 
#
cd $HOME
wget https://www.imagemagick.org/download/ImageMagick.tar.gz
tar xf ImageMagick.tar.gz
cd ImageMagick-7*
./configure
make
sudo make install
sudo ldconfig /usr/local/lib

#install or prepare any other environment below
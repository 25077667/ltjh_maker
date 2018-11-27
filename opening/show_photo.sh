#!/bin/bash 
#

#intialize the photo file to be standardization
for f in *.gif; do mv -- "$f" "${f%.jpg}.jpg"; done
for f in *.jpeg; do mv -- "$f" "${f%.jpg}.jpg"; done

# you can change below "120x120" to the size you want
i=0
for image in *.jpg; do sudo magick '*.jpg' -resize 120x120 ${image}${i}.png; i=$((${i}+1)); done

#use python to output image on LED martix
python output.py
#!/bin/bash

cd $1
X=$2
echo 'converting #' $X
pnmtopng $X.ppm > $X.png
rm $X.ppm

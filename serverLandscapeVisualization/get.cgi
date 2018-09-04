#!/bin/sh
printf "Content-type: text/html\n\n"
echo $(wget $1 -q -O -)

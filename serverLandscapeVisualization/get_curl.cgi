#!/bin/sh
printf "Content-type: text/html\n\n"
echo $(curl $1 -s)

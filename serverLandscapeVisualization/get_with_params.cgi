#!/bin/sh
printf "Pragma-directive: no-cache\n";
printf "Cache-directive: no-cache\n";
printf "Cache-control: no-cache\n";
printf "Pragma: no-cache\n";
printf "Expires: 0\n";
printf "Content-type: text/html\n\n"
url=`echo "$1"`
url=`echo $url | sed -e 's/\\\//g'`
echo $(wget ${url} -q -O -)
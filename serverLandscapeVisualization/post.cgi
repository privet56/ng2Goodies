#!/bin/sh
printf "Pragma-directive: no-cache\n";
printf "Cache-directive: no-cache\n";
printf "Cache-control: no-cache\n";
printf "Pragma: no-cache\n";
printf "Expires: 0\n";
printf "Content-type: text/html\n\n"
tfn=`echo $RANDOM`
url=`echo "$1"`
#xml=`echo "$2"`
xml=$(</dev/stdin)
url=`echo $url | sed -e 's/\\\//g'`
printf "${xml}" > /tmp/${tfn}
echo `curl -H "Accept: text/xml" -H "Content-Type:text/xml" -X POST ${url} -d @/tmp/${tfn} '${xml}'`
rm /tmp/${tfn}

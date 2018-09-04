#!/bin/sh
printf "Pragma-directive: no-cache\n";
printf "Cache-directive: no-cache\n";
printf "Cache-control: no-cache\n";
printf "Pragma: no-cache\n";
printf "Expires: 0\n";
printf "Content-type: text/plain\n\n"
params=`echo "$1"`
if [ $params == "getstatus" ]; then
	printf "{ \"8080\":"
	if [ -f "/app/apache2-8080/htdocs/maintenance/site-maintenance-page/maintenance.html" ]; then
		printf "1,"
	else
		printf "0,"
	fi
	printf " \"80\":"
	if [ -f "/app/www/apache2/htdocs/maintenance/site-maintenance-page/maintenance.html" ]; then
		printf "1"
	else
		printf "0"
	fi
	printf " }"
elif [ $params == "deactivatemaintpage80" ]; then
	mv "/app/www/apache2/htdocs/maintenance/site-maintenance-page/503_error.html" "/app/www/apache2/htdocs/maintenance/site-maintenance-page/_503_error.html" 2>&1
	echo $?
else
	echo "unknown param found param:'${params}'"
fi

#echo $(perl -e 'use Cwd;print getcwd')
#echo `perl -e "use Cwd;print 'params = ($params)'"`

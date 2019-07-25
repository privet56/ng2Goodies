# additional docker param:  -e "MATOMO_DATABASE_ADAPTER=PDO\MYSQL"\ or MATOMO_DATABASE_ADAPTER=mysql\
# check if DB reachable:    telnet 10.1.5.21 3306
# used docker image:        https://hub.docker.com/_/matomo
# prerequisite:             subdir 'matomo' in pwd
# start this script with:   sudo ./virtualmatomo.sh
# settings in the DB:       GRANT ALL PRIVILEGES ON *.* TO 'matomowebanalytics'@'%' WITH GRANT OPTION;
#                           FLUSH PRIVILEGES;
#                           # with no 'localhost' entry in the user management list of mariadb

docker run --rm -it\
    -v `pwd`/matomo:/var/www/html\
    --name matomoserver\
    -e "MATOMO_DATABASE_HOST=10.1.5.21"\
    -e "MATOMO_DATABASE_TABLES_PREFIX=matomo_"\
    -e "MATOMO_DATABASE_USERNAME=matomowebanalytics"\
    -e "MATOMO_DATABASE_PASSWORD=my"\
    -e "MATOMO_DATABASE_DBNAME=matomowebanalytics"\
    -p 8080:80\
    -d matomo

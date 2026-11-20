#!/usr/bin/env bash
set -e
if ! command -v mysqld >/dev/null || ! command -v mysql_config >/dev/null || ! command -v g++ >/dev/null; then
    sudo apt-get update
    sudo DEBIAN_FRONTEND=noninteractive apt-get install -y mysql-server mysql-client default-libmysqlclient-dev g++
fi
sudo service mysql start
sudo mysql <<'SQL'
CREATE DATABASE IF NOT EXISTS cvicenie9;
CREATE USER IF NOT EXISTS 'student'@'localhost' IDENTIFIED BY '1234';
GRANT ALL PRIVILEGES ON cvicenie9.* TO 'student'@'localhost';
SQL
mysql --protocol=TCP -h 127.0.0.1 -u student -p1234 cvicenie9 < databaza.sql
g++ -std=c++11 testdb.cpp -o testdb $(mysql_config --cflags --libs)
./testdb

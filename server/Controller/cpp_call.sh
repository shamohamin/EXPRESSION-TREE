#!/bin/bash

files="./cpp_files/*.out"

if ! [ -f files ]
then
    g++ ./cpp_files/main.cpp -lglut -lGL -pthread -o ./cpp_files/main.out
fi
echo $1

res=`./cpp_files/main.out $1`

import -window root ./src/img/graph.jpg

# echo "$1" ;
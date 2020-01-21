#!/bin/bash

files="./cpp_files/*.out"

if ! [ -f files ]
then
    g++ ./cpp_files/main.cpp -lglut -lGL -pthread -o ./cpp_files/main.out
fi

./cpp_files/main.out

import -window root ./src/img/graph.jpg

echo "$1" ;
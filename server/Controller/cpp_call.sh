#!/bin/bash
echo "$1"
files="./cpp_files/*.out"
# files="../../cpp_files/*.out"
if ! [ -f files ]
then
    g++ ./cpp_files/main.cpp -lglut -lGL -pthread -o ./cpp_files/main.out
    # g++ ../../cpp_files/main.cpp -lglut -lGL -pthread -o ../../cpp_files/main1.out
fi
# echo "sadsadkjasdb"
# echo $1

res=`./cpp_files/main.out $1`
# sleep 1
# res=`../../cpp_files/main1.out $1`
# echo $res

# import -window root ./src/img/graph.jpg

# echo "$1" ;
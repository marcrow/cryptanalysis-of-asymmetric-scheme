#!/bin/bash

if [ $# -eq 0 ]
  then
    echo "	Error : Please give a name for the result file"
    echo "	exemple : ./cleanFile.sh data200.txt -d"
    echo "           Option -d erase the previous version of data200.txt" 
    exit
fi
arg="default"
arg2=$2
if [ $1 = "-d" ]; then
	arg=$2
	arg2=$1
else
	arg=$1
fi

if [ $arg2 = "-d" ]; then
	cat ../result/nbFactor | sed "s/,//" | sed "s/(//"  | sed "s/,//" | sed "s/)//" > $arg
else
	cat ../result/nbFactor | sed "s/,//" | sed "s/(//"  | sed "s/,//" | sed "s/)//" >> $arg
fi
rm ../result/nbFactor

echo "it's done"
echo "print the file ? y/n"
ans="n"
read ans
if [ $ans = "y" ]; then
	echo "B ecart nbP-smooth"
	cat $arg
fi

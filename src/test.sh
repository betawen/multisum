#!/bin/bash
echo "Testing......"
echo "Thread Test===>"
path=$1
files=$(ls $path)
for filename in $files
do
    echo ---------
    echo $filename
    echo ---------
    ./thread/multisum ./$path/$filename
    echo "\n"
done
echo "Process Testing===>"
for filename in $files
do
    echo ---------
    echo $filename
    echo ---------
    ./process/multisum ./$path/$filename
    echo "\n"
done
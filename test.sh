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
    ./thread/a.out ./$path/$filename
    echo "\n"
done
echo "Process Testing===>"
for filename in $files
do
    echo ---------
    echo $filename
    echo ---------
    ./process/a.out ./$path/$filename
    echo "\n"
done

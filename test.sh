#!/bin/bash
echo "Testing......"
echo "Thread Test===>"
path=$1
files=$(ls $path)
for filename in $files
do
    echo ---------
    echo $filename
    ./thread/a.out ./$path/$filename
    echo ---------
    echo "\n"
done
echo "Process Testing===>"
for filename in $files
do
    echo ---------
    echo $filename
    ./process/a.out ./$path/$filename
    echo ---------
    echo "\n"
done

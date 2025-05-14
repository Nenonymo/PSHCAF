#!/bin/bash

s=$1

for i in {0..9}; do
    echo "Running $i"
    ./bin/benchmark tasks/"$i".txt 7 "$s" 010101 > results/"$s"_"$i".txt
done

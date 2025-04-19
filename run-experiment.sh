#!/bin/bash

for i in {0..8}; do
    echo "Running $i"
    ./bin/benchmark tasks/"$i".txt 7 000101 > results/"$i".txt
done
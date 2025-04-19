#!/bin/bash

for i in {0..10}; do
    echo "Running $i"
    ./bin/benchmark tasks/"$i".txt 6 000101 > results/"$i".txt
done
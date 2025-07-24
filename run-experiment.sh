#!/bin/bash

for e in {0..6}; do
    for i in {0..9}; do
        echo "Running $i of $e"
        ./bin/benchmark tasks/"$i".txt 6 "$e" 010101 > results/"$e"_"$i".txt
    done
    sleep 1m
done

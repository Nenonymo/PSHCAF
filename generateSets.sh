#!/bin/bash

arg=("0.0" "0.010" "0.018" "0.031" "0.056" "0.100" "0.180" "0.310" "0.560" "1.000")

for i in "${!arg[@]}"; do
    variance="${arg[$i]}"
    echo "Running gen set with variance $variance and seed $i"
    ./bin/taskGenerator 500 "$i" "$variance" 100 > tasks/"$i".txt
done
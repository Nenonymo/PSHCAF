#!/bin/bash

arg=("0.0" "0.01" "0.018" "0.031" "0.056" "0.1" "0.18" "0.32" "0.56" "0.8" "1.0")

for i in "${!arg[@]}"; do
    variance="${arg[$i]}"
    echo "Running gen set with variance $variance and seed $i"
    ./bin/taskGenerator 600 "$i" "$variance" > tasks/"$i".txt
done
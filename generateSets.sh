#!/bin/bash

arg=("0.0000" "0.0010" "0.0017" "0.0030" "0.0044" "0.0065" "0.0095" "0.0138" "0.0201" "0.0292" "0.0425" "0.0619" "0.0901" "0.1311" "0.1908" "0.2772" "0.4026" "0.5848" "0.8496" "1.0000")

for i in "${!arg[@]}"; do
    variance="${arg[$i]}"
    echo "Running gen set with variance $variance and seed $i"
    ./bin/taskGenerator 1000 "$i" "$variance" 200 > tasks/"$i".txt
done
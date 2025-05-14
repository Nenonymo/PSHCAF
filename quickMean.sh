#!/bin/bash

# File name
file="$1"
col="$2"

# echo run command
echo "Calculating for col $col of file $file"

# Skip first line and extract 2nd column
awk -v col="$col" '
    NR>1 {
        x = $(col)
        sum += x 
        sumsq += x^2
        n++
    }
     END {
        if (n > 1) {
            mean = sum / n
            std = sqrt((sumsq - sum^2 / n) / (n - 1))
            printf "Mean: %.5f\nStd Dev: %.5f\n", mean, std
        }
     }' "$file"


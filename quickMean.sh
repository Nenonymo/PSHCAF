#!/bin/bash

# File name
file="tasks/0.txt"
file="tasks/8.txt"

# Skip first line and extract 2nd column
awk 'NR>1 {sum += $2; sumsq += ($2)^2; n++}
     END {
        if (n > 1) {
            mean = sum / n
            std = sqrt((sumsq - sum^2 / n) / (n - 1))
            printf "Mean: %.5f\nStd Dev: %.5f\n", mean, std
        }
     }' "$file"


awk 'NR>1 {sum += $2; sumsq += ($2)^2; n++}
     END {
        if (n > 1) {
            mean = sum / n
            std = sqrt((sumsq - sum^2 / n) / (n - 1))
            printf "Mean: %.5f\nStd Dev: %.5f\n", mean, std
        }
     }' "$file"
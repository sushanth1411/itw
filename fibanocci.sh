#!/bin/bash

# Read the number of terms
echo "Enter the number of terms:"
read n

# Initialize the first two terms
a=0
b=1

echo "Fibonacci series up to $n terms:"

for (( i=0; i<n; i++ ))
do
    echo -n "$a "
    # Calculate the next term
    fn=$((a + b))
    a=$b
    b=$fn
done

echo

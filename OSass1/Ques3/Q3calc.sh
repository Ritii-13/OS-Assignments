#!/bin/bash

# Create the "Result" directory if it doesn't exist
mkdir -p Result

# Read input.txt line by line
while IFS= read -r line || [[ -n "$line" ]]; do
    # Split the line into x, y, and operation
    read -r x y operation <<< "$line"
    
    case "$operation" in
        "xor")
            result=$((x ^ y))
            ;;
        "product")
            result=$((x * y))
            ;;
        "compare")
            if [ "$x" -gt "$y" ]; then
                result="$x"
            else
                result="$y"
            fi
            ;;
        *)
            echo "Invalid operation: $operation"
            continue
            ;;
    esac
    
    # Write the result to output.txt
    echo "The result is: $result" >> Result/output.txt
done < input.txt

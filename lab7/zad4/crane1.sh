#!/bin/bash

size=3
counter=0

for file in first/*; do
    while [ $(ls buffer/ | wc -l) -ge $size ]; do
        sleep 1
    done
    echo "$file"
    if [ -f "$file" ]; then
        echo "created"
        mv "$file" buffer/
        ((counter++))
    fi
    sleep 1
done

kill -USR2 $PPID
echo "crane1: $counter"

exit 0
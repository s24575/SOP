#!/bin/bash

size=3
counter=0

for file in first/*; do
    while [ $(ls buffer/ | wc -l) -ge $size ]; do
        sleep 1
    done
    echo "$file"
    if [ -f "$file" ]; then
        mv "$file" buffer/
        ((counter++))
    fi
    sleep 1
done

# This kill was causing the issue, somehow bypassing the later exit and returning 140
# kill -USR2 $PPID

exit $counter
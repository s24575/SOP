#!/bin/bash

if [ $# -ne 3 ]; then
    echo "Must provide 3 arguments"
else
    for arg in "$@"
    do

        if [ $arg -le 0 ]; then
            echo "$arg is not a positive number"
            exit 1
        fi
    done

    echo "All args are positive numbers"
fi

exit 0
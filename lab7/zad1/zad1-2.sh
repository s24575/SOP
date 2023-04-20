#!/bin/bash

./zad1-1.sh $* &
pid=$! 
wait $pid
code=$?
if [ $code -eq 0 ]; then
    IFS=$'\n' arr=($(sort <<<"$*"))
    unset IFS

    # echo "${arr[*]}"
    # echo ${arr[0]}
    # echo ${arr[1]}
    # echo ${arr[2]}

    if [ $((${arr[0]} + ${arr[1]})) -gt ${arr[2]} ]; then
        echo "These numbers can make a triangle"
    else
        echo "These numbers can't make a triangle"
    fi

elif [ $code -eq 1 ]; then
    echo "error"
fi

exit 0

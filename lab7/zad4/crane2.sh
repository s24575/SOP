#!/bin/bash

counter=0
trap "echo 'crane2: $counter' && exit 0" SIGINT

hasCrane1Finished=false

function crane1_finished {
    hasCrane1Finished=true
}

trap crane1_finished USR1

while true; do
    current=$(ls buffer/ | wc -l)
    if [ $current -gt 0 ]; then
        file=$(ls buffer/ | head -n 1)
        if [[ -f "buffer/$file" ]]; then
            mv "buffer/$file" second/
            ((counter++))
        fi
    elif [ $hasCrane1Finished = true ]; then
        break
    fi
    sleep 2
done

exit $counter
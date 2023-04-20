#!/bin/bash

rm -rf first/ second/ buffer/
mkdir first second buffer
touch first/file{1..5}

function usr1_signal() {
    ./crane1.sh &
    c1_pid=$!
    ./crane2.sh &
    c2_pid=$!
}

function usr2_signal() {
    kill -USR1 $c2_pid
}

trap usr1_signal USR1
trap usr2_signal USR2
trap 'kill $c1_pid $c2_pid; echo "killed both cranes"; exit' SIGINT

# echo "executing: kill -USR1 $$"
# kill -USR1 $$

wait $c1_pid
wait $c2_pid
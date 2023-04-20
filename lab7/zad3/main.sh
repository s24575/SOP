#!/bin/bash

trap "echo I\'m immortal" SIGINT
trap "trap - SIGINT" SIGHUP
while true
do
    sleep 1
done
exit 0
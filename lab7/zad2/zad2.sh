#!/bin/bash

trap ./zad2-napis.sh USR1
trap ./zad2-koniec.sh USR2
while true
do
    sleep 5
done
exit 0
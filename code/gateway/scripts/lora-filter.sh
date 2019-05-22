#!/bin/bash

n1=$(cat /home/pi/polytech19/logs/log.txt | grep -a -i "0099387A" -A 2 | grep "JSON up" | grep -v "\"size\":18" | cut -d: -f 15 | cut -d} -f 1 | cut -d\" -f 2)
n1=$n1" 0099387A"
echo $n1 > /home/pi/polytech19/logs/data.txt

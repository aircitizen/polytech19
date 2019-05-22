#!/bin/bash

TEMPERATURE=23.6
HUMIDITY=30
PM10=10
PM2_5=10
NODE="0099387A"

cat /home/pi/polytech19/logs/data.txt | while read line
do
	data=$(echo $line | cut -d" " -f 1)
	NODE=$(echo $line | cut -d" " -f 2)
	data=$(nodejs /home/pi/polytech19/code/gateway/scripts/lora-decode.js $data)
	TEMPERATURE=$(echo $data | cut -d" " -f 1)
	HUMIDITY=$(echo $data | cut -d" " -f 2)
	PM10=$(echo $data | cut -d" " -f 3)
	PM2_5=$(echo $data | cut -d" " -f 4)

	influx -database "aircitizen" -execute "insert data temperature=$TEMPERATURE,humidity=$HUMIDITY,pm10=$PM10,pm2_5=$PM2_5,node=$NODE"
done

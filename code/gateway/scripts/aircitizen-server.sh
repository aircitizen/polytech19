#!/bin/bash

echo Starting Server
(while true;
do
	/home/pi/polytech19/code/gateway/scripts/lora-start.sh > /dev/null 2>&1
	echo [WARN] restarting server
done)&

echo [INFO] Logging data
while :
do
	bash /home/pi/polytech19/code/gateway/scripts/lora-filter.sh
	echo > /home/pi/polytech19/logs/log.txt
	bash /home/pi/polytech19/code/gateway/scripts/insert-messages.sh
	echo > /home/pi/polytech19/logs/data.txt
	sleep 900 # 15 minutes
done

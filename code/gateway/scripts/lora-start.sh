#!/bin/bash

# reset gateway
/home/pi/lora_gateway/reset_lgw.sh stop
/home/pi/lora_gateway/reset_lgw.sh start
cd /home/pi/packet_forwarder/lora_pkt_fwd/ && ./update_gwid.sh global_conf.json

# start packet forwarder
mkdir /home/pi/polytech19/logs/
cd /home/pi/packet_forwarder/lora_pkt_fwd/ && ./lora_pkt_fwd | tee /home/pi/polytech19/logs/log.txt > /dev/null

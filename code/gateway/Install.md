# This is how to install all the software needed for the gateway

## Install base Raspberry Pi system
Download the official [raspbian image file](https://www.raspberrypi.org/downloads/raspbian/).
Raspbian Lite is good, however you can install standard raspbian with desktop.
You can find on internet how to install raspbian and how to connect it to internet.
Now we assume you have a running raspberry connected to internet and that you directly have access to it with a keyboard and a screen or over ssh.

## Download LoRa software
LoRa gateway and packet-forwarder should be downloaded in the pi home directory :

```bash
git clone https://github.com/Lora-net/lora_gateway
git clone https://github.com/Lora-net/packet_forwarder
```
In order to decrypt the LoRa messages you need lora-packet and npm
```bash
sudo apt-get install node npm
git clone https://github.com/anthonykirby/lora-packet
```
then download this project :
```bash
git clone https://github.com/aircitizen/polytech19
```
## Install Grafana and Influxdb
In order to monitor data we install a local visualization tool.
Here is a useful [link](https://www.circuits.dk/install-grafana-influxdb-raspberry/) providing all the details to setup Grafana + Influxdb on the Raspberry Pi.

## Start the aircitizen gateway
To start it you simply have to run
```bash
polytech19/code/gateway/scripts/aircitizen-server.sh
```

## How to filter messages from multiple nodes
in the  script ```polytech19/code/gateway/scripts/lora-filter.sh``` you can duplicate the existing lines and modify the string "0099387A" (in the grep command and in the line after). This number is the DevAddr of your LoRa device. It can be obtained on your node by using at+id command ([see here](http://wiki.seeedstudio.com/LoRa_LoRaWan_Gateway_Kit/#step-4-use-seeeduino-lorawan-gpsrhf76-052am-access-lorawan-server)).

"use strict";
var lora_packet = require('lora-packet');

// decode a packet
var packet = lora_packet.fromWire(new Buffer(process.argv[2], 'base64'));


// decrypt payload
var AppSKey = new Buffer('2B7E151628AED2A6ABF7158809CF4F3C', 'hex');
var NwkSKey = new Buffer('2B7E151628AED2A6ABF7158809CF4F3C', 'hex');
console.log(lora_packet.decrypt(packet, AppSKey, NwkSKey).toString());

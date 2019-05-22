#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <avr/dtostrf.h>
#include <SoftwareSerial.h>
#include "Adafruit_SHT31.h"
#include "SdsDustSensor.h"

int rxPin = 7;
int txPin = 8;
SdsDustSensor sds(rxPin, txPin);

Adafruit_SHT31 sht31 = Adafruit_SHT31();

String str;

String command1="AT+CMSGHEX=";

int Get_Temperature(){
  float t = sht31.readTemperature();
  if (! isnan(t)) {  // check if 'is not a number'
    return int(t);
  } else {
    return -1;
  }
 }

int Get_Humidity(){
  float h = sht31.readHumidity();
  if (! isnan(h)) {  // check if 'is not a number'
    return int(h);
  } else {
    return -1;
  }
 }

String Get_PM(){
    PmResult pm = sds.readPm();
    String pm25=String(int(pm.pm25));
    String pm10=String(int(pm.pm10));
    String s=pm25+" "+pm10;
  if (pm.isOk()) {
    return s;
   //return pm.toString();
  } else {
    return "-1 -1";
  }
}

void Test_Commands(void){
  /*
  while(SerialUSB.available())
     {
         Serial1.write(SerialUSB.read());

     }
    */
   while(Serial1.available())
     {
        SerialUSB.write(Serial1.read());
     }
 }

void Measure(){
  str=String(Get_Temperature())+" "+String(Get_Humidity())+ " "+ Get_PM();
  SerialUSB.println("Finish measure:"+str);
  delay(5000);
}

void Envoyer(){
  String message=command1+"\""+str+"\"";
  Serial1.println(message);
  SerialUSB.println("Finish envoyer:"+message);
  delay(5000);
  //SerialUSB.println("Finish envoyer:"+message);
}


 void setup()
 {
    Serial1.begin(9600);
    SerialUSB.begin(9600);

     sds.begin();

    SerialUSB.println("Start");

  if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    SerialUSB.println("Couldn't start");
    while (1) delay(1);
  }
 }


 void loop()
 {
  //SerialUSB.println(String(Get_Temperature())+"aaa");
  //SerialUSB.println(String(Get_Humidity())+"bbbb");
  //delay(3000);

  delay(5000);    //delay 5s au debut
  Serial1.println("at+mode=lwabp");
  delay(5000);    //delay 5s
  Test_Commands();

  while(1){
    Measure(); //delay 20s
    Envoyer(); //delay 10s
    Test_Commands();
    delay(60000);
    SerialUSB.println("--------------------------------------");
    // Serial1.println("AT+CMSGHEX=\"22.5\"");
    //  Test_Commands();
  }
}

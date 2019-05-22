#include <Arduino.h>
#include <stdlib.h>
#include <Wire.h>
#include <avr/dtostrf.h>
#include <SoftwareSerial.h>
#include "Adafruit_SHT31.h"
#include "SdsDustSensor.h"
#include <LoRaWan.h>
#include <EnergySaving.h>
#include <RTCInt.h>

EnergySaving nrgSave;
RTCInt rtc;

int rxPin = 7;
int txPin = 8;
int delay_temp= 10000;
SdsDustSensor sds(rxPin, txPin);
String str_pm="-1 -1";

Adafruit_SHT31 sht31 = Adafruit_SHT31();

String str;

//String command1="AT+CMSGHEX=";
String command1="AT+MSG=";

void rest_alarm_int(void)  //interrupt routine
{}

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
    sds.wakeup();
    delay(30000);
    PmResult pm = sds.readPm();
    String pm25=String(int(pm.pm25));
    String pm10=String(int(pm.pm10));
    sds.sleep();
  if (pm.isOk()) {
    str_pm =pm25+" "+pm10;
    return str_pm;
  } else {
    return str_pm;
  }
}

void Measure(){
  str=String(Get_Temperature())+" "+String(Get_Humidity())+ " "+ Get_PM();
  SerialUSB.println("Finish measure:"+str);
  delay(delay_temp);
}

void Envoyer(){
  String message=command1+"\""+str+"\"";
  Serial1.println(message);
  SerialUSB.println("Finish envoyer:"+message);
  delay(delay_temp);
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

    rtc.begin(TIME_H24);
    rtc.setTime(0,0,0,0);
    rtc.enableAlarm(SEC,ALARM_INTERRUPT,rest_alarm_int);
    rtc.time.hour=0;
    rtc.time.minute=0;
    rtc.time.second=30;
    nrgSave.begin(WAKE_RTC_ALARM);  //standby setup for external interrupts
    rtc.setAlarm();

 }


 void loop()
 {
    Measure();
    Envoyer();
    SerialUSB.println("--------------------------------------");

    rtc.begin(TIME_H24);
    rtc.setTime(0,0,0,0);
    rtc.enableAlarm(SEC,ALARM_INTERRUPT,rest_alarm_int);
    rtc.time.hour=0;
    rtc.time.minute=0;
    rtc.time.second=30;
    nrgSave.begin(WAKE_RTC_ALARM);  //standby setup for external interrupts
    rtc.setAlarm();
}

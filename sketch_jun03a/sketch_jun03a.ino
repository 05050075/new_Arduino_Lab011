#include <LWiFi.h>
#include <WiFiClient.h>
#include "MCS.h"
#include "DHT.h"
#define DHTTYPE DHT11
#define DHTPIN 2 
DHT dht(DHTPIN, DHTTYPE);
// Assign AP ssid / password here
#define _SSID "嗷嗷嗷"
#define _KEY  "19970408"

// Assign device id / key of your test device
MCSDevice mcs("DfRJgbKO", "nF71QK5b0FzeeoK0");

// Assign channel id 
// The test device should have 2 channel
// the first channel should be "Controller" - "On/Off"
// the secord channel should be "Display" - "On/Off"

MCSDisplayFloat Temperature("a");
MCSDisplayFloat Humidity("z");

#define LED_PIN 7

void setup() {
  // setup Serial output at 9600
  Serial.begin(9600);
dht.begin();
  // setup LED/Button pin
  pinMode(7, OUTPUT);

  // setup Wifi connection
  while(WL_CONNECTED != WiFi.status())
  {
    Serial.print("WiFi.begin(");
    Serial.print(_SSID);
    Serial.print(",");
    Serial.print(_KEY);
    Serial.println(")...");
    WiFi.begin(_SSID, _KEY);
  }
  Serial.println("WiFi connected !!");

  // setup MCS connection

  mcs.addChannel(Temperature);
  mcs.addChannel(Humidity);
  while(!mcs.connected())
  {
    Serial.println("MCS.connect()...");
    mcs.connect();
  }
  Serial.println("MCS connected !!");

  // read LED value from MCS server
  
}

void loop() {

  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // call process() to allow background processing, add timeout to avoid high cpu usage
  Serial.print("process(");
  Serial.print(millis());
  Serial.println(")");
  mcs.process(100);
      if(!Temperature.set(t))
    {
      Serial.print("Failed to update remote");
      Serial.println(Temperature.value());
    }
          if(!Humidity.set(h))
    {
      Serial.print("Failed to update remote");
      Serial.println(Humidity.value());
    }
 delay(1000);
 
  // updated flag will be cleared in process(), user must check it after process() call.
  while(!mcs.connected())
  {
    Serial.println("re-connect to MCS...");
    mcs.connect();
    if(mcs.connected())
      Serial.println("MCS connected !!");
  }


  }

 
  // check if need to re-connect
 

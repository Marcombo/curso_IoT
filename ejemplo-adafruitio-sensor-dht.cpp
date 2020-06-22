#include <Arduino.h>
#include "AdafruitIO_WiFi.h"
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <Wire.h>


#define DHTPIN            D6
#define DHTTYPE           DHT22

/************************ Adafruit IO Config *******************************/

// visit io.adafruit.com if you need to create an account,
// or if you need your Adafruit IO key.
#define IO_USERNAME    "xxxx"
#define IO_KEY         "xxxx"

/******************************* WIFI **************************************/

// the AdafruitIO_WiFi client will work with the following boards:
//   - HUZZAH ESP8266 Breakout -> https://www.adafruit.com/products/2471
//   - Feather HUZZAH ESP8266 -> https://www.adafruit.com/products/2821
//   - Feather HUZZAH ESP32 -> https://www.adafruit.com/product/3405
//   - Feather M0 WiFi -> https://www.adafruit.com/products/3010
//   - Feather WICED -> https://www.adafruit.com/products/3056

#define WIFI_SSID       "xxxx"
#define WIFI_PASS       "xxxx"


// comment out the following two lines if you are using fona or ethernet
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS);

// Adafruit IO Publish Example
//
// Adafruit invests time and resources providing this open source code.
// Please support Adafruit and open source hardware by purchasing
// products from Adafruit!
//
// Written by Todd Treece for Adafruit Industries
// Copyright (c) 2016 Adafruit Industries
// Licensed under the MIT license.
//
// All text above must be included in any redistribution.


/************************ Example Starts Here *******************************/


DHT_Unified dht(DHTPIN, DHTTYPE);

// set up the 'counter' feed
AdafruitIO_Feed *adafruit_humedad = io.feed("Humedad");
AdafruitIO_Feed *adafruit_temperatura = io.feed("Temperatura");

int timecount = 0;

void setup() {

  // start the serial connection
  Serial.begin(9600);

  dht.begin();

  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.

  // wait for serial monitor to open
  while(! Serial);

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();

  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println("Error reading temperature!");
  }
  else {
    Serial.print("Temperature: ");
    Serial.print(event.temperature);
    Serial.println(" *C");
    adafruit_temperatura->save(event.temperature);
  }

  delay(5000);

  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    Serial.println("Error reading humidity!");
  }
  else {
    Serial.print("Humidity: ");
    Serial.print(event.relative_humidity);
    Serial.println("%");
    adafruit_humedad->save(event.relative_humidity);
  }

  delay(5000);
  
}
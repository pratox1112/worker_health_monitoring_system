#include <Wire.h>
#include<DHT.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_ADXL345_U.h>
#include "MAX30100_PulseOximeter.h"
#define REPORTING_PERIOD_MS     1000

PulseOximeter pox;
uint32_t tsLastReport = 0;
unsigned int heart = 0, oxidation = 0, timer = 0, temp = 0;

//
///* Assign a unique ID to this sensor at the same time */
//Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

uint8_t DHTPIN = 4;   // Digital pin connected to the DHT sensor

#define DHTTYPE DHT11   // DHT 11

// if you require to change the pin number, Edit the pin with your arduino pin.
DHT dht(DHTPIN, DHTTYPE);
 
int humidity=0, temperature=0;

#define REPORTING_PERIOD_MS     1000

int data_timer = 0, servo_timer = 0, servo_flag = 0;

void onBeatDetected()
{
  //    Serial.println("Beat!");
}

void setup()
{
//  pinMode(A0, INPUT);
  Serial.begin(9600);

    dht.begin();
  Serial.print("Initializing pulse oximeter..");

  // Initialize the PulseOximeter instance
  // Failures are generally due to an improper I2C wiring, missing power supply
  // or wrong target chip
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  // Register a callback for the beat detection
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop()
{
  // Make sure to call update as fast as possible
  pox.update();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
//    Serial.print("Heart rate:");

    heart = pox.getHeartRate();
//    Serial.println("heart");
//    Serial.println(heart);
    //        Serial.print(heart);

//    Serial.print("bpm / SpO2:");
    oxidation = pox.getSpO2();
//    Serial.println("oxidation");
//    Serial.println(oxidation);

//    Serial.println("%");

    tsLastReport = millis();

  }
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  humidity = h;
  temperature=t;
//  Serial.println("humidity");
//  Serial.println(humidity);

//  Serial.println("temperature");
//  Serial.println(temperature);
//delay(100);

  data_timer++;
  if(data_timer > 5000)
  {
    data_timer = 0;
    Serial.print('2');
    Serial.print(',');
    Serial.print(heart);
    Serial.print(',');
    Serial.print(oxidation);
    Serial.print(',');
    Serial.println(temperature);
  }
}

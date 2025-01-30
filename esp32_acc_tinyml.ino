#include "EloquentTinyML.h"
#include "eloquent_tinyml/tensorflow.h"
#include "sine_model.h"

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
#define IN 4
#define OUT 1
#define ARENA 1024

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);


Eloquent::TinyML::TensorFlow::TensorFlow<IN, OUT, ARENA> tf;
//using namespace Eloquent::TinyML::TensorFlow;

uint32_t tsLastReport = 0;
unsigned int heart = 0, oxidation = 0, timer = 0, temp = 0;
int data_timer = 0, servo_timer = 0, servo_flag = 0,acc = 0;
String input_data, sensor, sensor1, sensor2,sensor3;

//TensorFlow<IN, OUT, ARENA> tf;
//float a=2,b=2,c=2;

void displaySensorDetails(void)
{
  sensor_t sensor;
  accel.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" m/s^2");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" m/s^2");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" m/s^2");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void displayDataRate(void)
{
  Serial.print  ("Data Rate:    "); 
  
  switch(accel.getDataRate())
  {
    case ADXL345_DATARATE_3200_HZ:
      Serial.print  ("3200 "); 
      break;
    case ADXL345_DATARATE_1600_HZ:
      Serial.print  ("1600 "); 
      break;
    case ADXL345_DATARATE_800_HZ:
      Serial.print  ("800 "); 
      break;
    case ADXL345_DATARATE_400_HZ:
      Serial.print  ("400 "); 
      break;
    case ADXL345_DATARATE_200_HZ:
      Serial.print  ("200 "); 
      break;
    case ADXL345_DATARATE_100_HZ:
      Serial.print  ("100 "); 
      break;
    case ADXL345_DATARATE_50_HZ:
      Serial.print  ("50 "); 
      break;
    case ADXL345_DATARATE_25_HZ:
      Serial.print  ("25 "); 
      break;
    case ADXL345_DATARATE_12_5_HZ:
      Serial.print  ("12.5 "); 
      break;
    case ADXL345_DATARATE_6_25HZ:
      Serial.print  ("6.25 "); 
      break;
    case ADXL345_DATARATE_3_13_HZ:
      Serial.print  ("3.13 "); 
      break;
    case ADXL345_DATARATE_1_56_HZ:
      Serial.print  ("1.56 "); 
      break;
    case ADXL345_DATARATE_0_78_HZ:
      Serial.print  ("0.78 "); 
      break;
    case ADXL345_DATARATE_0_39_HZ:
      Serial.print  ("0.39 "); 
      break;
    case ADXL345_DATARATE_0_20_HZ:
      Serial.print  ("0.20 "); 
      break;
    case ADXL345_DATARATE_0_10_HZ:
      Serial.print  ("0.10 "); 
      break;
    default:
      Serial.print  ("???? "); 
      break;
  }  
  Serial.println(" Hz");  
}

void displayRange(void)
{
  Serial.print  ("Range:         +/- "); 
  switch(accel.getRange())
  {
    case ADXL345_RANGE_16_G:
      Serial.print  ("16 "); 
      break;
    case ADXL345_RANGE_8_G:
      Serial.print  ("8 "); 
      break;
    case ADXL345_RANGE_4_G:
      Serial.print  ("4 "); 
      break;
    case ADXL345_RANGE_2_G:
      Serial.print  ("2 "); 
      break;
    default:
      Serial.print  ("?? "); 
      break;
  }  
  Serial.println(" g");  
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
void setup() {
    Serial.begin(9600);
    tf.begin(sine_model);
if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no ADXL345 detected ... Check your wiring!");
    while(1);
  }

  /* Set the range to whatever is appropriate for your project */
  accel.setRange(ADXL345_RANGE_16_G);
  // accel.setRange(ADXL345_RANGE_8_G);
  // accel.setRange(ADXL345_RANGE_4_G);
  // accel.setRange(ADXL345_RANGE_2_G);
  
  /* Display some basic information on this sensor */
  displaySensorDetails();
  
  /* Display additional settings (outside the scope of sensor_t) */
  displayDataRate();
  displayRange();
  Serial.println("");
delay(3000);
}

void loop() {


sensors_event_t event; 
  accel.getEvent(&event);
 acc= event.acceleration.z;
  /* Display the results (acceleration is measured in m/s^2) */
//  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
//  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
//  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.println("m/s^2 ");
//  delay(500);
  
  while (Serial.available() > 0)
  {
    input_data = Serial.readStringUntil('\n');
    //Serial.println(input_data);
    sensor = getValue(input_data, ',', 0);
    if (sensor == "2")
    {
      sensor1 = getValue(input_data, ',', 1);
      sensor2 = getValue(input_data, ',', 2);
      sensor3 = getValue(input_data, ',', 3);
      int lastIndex = sensor3.length() - 1;
      sensor3.remove(lastIndex);




    float input[4] = {sensor1.toInt(),sensor2.toInt(),sensor3.toInt(),event.acceleration.z};// hearrate,oxidation,temp,accelrmtr
    float y_pred = tf.predict(input);
    int stat = 0,acc1 = 0 ;
    if (y_pred >0 )
    {
      stat = 1;
    }
    else
    {
      stat = 0;
    }
    if(acc >= 5)
    {
      acc1 = 0;
    }
    else
    {
      acc1=1;
    }
//    Serial.print("\t predicted: ");
//    Serial.println(y_pred);
      Serial.print('2');
    
      Serial.print(',');
      Serial.print(sensor1);
      Serial.print(':');
      Serial.print(sensor2);
      Serial.print(':');
      Serial.print(sensor3);
      Serial.print(':');
      Serial.print(acc1);
      Serial.print(':');
      Serial.print(stat);
      Serial.println(',');
    //delay(500);

    }  }
}

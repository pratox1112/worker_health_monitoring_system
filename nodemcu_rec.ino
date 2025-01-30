#include <ESP8266WiFi.h> // Enables the ESP8266 to connect to the local network (via WiFi)
#include <PubSubClient.h> // Allows us to connect to, and publish to the MQTT broker

const int ledPin = 2; // This code uses the built-in led for visual feedback that the button has been pressed
//const int buttonPin = 13; // Connect your button to pin #13

// WiFi
// Make sure to update this for your own WiFi network!
const char* ssid = "project";
const char* wifi_password = "project@123";

// MQTT
// Make sure to update this for your own MQTT Broker!
const char* mqtt_server = "broker.hivemq.com";

const char* mqtt_topic1 = "tinyml_616";
// The client id identifies the ESP8266 device. Think of it a bit like a hostname (Or just a name, like Greg).
const char* clientID = "tinyml";

// Initialise the Pushbutton Bouncer object
//Bounce bouncer = Bounce();

String no_of_sensor, data, sensor, sensor1, sensor2, sensor3, sensor4, sensor5, sensor6;

int data_received = 0;
char char_data[50];

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
PubSubClient client(mqtt_server, 1883, wifiClient); // 1883 is the listener port for the Broker

#define setPin 4

void setup() {
  pinMode(ledPin, OUTPUT);
  //  pinMode(buttonPin, INPUT);
  // Switch the on-board LED off to start with
  digitalWrite(ledPin, HIGH);
  delay(1000);
  digitalWrite(ledPin, LOW);
  delay(1000);
  digitalWrite(ledPin, HIGH);

    pinMode(setPin, OUTPUT);
  digitalWrite(setPin, HIGH);           // HC-12 normal, transparent mode
  // Setup pushbutton Bouncer object
  //  bouncer.attach(buttonPin);
  //  bouncer.interval(5);

  // Begin Serial on 115200
  // Remember to choose the correct Baudrate on the Serial monitor!
  // This is just for debugging purposes
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);
  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);
  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  // Connect to MQTT Broker
  if (client.connect(clientID)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
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

void loop()
{
  client.loop();

    if (Serial.available() > 0)
    {
      no_of_sensor = Serial.readStringUntil('\n');
          Serial.print(no_of_sensor);
      sensor = getValue(no_of_sensor, ',', 0);
//          Serial.println(sensor);
      if ( sensor.equals("2"))
      {
        data = getValue(no_of_sensor, ',', 1);
//                  int lastIndex = data.length() - 1;
//                  data.remove(lastIndex);
//                  Serial.println(data);

        data_received = 1;

      }
  }

  if (data_received == 1)
  {
//    Serial.print("1");
    data_received = 0;
    data.toCharArray(char_data, 50);
    //    Serial.println(char_data);
    client.connect(clientID);
    delay(100); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(mqtt_topic1, char_data);
    //    Serial.println("published data");
  }
  delay(1000);
}



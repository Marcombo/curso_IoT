
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi network
const char* ssid     = "xxxx";
const char* password = "xxxx";


const char* mqttServer = "xxxx";
const int mqttPort = 1883;
const char* mqttUser= "xxxx";
const char* mqttPassword = "xxxx";

char sendtomqtt[10];

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
 
  // Start serial
  Serial.begin(115200);
  delay(10);

  // Connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password); // the program sets up the WiFi ssid and password using the WiFi.begin() function del ESP32 library.
 
  while (WiFi.status() != WL_CONNECTED) { // and the executes the WiFi.status() function to try to connect to WiFi Network. The program checks whether the WiFi.status() function returns a true value when its connect.
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  // when the ESP32 connects to WiFi network, the sketch displays a message, WiFi connected and the IP address of the ESP32 shows on the serial monitor.
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



client.setServer(mqttServer, mqttPort);
while (!client.connected()) {
  Serial.println("connecting to MQTT Server...");
  if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
    Serial.println("Connected to MQTT Server");
  }
  else {
    Serial.print("failed with state ");
    Serial.print(client.state());
    delay(2000);
  }
}
}

void loop() {
 for (int i=0; i<10; i++) {
  sprintf(sendtomqtt, "msg%d", i);
  client.publish("test", sendtomqtt);
  delay(2000);
 }
}

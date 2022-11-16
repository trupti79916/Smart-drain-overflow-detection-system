#include <SPI.h>
#include <LoRa.h>
#include <WiFi.h>

#define LED 2

const char* ssid = "Virus1392001";
const char* password = "Anukul1392001" ;

int    HTTP_PORT   = 80;
String HTTP_METHOD = "GET"; // or POST
char   HOST_NAME[] = "lora-device.herokuapp.com";
String PATH_NAME   = "/map";
 
WiFiClient client;
char c;

void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  while (!Serial);
  
  Serial.println("LoRa Receiver");
   LoRa.setPins(5,14,4);
  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

    WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println("\n");
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("ESP32 connected to wifi...");
  Serial.println(ssid);
  Serial.println("\n");
}

void loop() {
  // try to parse packet
  int packetSize = LoRa.parsePacket();
  if(client.connect(HOST_NAME, HTTP_PORT)) {
    
  if (packetSize) {
    // received a packet
    Serial.print("Received packet '");
    
    // read packet
    while (LoRa.available()) {
      c = (char)LoRa.read();
    }
    Serial.print(c);
    // print RSSI of packet
    Serial.println("___________________________________________");

        // if connected:
    Serial.println("Connected to server");
    // make a HTTP request:
    // send HTTP header
    client.println(HTTP_METHOD + " " + PATH_NAME + " HTTP/1.1");
    client.println("Host: " + String(HOST_NAME));
    client.println("Connection: keep-alive");
    client.println(); // end HTTP header
    client.println();

    while(client.connected()) {
      if(client.available()){
        // read an incoming byte from the server and print it to serial monitor:
        char c = client.read();
        Serial.print(c);
      }
    }

    // the server's disconnected, stop the client:

 //   delay(10000);
    client.stop();
    Serial.println();
    Serial.println("disconnected");
    } 
  }
  else {
    Serial.println("connection failed");
  }
}

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Tenda_GaMa";
const char* password = "9440431187";

const int trigPin = 12;
const int echoPin = 14;


//define sound velocity in cm/uS
#define SOUND_VELOCITY 0.034


long duration;
float distanceCm,distanceCm01,distanceCm02,distanceCm03;
float avg;
String volume_string;

AsyncWebServer server(80);

float dis(){

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance
  float distance = duration * SOUND_VELOCITY/2;

  return distance;
}


void setup() {
        Serial.begin(115200); 
        pinMode(trigPin, OUTPUT); 
        pinMode(echoPin, INPUT); 

        WiFi.begin(ssid, password);
        while (WiFi.status() != WL_CONNECTED) {
          delay(1000);
          Serial.println("Connecting to WiFi..");
        }

        Serial.println(WiFi.localIP());

        server.on("/avg", HTTP_GET, [](AsyncWebServerRequest *request){
          request->send_P(200, "text/plain", volume_string.c_str());
        });

        server.begin();

}

void loop() {

  distanceCm = dis();  
  delay(100);

  distanceCm01 = dis();
  delay(100);

  distanceCm02 = dis();
  delay(100);

  distanceCm03 = dis();

   avg =(distanceCm01+distanceCm02+distanceCm+distanceCm03)/4;  
  
  // Prints the distance on the Serial Monitor
  
  Serial.print("Distance-0: ");
  Serial.println(distanceCm);
  Serial.print("Distance-1: ");
  Serial.println(distanceCm01);
  Serial.print("Distance-2 : ");
  Serial.println(distanceCm02);
  Serial.print("avg= ");
  Serial.println(avg);
  volume_string =  String((float)avg,2);

  delay(1000);
}

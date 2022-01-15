#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <ESP8266HTTPClient.h>

#include "httpGetRequest.h"
#include "index.h"


const char* ssid = "Tenda_GaMa";
const char* password = "9440431187";

const char* INPUT_1 = "outputPin";
const char* INPUT_2 = "state";

const float emptyHeight=35;
const int motorPin =12; //Pin to control motor 
int motorStatus;
float heigthCm,volume  ;
String dis;

String avg ="http://192.168.0.117/avg";

AsyncWebServer server(80);

void measureVolume(){

volume = (emptyHeight-heigthCm)/emptyHeight;
 Serial.println(volume);

if(volume<0.25&&volume>0)
{
  motorStatus=1;
digitalWrite(motorPin,motorStatus);
Serial.println("motor Status is on");
}
else if (volume>0.9)
{
  motorStatus=0;
  digitalWrite(motorPin,motorStatus);
  Serial.println("motor Status is off");
}
else{

if(motorStatus==0){
  Serial.println("motor is off");
}
else{
  Serial.println("motor in on");
}

}
}


void setup() {
Serial.begin(115200);
WiFi.begin(ssid,password);
while(WiFi.status()!=WL_CONNECTED ){
  delay(1000);
  Serial.println("connecting to wifi....");
}
Serial.println(WiFi.localIP());

pinMode(motorPin,OUTPUT);

server.on("/",HTTP_GET,[](AsyncWebServerRequest *request){
  request->send_P(200,"text/html",index_html);
});

server.on("/motorstatus",HTTP_GET,[](AsyncWebServerRequest *request){
String var = String((int)motorStatus);
request->send_P(200,"text/html",var.c_str());
});

server.on("/volume",HTTP_GET,[](AsyncWebServerRequest *request){
String var = String((float)volume);
  request->send_P(200,"text/plain",var.c_str());
});

server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage1;
    String inputMessage2;
    
    if (request->hasParam(INPUT_1) && request->hasParam(INPUT_2)) {
      inputMessage1 = request->getParam(INPUT_1)->value();
      inputMessage2 = request->getParam(INPUT_2)->value();
      motorStatus =inputMessage2.toInt();
      digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
    }
    else {
      inputMessage1 = "No message sent";
      inputMessage2 = "No message sent";
    }
    Serial.print("IO-Pin: ");
    Serial.print(inputMessage1);
    Serial.print(" - Set to: ");
    Serial.println(inputMessage2);
    request->send(200, "text/plain", "OK");
  });

  server.begin();

}

void loop() {
  dis = httpGETRequest(avg);
  Serial.println(dis);

heigthCm = round(dis.toFloat());


measureVolume();
  delay(2000);
}


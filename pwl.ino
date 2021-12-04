/*
* ProbablyWirelessLights 1.0 https://github.com/MrCheatEugene/PCL/releases/1.0.1
* Donate: https://donationalerts.com/r/mrcheatt
* Latest version: https://github.com/MrCheatEugene/PCL/releases/latest/
* Android app: http://vds.mrcheat.ga/dl/pcl.apk http://vds.mrcheat.ga/dl/pcl.aab 
* Windows app: http://vds.mrcheat.ga/dl/pcl.zip
* Also, this project is based on PCL (ProbablyCoolLights), so it's fully compatible with it. You can use PCL Android app for Wifi connectivity.
Note if not uploads:
If not uploading with error avrdude: ser_open(): can't open device "\\.\COM4":Device is busy(or for other languages �������� � �������, and no this is not encoding error)
or any other:
Install driver for your board
Unplug&plug back in your Arduno
Close Arduino lights control software
Reboot your PC 
Change serial port in arduino IDE to board's port(after uploading - change it to COM4 if it isn't in Device manager for software to work)
---
Made with love by Emil Chairullin or https://github.com/MrCheatEugene
*/
int ledPin=2;//ledpin is a MOSFET pin(it must be N-channel) - default for Wemos d1 r2(lolin)
String str;//input string
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "WiFi_SSID"// SSID of your wifi
#define STAPSK  "12345678" // wifi password
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(24000);

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);//start listening serial port at 9600 baud
    WiFi.mode(WIFI_STA);//start wifi as station - like pc or phone
  WiFi.begin(ssid, password);// connect to wifi
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
  //set commands
  server.on("/turn_on", []() {
      digitalWrite(ledPin,HIGH);//set 100% brighntess to mosfet
    server.send(200, "text/plain", "true");
  });
  server.on("/script.js", []() {
      digitalWrite(ledPin,HIGH);//set 100% brighntess to mosfet
    server.send(200, "application/javascript", "function turn_on{ fetch('/turn_on'); document.getElementsByTagName('div')[0].innerHTML='Turned on';}function turn_off{ fetch('/turn_off'); document.getElementsByTagName('div')[0].innerHTML='Turned off';}function turn_on_smooth{ fetch('/turn_on_smooth'); document.getElementById('result').innerHTML='Turned on smootly';} function turn_off_smooth{ fetch('/turn_off_smooth');document.getElementsByTagName('div')[0].innerHTML='Turned off smoothly';} function blink{ fetch('/blink'); document.getElementsByTagName('div')[0].innerHTML='Blinked';}");
  });
    server.on("/style.css", []() {
    server.send(200, "text/css", "body { font: 16px Segoe UI} div { font: 28px Segoe UI Light} ");
  });

  server.on("/", []() {  
        server.send(200, "text/html", "UI can be here. Basic JS file with functions: /script.js. Basic CSS file: /style.css");
  });

  server.on("/turn_off", []() {  
    digitalWrite(ledPin,LOW);//set 0 brighntess to mosfet
    server.send(200, "text/plain", "true");
  });

  server.on("/turn_off", []() {  
    digitalWrite(ledPin,LOW);//set 0 brighntess to mosfet
    server.send(200, "text/plain", "true");
  });
  
  server.on("/turn_on_smooth", []() {
      fadeOn(1000,5);
    server.send(200, "text/plain", "true");
  });
  
  server.on("/turn_off_smooth", []() {
    fadeOff(1000,5);
    server.send(200, "text/plain", "true");
  });
  
  server.on("/turn_on_smooth_fast", []() {
    fadeOn(250,5);
    server.send(200, "text/plain", "true");
  });
  
  server.on("/turn_off_smooth_fast", []() {
    fadeOff(250,5);
    server.send(200, "text/plain", "true");
  });
  
  server.on("/blink", []() {
    fadeOn(1000,5);
fadeOff(1000,5);
    server.send(200, "text/plain", "true");
  });
  
  server.on("/blink_fast", []() {
    fadeOn(100,5);
fadeOff(100,5);
    server.send(200, "text/plain", "true");
  });
    server.onNotFound([]() {
      server.send(404,"text/plain","404 Not found");//check this vid out it's good
      });
 server.addHook([](const String & method, const String & url, WiFiClient * client, ESP8266WebServer::ContentTypeFunction contentType) {
    (void)method;      
    (void)url;       
    (void)client;      
    (void)contentType; 
 if(url.indexOf("/set%20")==0){//if command is set then 
    String input = url;
String firstVal, secondVal;
for (int i = 0; i < input.length(); i++) {//splitting strings by space https://gist.github.com/mattfelsen/9467420
  if (input.substring(i, i+1) == "%20") {
    firstVal = input.substring(0, i);
    secondVal = input.substring(i+1);
    break;
  }
}
    Serial.println(secondVal.toInt());//return result in Integer
    digitalWrite(ledPin,secondVal.toInt());  // set brighness as an input
}
    return ESP8266WebServer::CLIENT_REQUEST_CAN_CONTINUE;
  });
server.begin();
  Serial.println("HTTP server has started at port 24000");
}
// the loop function runs over and over again forever
void loop() {
while (Serial.available()) {//if catched command
  str=Serial.readString();str.replace("\r\n","");  str.replace("\n","");  //1.read it&convert it to string; 2. remove CRNL(Carriage return+Newline) byte from string(Windows) 3. remove NL(Newline) byte from string(*nix)
  if(str==""){
    Serial.println("No command was recognized. Send help for help.");//if no command was catched
    }
    if(str=="help"){//help command
      Serial.println("help : prints avaliable commands");//print something(all commands below in this IF do the same)
      Serial.println("turn_on: turn lights ON whitout PWM");
      Serial.println("turn_off: turn lights OFF whitout PWM");
      Serial.println("turn_on_smooth: turn lights ON smoothly using PWM - takes 1s to fully bright up");
      Serial.println("turn_off_smooth: turn lights OFF smoothly using PWM - takes 1s to fully bright down");
      Serial.println("turn_on_smooth_fast: turn lights ON using PWM - takes a quarter of a second(250ms) to fully bright up");
      Serial.println("turn_off_smooth_fast: turn lights OFF using PWM - takes a quarter of a second(250ms) to fully bright down");
      Serial.println("blink: turn lights on&off smoothly. takes 2 seconds in total");
      Serial.println("blink_fast: turn lights on&off really fast, DO NOT USE if you or people nearby you have increased light sensitivity problems");
      Serial.println("set Integer: set brigthness manually, where Integer is a number without floating point that's also less 1023");
      }
if(str=="turn_off"){//turn off
  digitalWrite(ledPin,LOW);//set 0 brighntess to mosfet
Serial.println("True");//return true
  }
  if(str=="turn_on"){//turn on
  digitalWrite(ledPin,HIGH);Serial.println("True");//set max brightness to mosfet&return true
  }
  if(str=="blink"){
    //fade In using PWM & fade Out using PWM 
fadeOn(1000,5);
fadeOff(1000,5);
}
 if(str=="blink_fast"){//fade In using PWM & fade Out using PWM, but more faster
fadeOn(100,5);
fadeOff(100,5);
}
  if(str=="turn_on_smooth"){//fade In using PWM 
fadeOn(1000,5);
}
  if(str=="turn_off_smooth"){//fade Out using PWM
fadeOff(1000,5);
}
  if(str=="turn_on_smooth_fast"){//fast fade in
fadeOn(250,5);
}
  if(str=="turn_off_smooth_fast"){//fast fade out
fadeOff(250,5);
}
  if(str.indexOf("set")==0){//if command is set then 
    
    String input = str;
String firstVal, secondVal;
for (int i = 0; i < input.length(); i++) {//splitting strings by space https://gist.github.com/mattfelsen/9467420
  if (input.substring(i, i+1) == " ") {
    firstVal = input.substring(0, i);
    secondVal = input.substring(i+1);
    break;
  }
}
    Serial.println(secondVal.toInt());//return result in Integer
    digitalWrite(ledPin,secondVal.toInt());  // set brighness as an input
}
}

  server.handleClient();
  MDNS.update();
}
void fadeOn(unsigned int time,int increament){//fade in function, i forgot where i copypasted it
for (byte value = 0 ; value < 255; value+=increament){
  if(value<254){
analogWrite(ledPin, value);
delay(time/(255/5));
}
}
Serial.println("True");
  digitalWrite(ledPin,HIGH);
}
void fadeOff(unsigned int time,int decreament){//fade out function,i forgot where i copypasted it
for (byte value= 255; value >0; value-=decreament){
analogWrite(ledPin, value);
delay(time/(255/5));
}
Serial.println("True");
  digitalWrite(ledPin,LOW);
}

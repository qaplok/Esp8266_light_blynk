#define BLYNK_TEMPLATE_ID "TMPL3DbNzllJ"
#define BLYNK_TEMPLATE_NAME "ESP826601"
#define BLYNK_AUTH_TOKEN "3iQzt-yiIn7-v1-5asHi19Y6_2aU0f3r"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <Arduino.h>
#include "PCF8574.h"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "QWww";
char pass[] = "9498498499";

// Set i2c address
PCF8574 pcf8574(0x20);

BlynkTimer timer;
int ledState1 = LOW;
int ledState2 = LOW;
int ledState3 = LOW;
int GirlandState = LOW;
int BtnGirland = LOW;

int button1 = 14; //GPIO14 
int button2 = 12; //GPIO12
int button3 = 13; //GPIO13
//int button4 = 0;  //P0 on pcf8574

void myTimerEvent()
{
  
}

void setup()
{
  
  pcf8574.pinMode(4, OUTPUT);
  pcf8574.pinMode(5, OUTPUT);
  pcf8574.pinMode(6, OUTPUT);
  pcf8574.pinMode(7, OUTPUT);
  pcf8574.digitalWrite(4, LOW);
  pcf8574.digitalWrite(5, LOW);
  pcf8574.digitalWrite(6, LOW);
  pcf8574.digitalWrite(7, LOW);

  //pcf8574.pinMode(2, OUTPUT);
  //pcf8574.digitalWrite(2, LOW);

  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pcf8574.pinMode(P0, INPUT);

  digitalWrite(button1, LOW);
  digitalWrite(button2, LOW);
  digitalWrite(button3, LOW);
  pcf8574.digitalWrite(P0, LOW);
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
  Serial.print("Init pcf8574...");
	if (pcf8574.begin()){
		Serial.println("OK");
	}else{
		Serial.println("FAIL");
	}
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
  if (digitalRead(button1) == HIGH){
     ledState1 = !ledState1;
     pcf8574.digitalWrite(4, ledState1);
     //Blynk.virtualWrite(V2, ledState1);
     Serial.println("led1 on");
     while (digitalRead(button1) == HIGH){
      delay(200);
     }
     
   }
   if (digitalRead(button2) == HIGH) {
     ledState2 = !ledState2;
     pcf8574.digitalWrite(5, ledState2);
     //Blynk.virtualWrite(V3, ledState2);
     Serial.println("led2 on");
   }
   if (digitalRead(button3) == HIGH) {
     ledState3 = !ledState3;
     pcf8574.digitalWrite(6, ledState3);
    // Blynk.virtualWrite(V4, ledState3);
     Serial.println("led3 on");
   }
   if (pcf8574.digitalRead(P0) == HIGH) {
     GirlandState = !GirlandState;
     pcf8574.digitalWrite(7, GirlandState);
    // Blynk.virtualWrite(V5, GirlandState);
     Serial.println("led4 on");
   }

}

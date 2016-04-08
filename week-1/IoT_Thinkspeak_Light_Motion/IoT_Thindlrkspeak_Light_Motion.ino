#include "EIoTCloudRestApi.h"
#include "EIoTCloudRestApiConfig.h"
#include "ThingSpeak.h"
#include <ESP8266WiFi.h>

// IoT
EIoTCloudRestApi eiotcloud;

// Thinkspeak
char ssid[] = "xxxxxx";
char pass[] = "xxxxxx";

int status = WL_IDLE_STATUS;
WiFiClient  client;

long myChannelNumber = 106657; 
const char * myWriteAPIKey = "GALN6Y5ZB7SS9EMD"; 

// Setup
// the naming could be better to make it more understandable for other people
#define pir D0
#define led LED_BUILTIN
#define ldr A0

int pirState = LOW;
int val = 0;
int light;

void setup() {
  WiFi.begin(ssid, pass);  
  ThingSpeak.begin(client);
  eiotcloud.begin();
  Serial.begin(9600);
}

void loop() {
  int motion = digitalRead(pir); // already defined D0 so you're better off using the D0 you've defined in pir
  int light = analogRead(ldr); // could do the same with analog

  ThingSpeak.setField(1,light);
  ThingSpeak.setField(2, motion);
  ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);  

  eiotcloud.sendParameter("57050077c943a0661cf314bc/17yzUGAspb7srIv0", light);
  eiotcloud.sendParameter("57050077c943a0661cf314bc/uHIQBZexNqt7gyIq", motion);
  
   val = digitalRead(pir);
    if (val == HIGH) {
      digitalWrite(led, HIGH);
        if (pirState == LOW) {
          Serial.println("Motion detected!");
          pirState = HIGH;
        }
    } else {
      digitalWrite(led, LOW);
        if (pirState == HIGH) {
          Serial.println("Motion ended");
          pirState = LOW;
        }
    }

  delay(1000);
}

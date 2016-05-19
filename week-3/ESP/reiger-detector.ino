// Include 
#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <Time.h>
#include <TimeLib.h>

#define TIME_MSG_LEN  11   // time sync to PC is HEADER followed by unix time_t as ten ascii digits
#define TIME_HEADER  255   // Header tag for serial time sync message


// Declarations  
int pir = D1;
int led = D4;
int speakerOut = D3;
int pirState = LOW;
int val = 0;

// TONES  ==========================================
// Start by defining the relationship between 
//       note, period, &  frequency. 
#define  c     3830    // 261 Hz 
#define  d     3400    // 294 Hz 
#define  e     3038    // 329 Hz 
#define  f     2864    // 349 Hz 
#define  g     2550    // 392 Hz 
#define  a     2272    // 440 Hz 
#define  b     2028    // 493 Hz 
#define  C     1912    // 523 Hz 
// Define a special note, 'R', to represent a rest
#define  R     0

// Do we want debugging on serial out? 1 for yes, 0 for no
int DEBUG = 1;
// MELODY and TIMING  =======================================
//  melody[] is an array of notes, accompanied by beats[], 
//  which sets each note's relative length (higher #, longer note) 
//int melody[] = {  C,  b,  g,  C,  b,   e,  R,  C,  c,  g, a, C };
int melody[] = {  C,  b };
int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 8 }; 
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
// Set overall tempo
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES
// Initialize core variables


int tone_ = 0;
int beat = 0;
long duration  = 0;

int power = false;
const char* host     = "tomsnepvangers.com"; // Your domain
String path          = "/IoT/switch.json";

const char* ssid     = "iPhone van Tom"; // Fill in your own SSID.
const char* password = "snepvangers"; // Fill in your password.

void sendMotionValue(int value){

  WiFiClient client;
  int contentLength = String(value).length() + 7;

    if (client.connect("tomsnepvangers.com", 80)) {
    Serial.println("connected");
    client.println("POST /IoT/motion.php HTTP/1.1");
    client.println("Host: tomsnepvangers.com");
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.print("Content-Length: ");
    client.println(contentLength);
    client.println();
    client.print("motion=");
    client.println(value);
  } else {
    Serial.println("connection failed");
  }
}

void onOffSwitch() {
  Serial.print(hour());
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n\r\n");

  delay(500); // wait for server to respond

  // read response
  String section = "header";
  while (client.available()) {
    String line = client.readStringUntil('\r');
    // Serial.print(line);
    // we'll parse the HTML body here
    if (section == "header") { // headers..
      Serial.print(".");
      if (line == "\n") { // skips the empty space at the beginning
        section = "json";
      }
    }
    else if (section == "json") { // print the good stuff
      section = "ignore";
      String result = line.substring(1);

      // Parse JSON
      int size = result.length() + 2;
      char json[size];
      result.toCharArray(json, size);
      StaticJsonBuffer<200> jsonBuffer;
      JsonObject& json_parsed = jsonBuffer.parseObject(json);
      if (!json_parsed.success())
      {
        Serial.println("parseObject() failed");
        return;
      }

      // Make the decision to turn off or on the LED
      if (strcmp(json_parsed["switch"], "on") == 0) {
        Serial.println("Switch is on");
        powerOn();
      }
      else {
        Serial.println("Switch is off");
      }
    }
  }
  Serial.print("closing connection. ");
}


// setup
void setup() {
  pinMode(speakerOut, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(pir, INPUT);

  Serial.begin(115200);
  
  delay(10);
 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  
  Serial.println("WiFi connected");
  Serial.println("IP address: " + WiFi.localIP());
}

// PLay Tone
void playTone() {
 
 long elapsed_time = 0;
 if (tone_ > 0) { // if this isn't a Rest beat, while the tone has 
   //  played less long than 'duration', pulse speaker HIGH and LOW
   
   while (elapsed_time < duration) {
     digitalWrite(speakerOut,HIGH);
     delayMicroseconds(tone_ / 2);
     // DOWN
     digitalWrite(speakerOut, LOW);
     delayMicroseconds(tone_ / 2);
     // Keep track of how long we pulsed
     elapsed_time += (tone_);
   } 
 }
 else { // Rest beat; loop times delay
   for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
     delayMicroseconds(duration);  
   }                                
 }                                 
}

void powerOn(){
  val = digitalRead(pir);
     Serial.println(digitalRead(pir));
     if (val == HIGH) {
         if (pirState == LOW) {
           Serial.println("Motion detected!");
           digitalWrite(led, HIGH);
           sendMotionValue(1);
           pirState = HIGH;
           for (int i=0; i<MAX_COUNT; i++) {
             tone_ = melody[i];
             beat = beats[i];
         
             duration = beat * tempo; // Set up timing
         
             playTone(); 
             // A pause between notes...
             delayMicroseconds(pause);
         
             if (DEBUG) { // If debugging, report loop, tone, beat, and duration
               Serial.print(i);
               Serial.print(":");
               Serial.print(beat);
               Serial.print(" ");    
               Serial.print(tone_);
               Serial.print(" ");
               Serial.println(duration);
             }
           }
         } else if (pirState == HIGH) {
             digitalWrite(led, LOW);
             Serial.println("Motion ended");
             pirState = LOW;
           }
     } else {
       Serial.println("No motion detected!");
       digitalWrite(led, LOW);
     }
     delay(2000);
}


void loop() {
  Serial.print(hour());
  onOffSwitch();
}

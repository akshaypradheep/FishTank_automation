#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <Servo.h>
#include <FirebaseArduino.h>
#include "DHT.h"
#define DHTPIN D2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

Servo myservo;
int pos = 0;

#define FIREBASE_HOST "myextprojects.firebaseio.com"
#define FIREBASE_AUTH "953cVa49ZEJVG4oq400eCQrgeLk9NDJZR83S5TbI"
#define WIFI_SSID "SMART_HOME"
#define WIFI_PASSWORD "nodemcu8266"

void setup() {
  dht.begin();
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  myservo.attach(9);
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
  pinMode(13,OUTPUT);//relay
 
  }

void loop() {
    float t = dht.readTemperature();
  float f = dht.readHumidity();
  Firebase.setInt("t",t);
  Firebase.setInt("f",f);
  tmElements_t tm;
  if (RTC.read(tm)) {
    Serial.print(tm.Hour);
    Serial.print(":");
    Serial.print(tm.Minute);
    Serial.print(":");
    Serial.print(tm.Second);
    Serial.println(":");
    if(digitalRead(2)==HIGH){
      feed();
    }
    
    if(tm.Hour == 00 && tm.Minute == 00 && tm.Second ==30){
      feed();
    }
    if(tm.Hour == 00 && tm.Minute == 01 && tm.Second ==00){
      feed();
    }
    if(tm.Hour == 00 && tm.Minute == 01 && tm.Second ==30){
      feed();
    }
    if(tm.Hour == 00 && tm.Minute == 02 && tm.Second ==30){
      feed();
    }
    if(tm.Hour == 00 && tm.Minute == 3 && tm.Second ==00){
      digitalWrite(13,LOW);
    }
    if(tm.Hour == 00 && tm.Minute > 4 && tm.Second >00){
      digitalWrite(13,HIGH);
    }
    
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void feed(){
  int z = 0;
  while(z<5){
    myservo.write(90);                  
    delay(500);
    myservo.write(0);
    delay(500);
    z++;
  }
 myservo.write(0);
}

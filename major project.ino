#define BLYNK_TEMPLATE_ID "TMPL3dwLktbKz"
#define BLYNK_TEMPLATE_NAME "SMART ROBOT"
#define BLYNK_AUTH_TOKEN "eRyxzushLs5O1WN9qftoDt7Cl1h3vJOK"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid [] = "SVTECHNOLOGIES";
char pass [] = "Smart.23";

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h> //includes the servo library
Servo myservo;
LiquidCrystal_I2C Lcd(0x27,16,2);


// ESP32 Pin Definitions
#define ALCOHOL_SENSOR 34
#define ACCIDENT_SENSOR 25
#define EYE_SENSOR 26
#define ENGINE_RELAY 27
#define EMG_LIGHT 14
#define BUZZER 12
int pos = 90;
void setup()
{
 
  Serial.begin(115200);
myservo.attach(18);
  pinMode(ALCOHOL_SENSOR,INPUT);
  pinMode(ACCIDENT_SENSOR,INPUT);
  pinMode(EYE_SENSOR,INPUT);

  pinMode(ENGINE_RELAY,OUTPUT);
  pinMode(EMG_LIGHT,OUTPUT);
  pinMode(BUZZER,OUTPUT);

  digitalWrite(ENGINE_RELAY,LOW);
  digitalWrite(EMG_LIGHT,HIGH);
  digitalWrite(BUZZER,LOW);

  Lcd.begin();
  Lcd.backlight();

  Blynk.begin(auth, ssid, pass);
  myservo.write(0);
  Lcd.setCursor(0,0);
  Lcd.print("Please Wait...");
  Lcd.setCursor(0,1);
  Lcd.print("INITIALIZING...");
  delay(3000);
}

void loop()
{
  Blynk.run();
 

  int S,V,T;

  S = analogRead(ALCOHOL_SENSOR);
  V = digitalRead(ACCIDENT_SENSOR);
  T = digitalRead(EYE_SENSOR);

  Blynk.virtualWrite(V7,S);
  Blynk.virtualWrite(V8,V);
  Blynk.virtualWrite(V9,T);

  if(S >= 750)
  {
     myservo.write(0);
    Lcd.setCursor(0,0);
    Lcd.print("HIGH ALCOHOL");
    Lcd.setCursor(0,1);
    Lcd.print("ENGINE : OFF");

    digitalWrite(ENGINE_RELAY,HIGH);
    digitalWrite(EMG_LIGHT,HIGH);
    digitalWrite(BUZZER,HIGH);
  }

  else if(V == 0)
  {
     myservo.write(0);
    Lcd.setCursor(0,0);
    Lcd.print("ACCIDENT ALERT");
    Lcd.setCursor(0,1);
    Lcd.print("ENGINE : OFF");

    digitalWrite(ENGINE_RELAY,HIGH);
    digitalWrite(EMG_LIGHT,LOW);
    digitalWrite(BUZZER,HIGH);
  }

  else if(T == 0)
  {
    Lcd.setCursor(0,0);
    Lcd.print("DRIVER SLEEPY");
    Lcd.setCursor(0,1);
    Lcd.print("ENGINE : OFF");
    digitalWrite(BUZZER,HIGH);
    digitalWrite(EMG_LIGHT,HIGH);
    delay(300);
    digitalWrite(BUZZER,LOW);
    digitalWrite(EMG_LIGHT,LOW);
    delay(300);
    myservo.write(35); // write the turning angel
    delay(1000);
    digitalWrite(BUZZER,HIGH);
    digitalWrite(EMG_LIGHT,HIGH);
    delay(300);
    digitalWrite(BUZZER,LOW);
    digitalWrite(EMG_LIGHT,LOW);
    delay(300);
    digitalWrite(BUZZER,HIGH);
    digitalWrite(EMG_LIGHT,HIGH);
    delay(300);
    digitalWrite(BUZZER,LOW);
    digitalWrite(EMG_LIGHT,LOW);
    delay(300);
    digitalWrite(ENGINE_RELAY,HIGH);
    digitalWrite(BUZZER,HIGH);
    digitalWrite(EMG_LIGHT,LOW);
    delay(7000);
   
  }

  else
  {
     myservo.write(0); // write the turning angel
   
    Lcd.setCursor(0,0);
    Lcd.print("*SMART VEHICLE*");
    Lcd.setCursor(0,1);
    Lcd.print("MONITORING...");

    digitalWrite(ENGINE_RELAY,LOW);
    digitalWrite(EMG_LIGHT,HIGH);
    digitalWrite(BUZZER,LOW);
  }

  delay(500);
}
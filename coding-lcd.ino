//Library
#include <DHT.h>
#include <DHT_U.h>
#include <FastIO.h>
#include <I2CIO.h>
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SR.h>
#include <LiquidCrystal_SR2W.h>
#include <LiquidCrystal_SR3W.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//HDT11 Declaration
#define DHTPIN 12// pin 12
#define DHTTYPE DHT11//type dht11
DHT dht(DHTPIN, DHTTYPE);
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
const int buzzer = 8; //Buzzer pin 8
int Switch = 2; // Float Switch pin 2
int Fswitch = 1; //reads pushbutton status

void setup() 
{
Serial.begin(9600);
pinMode(Switch, INPUT_PULLUP);
pinMode(buzzer, OUTPUT); //buzzer as output
pinMode(10,OUTPUT);
dht.begin();// initialize the sensor
lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
lcd.backlight();//To Power ON the back light

}

void loop(){
Fswitch = digitalRead(Switch);
float h = dht.readHumidity();
float t = dht.readTemperature();
    
    lcd.clear();
    lcd.setCursor(0,0);// set the cursor on the first row and column
    //Humidity and Temperature
    lcd.print("H>");
    lcd.print(h);//print the humidity
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("T>");
    lcd.print(t);//print the temperature
    lcd.print("C");
    //Water Level
    lcd.setCursor(9,0);
    lcd.print("Wtr Lvl");
  if(Fswitch == LOW){
    lcd.setCursor(11,1);
    lcd.print("Low");
    //Buzzer
    //Beep Twice
    tone(buzzer, 500);//KHz
    delay(100);
    noTone(buzzer);//silent
    delay(100);
    tone(buzzer, 500);//KHz
    delay(100);
    noTone(buzzer);//silent
    delay(100);
    delay(1000);
    }
  else {  
    lcd.setCursor(10,1);
    lcd.print("Full");
    delay(100);
    }
  //LDR pin analog 0 & led pin digital 10
  if (analogRead(A0)>500){
    digitalWrite(10 ,HIGH);
  }
  if (analogRead(A0)<500){
    digitalWrite(10 ,LOW);
  }
lcd.clear();
}

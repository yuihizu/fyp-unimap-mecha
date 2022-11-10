//Declare DHT Sensor Module Library
#include <DHT.h>
#define DHT11Pin 12
#define DHTType DHT11
//OLED 128x64 Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
DHT HT(DHT11Pin,DHTType);
//OLED define adress
#define OLE_ADDR 0x3D
#define SSD1306_128_64
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
const int buzzer = 8; // Digital Pin 8 - Buzzer
int Switch = 2; // Digital Pin 2 - Float Switch
int Fswitch = 1; //Float Switch initial state

void setup() {
  Serial.begin(9600);
  HT.begin();
  //For OLED I2C
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
display.clearDisplay();
pinMode(Switch, INPUT_PULLUP);
pinMode(buzzer, OUTPUT);
}

void loop() {
  unsigned int AnalogValue;
  AnalogValue = analogRead(A0);
  Fswitch = digitalRead(Switch);
  monitordisplay();
  display.clearDisplay();
  display.fillRect(0, 0, 128, 8, WHITE);
  oledHeader();
  display.drawRect(0, 0, 128, 20, WHITE);
  display.drawLine(55, 0, 55, 8, BLACK);
  display.drawLine(55, 8, 55, 18, WHITE);
  oledUnit();
  oledWater();

if(Fswitch == LOW){
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(40,55);
  display.print("Low");
  soundBuzzer();
}
else{
  display.setTextSize(1);
  display.setTextColor(BLACK,WHITE);
  display.setCursor(40,55);
  display.print("Full");
}
if (AnalogValue > 500){
  oledMoon();
}
if (AnalogValue > 0 && AnalogValue < 500){
  oledSun();
}
display.display(); 
display.clearDisplay();
}

void monitordisplay(){  //Show Sensors reading in Microsoft Excel
  Serial.print(HT.readHumidity());
  Serial.print(",");
  Serial.print(HT.readTemperature());
  Serial.print(",");
  if (analogRead(A0)>500){
    Serial.print("Night");}
  if (analogRead(A0)<500){
    Serial.print("Day");
  }
  Serial.print(",");
  if (digitalRead(2)==0){
    Serial.print("LOW");
  }
  if (digitalRead(2)==1){
    Serial.print("FULL");
  }
  Serial.print(",");
  Serial.println();
  delay(1000);
}

void oledHeader() { //Tempeature and Humidity Header
 display.setTextSize(1);
 display.setTextColor(BLACK,WHITE);
 display.setCursor(1, 0);
 display.print("Humidity");
 display.setCursor(60,0);
 display.print("Temperature");
}
void oledUnit() {   //Temperature and Humidity Reading
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(8, 10);
  display.print(HT.readHumidity());
  display.print(" %");
  display.setCursor(78, 10);
  display.print(HT.readTemperature());
  display.print(" C"); 
}
void oledWater() {    //Float Switch
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,55);
  display.print(">Water");
}
void oledSun() { //Sun Symbol
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(80,55);
  display.print("Day");
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(108,50);
  display.print("*");
  display.drawLine(106, 56, 119, 55, WHITE); //y
  display.drawLine(106, 57, 119, 56, WHITE);
  display.drawCircle(113, 56, 5, BLACK);
}
void oledMoon() { //Moon Symbol
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(72,55);
  display.print("Night");
  display.fillCircle(114, 55, 6, WHITE);
  display.fillCircle(117, 55, 4, BLACK);
}
void soundBuzzer() { //Buzzer
  tone(buzzer, 500);
  delay(100);
  noTone(buzzer);
  delay(1000);
}

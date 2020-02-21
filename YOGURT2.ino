// TMP36 temp sensor output connected to analog input A0
unsigned int total = 0; // A/D readings
float tempC; // Celcius
float tempF; // Fahrenheit  //only using F

int BathTemp = 100; // change this as needed to calbrate with the thermometer 
int SSR = 1; //connect SSR to pin 6 to control the relay on and off

#include <Wire.h>       // Needed libary files
#include <LiquidCrystal_I2C.h> // Needed libary files

LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
 pinMode(6, OUTPUT); // initialize digital pin 6 as an output for SSR.
  lcd.init();                      // initialize the lcd 
  lcd.init();
  
  lcd.backlight();   
  lcd.setCursor(4,0);
  lcd.print("Yogurt Maker");  // Print a message to the LCD.
  lcd.setCursor(2,1);
  lcd.print("Bath set to ");   // Print a message to the LCD.
  lcd.setCursor(14,1);
  lcd.print(BathTemp);   // Print sensor temp to the LCD.
 

  analogReference(INTERNAL); // use the internal ~1.1volt reference | change to (INTERNAL1V1) for a Mega
  Serial.begin(9600);
}

void loop() {
  // read the sensor and average
  for (int x = 0; x < 64; x++) { // 64 readings for averaging keeps the value from jumping around
    total = total + analogRead(A0); // add each value
  }
  // temp conversion
  tempC = total * 0.001632 - 50.0; // value to tempC >>> change last two or three digits slightly to calibrate temp if needed, this is not the TMP36 calibration for bath water!!!<<<
  tempF = tempC * 1.8 + 32; // Celcius to Fahrenheit
  // fount this bit above on an Arduino forum talking about temp sensors, thanks to whoever the author was!

  Serial.print("The temperature is  ");
  //Serial.print(tempC, 1); // one decimal place
  //Serial.print(" Celcius  ");
  Serial.print(tempF, 0); // no decimal places
  Serial.println(" Fahrenheit");

lcd.setCursor(0,3);
lcd.print("Temp of water ");
lcd.setCursor(14,3);
  lcd.print(tempF);

lcd.setCursor(5,2);
  lcd.print("Heat is: ");
lcd.setCursor(14,2);
  lcd.print (SSR);
  
if (tempF < BathTemp) // looks at sensor and compaires to BathTemp
{
digitalWrite(6, HIGH);   // turn the heat ON (HIGH (5V) is the voltage level to relay control)
SSR = 1;
}
 
if (tempF >= BathTemp)
{
digitalWrite(6, LOW);   // turn the heat OFF( LOW or 0 is the voltage level)
SSR = 0;
}


  total = 0; // reset total to adverage sensor again 
  delay(500); // slows readings and loops forever
}

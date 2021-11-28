#include <LiquidCrystal.h>
LiquidCrystal lcd(7,8,10,11,12,13);
 
int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor  
int redLed = 5; 
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
int soundlow = 40;
int soundmedium = 500;
 
void setup ()  
{   
  pinMode (pinSignal, INPUT); // Set the signal pin as input   
  Serial.begin (9600); 
  lcd.begin(16,2); 
}  
   
void loop ()  
{  
  // Performs 128 signal readings   
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure; // Calculate the average value   
  Serial.print("Sound Level: ");
  lcd.print("Sound Level= ");
  Serial.println (level-33);  
  lcd.print(level-33);
  if(level-33<soundlow)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity= Low");
     digitalWrite(redLed,LOW);
  }
  if(level-33>soundlow && level-33<soundmedium)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity=Medium"); 
     digitalWrite(redLed,LOW); 
  }
  if(level-33>soundmedium)
  {
    lcd.setCursor(0,2);
    lcd.print("Intensity= High");   
    digitalWrite(redLed,HIGH); 
  }
  sum = 0 ; // Reset the sum of the measurement values  
  delay(200);
  lcd.clear();
}

 /*  
Modified on Nov 16, 2020
Modified by MehranMaleki from Arduino Examples
Home
*/

/*                                                                                                                                 
 * For this example, connect your X9C103P (or the like) as follows:
 * 1 - INC - Arduino pin 2
 * 2 - U/D - Arduino pin 3
 * 3 - VH  - 5V
 * 4 - VSS - GND
 * 5 - VW  - Output: Arduino pin A0 for analogRead
 * 6 - VL  - GND
 * 7 - CS  - Arduino pin 4
 * 8 - VCC - 5V
 */


#include <DigiPotX9Cxxx.h>
#include <Keypad.h>//Include library(library link in my blog)
const byte rows[4] = {2, 3, 4, 5};//connect to the row pinouts of the keypad
const byte cols[4] = {6, 7, 8, 9};//connect to the column pinouts of the keypad 

char keys[4][4] = { //create 2D arry for keys
  {'D', 'C', 'B', 'A'},
  {'#', '9', '6', '3'},
  {'0', '8', '5', '2'},
  {'*', '7', '4', '1'},

};

Keypad pad = Keypad(makeKeymap(keys), rows, cols, 4, 4);


DigiPot pot(2,3,4);
int num_Measure = 128 ; // Set the number of measurements   
int pinSignal = A0; // pin connected to pin O module sound sensor  
int redLed = 5; 
long Sound_signal;    // Store the value read Sound Sensor   
long sum = 0 ; // Store the total value of n measurements   
long level = 0 ; // Store the average value   
int soundlow = 40;
int soundmedium = 500;

void setup() {
   pinMode (pinSignal, INPUT); // Set the signal pin as input   
  Serial.begin (9600); 
}

void loop() 
{
  char myKey = pad.getKey();//get key and put in to the veriable
  if (myKey=='1')
  { //check condition
  Serial.println("eneabled smart audio system");
  Serial.println("category 1:home");
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure;
  if(level-33<soundlow)
  {
  for (int i=0; i<100; i++) 
  {
    pot.increase(1);
    Serial.println(analogRead(A0));
    delay(20);
  }
  }
  }
  else
  {
  for ( int i = 0 ; i <num_Measure; i ++)  
  {  
   Sound_signal = analogRead (pinSignal);  
    sum =sum + Sound_signal;  
  }  
 
  level = sum / num_Measure;
  if(level-33>soundmedium)
  {
     for (int i=0; i<100; i++) 
     {
      pot.decrease(1);
       Serial.println(analogRead(A0));
       delay(20); 
     }
   }
  }
   sum = 0 ; // Reset the sum of the measurement values  
   delay(200);
}

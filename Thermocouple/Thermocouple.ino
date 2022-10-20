#include <max6675.h>

//PINS FOR MAX6675

const int SO1   = 8;    
const int CS1   = 9;
const int CLK1  = 10;

const int SO2   = 5;    
const int CS2   = 6;
const int CLK2  = 7;

const int SO3   = 4;    
const int CS3   = 3;
const int CLK3  = 2;

MAX6675 T1(CLK1, CS1, SO1);
MAX6675 T2(CLK2, CS2, SO2);
MAX6675 T3(CLK3, CS3, SO3);

void setup()
{
  //PREPARE SERIAL INTERFACE
  Serial.begin(9600);

  //WAIT 1 SECOND
  delay(1000);
}

void loop()
{
  //SEND READING ON THE SERIAL MONITOR
   
  Serial.print(T1.readCelsius(),2);
  Serial.print(' ');
  Serial.print(T2.readCelsius(),2);
  Serial.print(' ');
  Serial.print(T3.readCelsius(),2);
  Serial.print('\n');

  //WAIT 0.5 SEG  BETWEEN LECTURES
  delay(500);
}

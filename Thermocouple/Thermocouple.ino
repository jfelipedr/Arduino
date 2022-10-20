#include <max6675.h>

//PINS FOR MAX6675

const int SO1 = 8;    
const int CS1 = 9;
const int CLK1 = 10;

const int SO2 = 5;    
const int CS2 = 6;
const int CLK2 = 7;

const int SO3 = 4;    
const int CS3 = 3;
const int CLK3 = 2;

MAX6675 T1(CLK1, CS1, SO1);
MAX6675 T2(CLK2, CS2, SO2);
MAX6675 T3(CLK3, CS3, SO3);

void setup()
{
  //PREPARAR LA INTERFAZ SERIAL
  Serial.begin(9600);

  //ESPERAR UN SEGUNDO
  delay(1000);
}

void loop()
{
  //SEND READING ON THE SERIAL MONITOR

  float TEMP1, TEMP2, TEMP3;
  
  TEMP1 = T1.readCelsius();
  TEMP2 = T2.readCelsius();
  TEMP3 = T3.readCelsius();
  
  Serial.print(TEMP1,2);
  Serial.print(' ');
  Serial.print(TEMP2,2);
  Serial.print(' ');
  Serial.print(TEMP3,2);
  Serial.print('\n');

  //WAIT 0.5 SEG  BETWEEN LECTURES
  delay(500);
}

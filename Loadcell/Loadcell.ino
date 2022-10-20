#include "HX711.h"

//PINS FOR HX711

const int DOUT_PIN  =  3;
const int SCK_PIN   =  2;
long READING        =  0;


//ANTI-DEBOUNCE
void anti_debounce( byte BUTTON )
{
  delay(100);
  while( digitalRead(BUTTON) ); //Anti-debounce
  delay(100);
}

void setup() 
{
  Serial.begin(9600);
  
  delay(1000);
}

void loop() 
{
  HX711 SCALE;
  
  SCALE.begin(DOUT_PIN, SCK_PIN);
  
  if ( SCALE.is_ready() ) 
  {
    READING = SCALE.read();
    Serial.print("Reading: ");
    Serial.println(READING);
  }
  else 
  {
    Serial.println("HX711 not found.");
  }

  delay(500);
}

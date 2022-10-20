/*---------------------------------------------------------------*/
/*---------------------------LIBRARIES---------------------------*/
/*---------------------------------------------------------------*/

#include <max6675.h> // THERMOCOUPLE
#include <HX711.h> // LOADCELL

/*----------------------------------------------------------------------------*/
/*---------------------------PINS & CONSTANTS SETUP---------------------------*/
/*----------------------------------------------------------------------------*/

long FUEL   =     0;
long THRUST =     0;
float TEMP1 =     0;
float TEMP2 =     0;
float TEMP3 =     0;

// TIME INTERVALS
unsigned long PREVIOUS_TIME1  =    0;
unsigned long PREVIOUS_TIME2  =    0;
unsigned long PREVIOUS_TIME3  =    0;
unsigned long CURRENT_TIME    =    0;

const long SEND_DATA    =   700;
const long OPEN_VALVE   =   655;
const long CLOSE_VALVE  =   1000;

const int DOUT_PIN1   =      A0; // LOADCELL FUEL
const int SCK_PIN1    =      A1; // LOADCELL FUEL
const int START       =      A2; // VALVE
const int STOP_VALVE  =      A3; // VALVE
const int TARE1       =      A4; // LOADCELL FUEL
const int TARE2       =      A5; // LOADCELL THRUST

const int VALVE     =        2;  // VALVE
const int SCK_PIN2  =        3;  // LOADCELL THRUST
const int DOUT_PIN2 =        4;  // LOADCELL THRUST
const int SO3       =        5;  // THERMOCOUPLE EXHAUST
const int CS3       =        6;  // THERMOCOUPLE EXHAUST
const int CLK3      =        7;  // THERMOCOUPLE EXHAUST

const int SO2   =            8;  // THERMOCOUPLE 2
const int CS2   =            9;  // THERMOCOUPLE 2
const int CLK2  =            10; // THERMOCOUPLE 2
const int SO1   =            11; // THERMOCOUPLE C.C.
const int CS1   =            12; // THERMOCOUPLE C.C.
const int CLK1  =            13; // THERMOCOUPLE C.C.

MAX6675 T1(CLK1, CS1, SO1);
MAX6675 T2(CLK2, CS2, SO2);
MAX6675 T3(CLK3, CS3, SO3);

HX711 SCALE1;
HX711 SCALE2;

/*------------------------------------------------------SETUP------------------------------------------------------*/
/*------------------------------------------------------SETUP------------------------------------------------------*/
/*------------------------------------------------------SETUP------------------------------------------------------*/

void setup()
{
  // PREPARE SERIAL INTERFACE
  Serial.begin(9600);
  //Serial.println("Setup");

  // SET ANALOG PINS FOR I/O AS A DIGITAL PIN
  pinMode(VALVE, OUTPUT);
  pinMode(START, INPUT);
  pinMode(STOP_VALVE, INPUT); 
   
  pinMode(TARE1,INPUT);
  pinMode(TARE2,INPUT);  
  pinMode(SCK_PIN1,INPUT);
  pinMode(DOUT_PIN1,INPUT);
  //Serial.println("pins finished");

  // VALVE   
  digitalWrite(VALVE, HIGH);
  digitalWrite(START, HIGH);
  digitalWrite(STOP_VALVE, HIGH);

  // LOADCELL
  digitalWrite(TARE1, HIGH);
  digitalWrite(TARE2, HIGH); 
  //Serial.println("valve & loadcell finished");

  // LOADCELL
  SCALE1.begin(DOUT_PIN1, SCK_PIN1); //FUEL
  SCALE2.begin(DOUT_PIN2, SCK_PIN2); //THRUST
  SCALE1.set_scale(-735.33);  // SCALE FACTOR FOR FUEL LOADCELL
  SCALE2.set_scale(-483);     // SCALE FACTOR FOR THRUST LOADCELL
  //SCALE1.tare(10);
  //SCALE2.tare(10);

  //Serial.println("ending...");
  delay(500); // WAIT
  //Serial.println("Setup finished");
}

/*------------------------------------------------------LOOP------------------------------------------------------*/
/*------------------------------------------------------LOOP------------------------------------------------------*/
/*------------------------------------------------------LOOP------------------------------------------------------*/

void loop()
{
  //Serial.println("Loop");
  CURRENT_TIME = millis();

  // THERMOCOUPLE

  // LOADCELL
  /*if ( SCALE1.is_ready() )
    FUEL = SCALE1.get_units(1);

  if ( SCALE2.is_ready() )
    THRUST = SCALE2.get_units(1);*/
    
  //Serial.println("load has been read");

  // LOADCELLS TARE
  if ( digitalRead(TARE1) == LOW )
  {
    Serial.println("Destarando FUEL...");
    SCALE1.tare(10);
  }

  if ( digitalRead(TARE2) == LOW )
  {
    Serial.println("Destarando THRUST...");
    SCALE2.tare(10);
  }

  // VALVE
  if( digitalRead(START) == LOW )
  {
    //Serial.println("Start ");
    
    while( digitalRead(STOP_VALVE) == HIGH )
    {
      if (digitalRead(STOP_VALVE) == LOW)
        break;
      
      //Serial.println("Open");
      digitalWrite(VALVE, LOW);
      
      Serial.print(T1.readCelsius(),2);
      Serial.print(" ");
      Serial.print(T2.readCelsius(),2);
      Serial.print(" ");
      Serial.print(T3.readCelsius(),2);
      Serial.print(" ");
      Serial.print(SCALE2.get_units(1),3);//THRUST
      Serial.print(" ");
      Serial.print(SCALE1.get_units(1),3);//FUEL 
      Serial.print("\n");
      delay(OPEN_VALVE);

      //Serial.println("Close");
      digitalWrite(VALVE, HIGH);
      
      Serial.print(T1.readCelsius(),2);
      Serial.print(" ");
      Serial.print(T2.readCelsius(),2);
      Serial.print(" ");
      Serial.print(T3.readCelsius(),2);
      Serial.print(" ");
      Serial.print(SCALE2.get_units(1),3);//THRUST
      Serial.print(" ");
      Serial.print(SCALE1.get_units(1),3);//FUEL
      Serial.print("\n");
      delay(CLOSE_VALVE);
    }    
    //Serial.println("Stopped");
  }
  
  //PREVIOUS_TIME1 = CURRENT_TIME;
  //PREVIOUS_TIME2 = CURRENT_TIME;

  /*if( Serial.read() == '1' )
  {
    PREVIOUS_TIME1 = CURRENT_TIME;
    PREVIOUS_TIME2 = CURRENT_TIME;
    PREVIOUS_TIME3 = CURRENT_TIME;
    while( digitalRead(STOP_VALVE) == HIGH )
    {
      if( Serial.read() == '8' )
      break;
      
      if ( CURRENT_TIME - PREVIOUS_TIME1 >= OPEN_VALVE )
      {
        Serial.println("Open");
        digitalWrite(VALVE, LOW);
        PREVIOUS_TIME1 = CURRENT_TIME;
        PREVIOUS_TIME2 = CURRENT_TIME;
      }

      if ( CURRENT_TIME - PREVIOUS_TIME2 >= CLOSE_VALVE )
      {
        Serial.println("Close");
        digitalWrite(VALVE, HIGH);
        PREVIOUS_TIME2 = CURRENT_TIME;
      }

      if ( CURRENT_TIME - PREVIOUS_TIME3 >= SEND_DATA )
      {
        Serial.print(TEMP1,2);
        Serial.print(" ");
        Serial.print(TEMP2,2);
        Serial.print(" ");
        Serial.print(TEMP3,2);
        Serial.print(" ");
        Serial.print(FUEL,3);
        Serial.print(" ");
        Serial.print(THRUST,3);
        Serial.print("\n");

        PREVIOUS_TIME3 = CURRENT_TIME;
      }
    }
    //Serial.println("Stopped");
  }*/

  //Serial.println("valve finished");

  // SEND READINGS
  /*if ( CURRENT_TIME - PREVIOUS_TIME3 >= SEND_DATA )
  {
    Serial.print(TEMP1,2);
    Serial.print(" ");
    Serial.print(TEMP2,2);
    Serial.print(" ");
    Serial.print(TEMP3,2);
    Serial.print(" ");
    Serial.print(SCALE2.get_units(1),3);
    //Serial.print(FUEL,3);
    Serial.print(" ");
    Serial.print(SCALE1.get_units(1),3);
    //Serial.print(THRUST,3);
    Serial.print("\n");

    PREVIOUS_TIME3 = CURRENT_TIME;
  }*/
  Serial.print(T1.readCelsius(),2);
  Serial.print(" ");
  Serial.print(T2.readCelsius(),2);
  Serial.print(" ");
  Serial.print(T3.readCelsius(),2);
  Serial.print(" ");
  Serial.print(SCALE2.get_units(1),3);//FUEL
  Serial.print(" ");
  Serial.print(SCALE1.get_units(1),3);//THRUST
  Serial.print("\n");
 
  delay(500);
  //Serial.println(millis());
}

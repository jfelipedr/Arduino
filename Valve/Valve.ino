#define START 2 
#define VALVE 7 
#define STOP_VALVE 0 

void setup () 
{
  //PREPARE SERIAL INTERFACE
  Serial.begin(9600);
  
  //LECTURE & WRITE PINS
  pinMode(START, INPUT);
  pinMode(STOP_VALVE, INPUT);
  pinMode(VALVE, OUTPUT);
  pinMode(13, OUTPUT); 

  delay(1000);
  Serial.print("Setup finished");
}

void loop()
{
  digitalWrite(START, HIGH);
  digitalWrite(STOP_VALVE, HIGH);
  //Mientras valve este HIGH la valvula estara CERRADA, por eso se comienza en high
  digitalWrite(VALVE, HIGH);
  
  if( digitalRead(START) == LOW )
  {
    Serial.println("Start ");
    
    while( digitalRead(STOP_VALVE) == HIGH )
    {
    Serial.println("Open");
    digitalWrite(VALVE, LOW);
    digitalWrite(13, LOW);
    digitalRead(STOP_VALVE);
    delay(900);

    Serial.println("Close");
    digitalWrite(VALVE, HIGH);
    digitalWrite(13, HIGH);
    digitalRead(STOP_VALVE);
    
    delay(1000);
    }
    
    Serial.println("Stopped");
  }
}

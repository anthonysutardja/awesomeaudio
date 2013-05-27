int READ_INTERVAL = 60; //Interval reading time -- 60ms
float SND_VEL = 340.0; //velocity of sound 340m/s

unsigned long timeStart;
unsigned long timeEnd;

unsigned long checkTimeStart;

unsigned long elapsedTime = 0;

boolean sent = false;
boolean highFound = false;
boolean lowFound = false;

int echoPin = 8;
int trigPin = 11;

void setup() {                
  //LED pin 
  pinMode(13, OUTPUT);
  
  //Digital read for echo output
  pinMode(echoPin, INPUT);
  
  //Echo trigger
  pinMode(trigPin, OUTPUT);
  
  //Initialize serial reading
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  //Send stage
  if (!sent){
    if (digitalRead(echoPin) == LOW){
      sendTrigger();
      checkTimeStart = millis();
    } else {
      //Serial.print("oops  ");
      delay(READ_INTERVAL);
    }
    
  }
  //Wait for high rise
  else if (!highFound){
    elapsedTime = millis() - checkTimeStart;
    
    if ( elapsedTime < 1000 ){
      if (digitalRead(echoPin) == HIGH){
        //Serial.print("Found high\t");
        timeStart = micros();
        highFound = true;
        checkTimeStart = millis();
      }
    } else{
      reset();
    } 
  }
  //Wait for high drop
  else if (!lowFound){
    elapsedTime = millis() - checkTimeStart;
    
    if ( elapsedTime < 1000 ){
      if (digitalRead(echoPin) == LOW){
        //Serial.print("Found low\t");
        timeEnd = micros();
        lowFound = true;
      }
    }else{
        reset();
    }
  }
  //Output stage
  else{
    output();
    reset();
    delay(READ_INTERVAL);
  }
}

/*  sendTrigger()
    Sends a 15 microsecond pulse to the tigger pin. */
void sendTrigger() {
  digitalWrite(trigPin, HIGH);
  delay(0.015); //Maintain trigger for 15 uS
  digitalWrite(trigPin, LOW);
  sent = true;
}

/*  output()
    Outputs microsecond time since start and distance to serial. */
void output(){
  unsigned long highTime = timeEnd-timeStart;
  Serial.print(micros());
  Serial.print(",");
  float distance = highTime * SND_VEL / (2 * 10000); //output cm
  Serial.print(distance);
  Serial.print("\n");
}

/*  reset()
    Resets the loop and discards all progress. */
void reset(){
  sent = false;
  highFound = false;
  lowFound = false;
  elapsedTime = 0;
}

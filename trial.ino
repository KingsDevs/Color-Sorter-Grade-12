#include <Servo.h>
Servo Cservo;
Servo Dservo;
Servo Pservo;

 int potpin = 0;
 int nm;
int PservoRUN = 1;
#define S0 4 
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8    
int frequency = 0;
int color=0;
//LED's
int rLed = 1;
int gLed = 2;
int bLed = 3;

int detectColor() {
  // activating red photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);//printing RED color frequency
  Serial.print("   ");
  delay(50);

   // activating blue photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  
  // activating green photodiodes to read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  // Reading the output frequency
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.print("   ");
  delay(50);

  delay(50);

//Readings are different for different setup
//change the readings according your project and readings detected
  if(R<36 & R>30 & G<=41 & G>=24){
    color = 1; // Red
    Serial.print("Detected Color is = ");
    Serial.println("RED");
  }
  
  if(R<37 & R>20 & G<28 & G>25){
    color = 2; // Green
      Serial.print("Detected Color is = ");
    Serial.println("GREEN");
  }
  
  if (G<29 & G>27 & B<22 &B>19){
    color = 3; // Blue
     Serial.print("Detected Color is = ");
    Serial.println("BLUE");
  }
  return color;  
}
void setup() {
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  //servo motors
  Pservo.attach(9);
  Dservo.attach(10);
  Cservo.attach(11);

  //LED
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT); 

}

void loop() {
  //Conveyor
  nm = analogRead(potpin);           
  nm = map(nm, 0, 1023, 0, 180);     
  Cservo.write(nm);                  
  delay(15);

   //initial position of Pservo
  Pservo.write(115);
  delay(600);
   if(PservoRUN == 1) {
    PservoRUN = 0;
    for(int i = 115; i > 65; i--) {
    Pservo.write(i);
    delay(2);
  }
 }
  
  switch (color) {
    case 1:
    Dservo.write(20);
    digitalWrite(rLed, HIGH);
    PservoRUN = 1;
    delay(1000);
    digitalWrite(rLed, LOW);
    break;

    case 2:
    Dservo.write(50);
    digitalWrite(gLed, HIGH);
    PservoRUN = 1;
    delay(1000);
    digitalWrite(gLed, LOW);
    break;

    case 3:
    Dservo.write(90);
    digitalWrite(bLed, HIGH);
    PservoRUN = 1;
    delay(1000);
    digitalWrite(bLed, LOW);
    break;
  }
}

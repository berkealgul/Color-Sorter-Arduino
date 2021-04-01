#include <Servo.h>
#include <LiquidCrystal.h>
#define S0 A0
#define S1 2
#define S2 3
#define S3 4
#define sensorOut 5
Servo topServo;
Servo bottomServo;
LiquidCrystal lcd(8,9,10,11,12,13,A1);
int frequency = 0;
int color=0;

//colors
int r,y,g,o;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  // Setting frequency-scaling to 20%
  digitalWrite(S0, HIGH);
  digitalWrite(S1, LOW);
  topServo.attach(6);
  bottomServo.attach(7);
  lcd.begin(16,2);
  Serial.begin(9600);
  updateLcd();
}


void loop() {

  for(int i = 180; i > 90; i--) {
    topServo.write(i);
    delay(20);
  }

   color = readColor();
  
   switch (color) {
    case 1:
    r++;
    bottomServo.write(20);
    break;
    case 2:
    o++;
    bottomServo.write(65);
    break;
    case 3:
    g++;
    bottomServo.write(110);
    break;
    case 4:
    y++;
    bottomServo.write(155);
    break;
    //default:
    //n++;
    //bottomServo.write(150);
  }
  
  updateLcd();
   for(int i = 90; i > 0; i--) {
    topServo.write(i);
    delay(20);
  }
 
  delay(200);
  for(int i = 0; i < 180; i++) {
    topServo.write(i);
    delay(5);
  }
  
  color=0;
  delay(2500);
}


int readColor() {
  // red
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int R = frequency;
  Serial.print("R= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  
  // green
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int G = frequency;
  Serial.print("G= ");
  Serial.print(frequency);
  Serial.print("  ");
  delay(50);
  
  // Blue
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int B = frequency;
  Serial.print("B= ");//printing name
  Serial.print(frequency);//printing RED color frequency
  Serial.println("  ");
  delay(50);
  
  if(R<77 & R>60 & G<130 & G>105){
    color = 1; // Red 
  }
  if(R<70 & R>50 & G<110 & G>90){
    color = 2; // Orange
  }
  if(R<100 & R>60 & G<95 & G>70){
    color = 3; // Green 
  }
  if(R<62 & R>45 & G<80 & G>65){
    color = 4; // Yellow 
  }
  
  return color;  
}

void updateLcd()
{
  lcd.setCursor(0,0);
  lcd.print("K");
  lcd.print(r);
  
  lcd.print(" T");
  lcd.print(o);

  lcd.print(" Y");
  lcd.print(g);

  lcd.print(" S");
  lcd.print(y);

   //lcd.print(" N");
   //lcd.print(n);
}

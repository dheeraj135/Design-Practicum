#define INDEX_SIZE 5        // size of pos[]
int currpos = 0;            //  currposition
int pos[INDEX_SIZE] = {0,7,14,21};  // relative positions 0-7 means full rotati
int index = 0;            // temp var for iteration
int dirPin[] = {13,3};     //dir pins for horizontal motor
int stepPin[] = {2,4};    // step pins for horizontal motor
int vdirPin[] = {5,7};   // dir pins for vertical motors
int vstepPin[] = {6,8};  // step pins of vertical motors
int sp = 2000;  // sleep for motor
int rotate = 30;  // num of rotations for each pos
float offset = 56;  //offset for outDir
float ratio = 1;    // pos to real distance
float disOut=0;      // distance between outer electrodes
float disIn = 5;    // distance between inner electrodes


float value3 = 0;
int value1 = 0;
int value2 = 0;
double voltage,voltage2;
const int transistorPin1 = 9;
const int grd1 = 10;
const int transistorPin2 = 11; 
const int grd2 =12; 
int start = 1;
//TODO: Potentiometer
//TODO: Code needs to be tweeked based on the real configuration
// of hardware.(Like directions, and offset,ratio etc.)

void setup()
{
  Serial.begin(9600);
  for(int i=0;i<2;i++)
  {
    pinMode(dirPin[i],OUTPUT);
    pinMode(vdirPin[i],OUTPUT); 
    pinMode(stepPin[i],OUTPUT);
    pinMode(vstepPin[i],OUTPUT);
    digitalWrite(dirPin[i],LOW);
    digitalWrite(stepPin[i],LOW);
    digitalWrite(vdirPin[i],LOW);
    digitalWrite(vstepPin[i],LOW);
  }
    pinMode(transistorPin1, OUTPUT);
  pinMode(grd2, OUTPUT);
pinMode(grd1, OUTPUT);
   pinMode(transistorPin2, OUTPUT);
  digitalWrite(transistorPin1,HIGH);
  digitalWrite(transistorPin2,HIGH);
  digitalWrite(grd1,HIGH);
  digitalWrite(grd2,HIGH);
}
void gotoPos(int a,int b,int m,int hold=0)
{
  int diff = a-b;
  //if(m) diff=-diff ???? Because motors can be working in Anti-
  if(diff<0) digitalWrite(dirPin[m],LOW),diff=-diff;
  else digitalWrite(dirPin[m],HIGH);
  
  digitalWrite(stepPin[m],LOW);
  for(int x = 0; x<rotate*diff;x++) {
    digitalWrite(stepPin[m],HIGH);
    delayMicroseconds(sp);
    digitalWrite(stepPin[m],LOW);
    delayMicroseconds(sp);
  }
  
//  if(hold)
//    digitalWrite(stepPin[m],HIGH);
  delay(1000);
  
}

void moveUpDown(int m, int a, int hold){
 if(a){
   digitalWrite(vdirPin[m],HIGH);
 } 
 else digitalWrite(vdirPin[m],LOW);
 digitalWrite(vstepPin[m],LOW);
 for(int i=0;i<700;i++)
 {
   digitalWrite(vstepPin[m],HIGH);
   delayMicroseconds(sp);
   digitalWrite(vstepPin[m],LOW);
   delayMicroseconds(sp);
 }
// if(hold) 
//   digitalWrite(vstepPin[m],HIGH);
 delay(1000);
}

void takeReading(int pos1){
//  int value1 = analogRead(A7);
//  int value2 = analogRead(A1);
//  int value3 = analogRead(A4);
//  value2 = value2-value3;
  disOut = pos1*ratio+offset;
  char str[1000];
  char temp1[100], temp2[100];
  dtostrf(disOut,0,4,temp1);
  dtostrf(disIn,0,4,temp2);
  digitalWrite(transistorPin1,HIGH);
    digitalWrite(grd1,HIGH);
  delay(200);
digitalWrite(transistorPin2,LOW);
digitalWrite(grd2,LOW);
  delay(200);
  
   value1 = analogRead(A1);
  delay(200);
  //value1 = value1*5.0/1023;
  // Serial.print(value1);
     digitalWrite(transistorPin2,HIGH);
    digitalWrite(grd2,HIGH);
    delay(200);
     digitalWrite(transistorPin1,LOW);
    digitalWrite(grd1,LOW);
   delay(200);
   digitalWrite(transistorPin2,HIGH);
    digitalWrite(grd2,HIGH);
//delay(500);
value2 = analogRead(A0);
 delay(200);
  sprintf(str,"%d %d %s %s",value1,value2,temp1,temp2);
  Serial.println(str);
  delay(100);
}


void loop()
{
//  Serial.println(start);
  if(start)
  {
//    Serial.println(start);
//    Serial.println(Serial.available());
//    while(Serial.available()==0);
//    Serial.println("YO");
  }
  moveUpDown(1,0,1);
  moveUpDown(0,0,1);
  gotoPos(pos[index],currpos,0);
  gotoPos(pos[index],currpos,1);
  currpos = pos[index];
  moveUpDown(1,1,0);
  moveUpDown(0,1,0);
  for(int i=0;i<20;i++){
    takeReading(currpos);
  }
//  digitalWrite(dirPin[1],LOW);
//  for(int x = 0; x<rotate*10;x++) {
//    digitalWrite(stepPin[1],HIGH);
//    delayMicroseconds(sp);
//    digitalWrite(stepPin[1],LOW);
//    delayMicroseconds(sp);
//  }
//  delay(1500);
//    digitalWrite(dirPin[1],HIGH);
//  for(int x = 0; x<rotate*10;x++) {
//    digitalWrite(stepPin[1],HIGH);
//    delayMicroseconds(sp);
//    digitalWrite(stepPin[1],LOW);
//    delayMicroseconds(sp);
//  }
//  delay(1500);
 // }
  index+=1;
  index%=INDEX_SIZE;
}

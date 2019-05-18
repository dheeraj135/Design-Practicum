#define INDEX_SIZE 9        // size of pos[]
int currpos = 0;            //  currposition
int pos[INDEX_SIZE] = {0,1,2,3,4,5,6,7,8};  // relative positions
int index = 0;            // temp var for iteration
int dirPin[] = {1,3};     //dir pins for horizontal motor
int stepPin[] = {2,4};    // step pins for horizontal motor
int vdirPin[] = {5,7};   // dir pins for vertical motors
int vstepPin[] = {6,8};  // step pins of vertical motors
int sp = 1000;  // sleep for motor
int rotate = 20;  // num of rotations for each pos
float offset = 20;  //offset for outDir
float ratio = 10;    // pos to real distance
float disOut=0;      // distance between outer electrodes
float disIn = 10;    // distance between inner electrodes

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
  }
}
void gotoPos(int a,int b,int m,int hold=0)
{
  int diff = a-b;
  //if(m) diff=-diff ???? Because motors can be working in Anti-
  if(diff<0) digitalWrite(dirPin[m],HIGH),diff=-diff;
  else digitalWrite(dirPin[m],LOW);
  
  digitalWrite(stepPin[m],LOW);
  for(int x = 0; x<rotate*diff;x++) {
    digitalWrite(stepPin[m],HIGH);
    delayMicroseconds(sp);
    digitalWrite(stepPin[m],LOW);
    delayMicroseconds(sp);
  }
  
  if(hold)
    digitalWrite(stepPin[m],HIGH);
  delay(1000);
  
}

void moveUpDown(int m, int a, int hold){
 if(a){
   digitalWrite(vdirPin[m],HIGH);
 } 
 else digitalWrite(vdirPin[m],LOW);
 digitalWrite(vstepPin[m],LOW);
 for(int i=0;i<rotate*7;i++)
 {
   digitalWrite(vstepPin[m],HIGH);
   delayMicroseconds(sp);
   digitalWrite(vstepPin[m],LOW);
   delayMicroseconds(sp);
 }
 if(hold) 
   digitalWrite(vstepPin[m],HIGH);
 delay(1000);
}

void takeReading(int pos){
  int value1 = analogRead(A7);
  int value2 = analogRead(A1);
  int value3 = analogRead(A4);
  value2 = abs(value2-value3);
  disOut = pos*ratio+offset;
  char *str;
  char *temp1, *temp2;
  dtostrf(disOut,0,4,temp1);
  dtostrf(disIn,0,4,temp2);
  sprintf(str,"%d %d %s %s",value1,value2,temp1,temp2);
  Serial.print(str);
  delay(100);
}


void loop()
{
  moveUpDown(1,1,1);
  moveUpDown(0,1,1);
  gotoPos(pos[index],currpos,0);
  gotoPos(pos[index],currpos,1);
  currpos = pos[index];
  moveUpDown(1,0,0);
  moveUpDown(0,0,0);
  for(int i=0;i<20;i++){
    takeReading(currpos);
  }
  index+=1;
  index%=INDEX_SIZE;
}
float value3 = 0;
float value1 = 0;
float value2 = 0;
double voltage,voltage2;

void setup(){
  Serial.begin(9600);
}

void loop(){
//  value1 = analogRead(A1);
//  delay(100);
  value2 = analogRead(A0);
//  delay(100);
//  value1 = value1*5.0/1023;
  value2 = value2*5.0/1023;
  //value3 = analogRead(A4);
  //value2 = abs(value2-value3);
//  Serial.println(value1);
//  Serial.print(" ");
  Serial.println(value2);
  delay(500);
}

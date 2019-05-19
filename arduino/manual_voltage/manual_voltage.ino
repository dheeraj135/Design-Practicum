int value3 = 0;
int value1 = 0;
int value2 = 0;
double voltage,voltage2;

void setup(){
  Serial.begin(9600);
}

void loop(){
  value1 = analogRead(A7);
  value2 = analogRead(A1);
  value3 = analogRead(A4);
  value2 = abs(value2-value3);
  Serial.print(value1);
  Serial.print(" ");
  Serial.println(value2);
  delay(500);
}



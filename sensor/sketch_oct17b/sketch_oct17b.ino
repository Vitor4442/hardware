#define temp 2000

void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.write('T');
  delay(100);
  while (Serial.available()){
    Serial.println(Serial.readString());
}

  delay(temp);

Serial.write('U');
  delay(100);
  while (Serial.available()){
    Serial.println(Serial.readString());
}
}

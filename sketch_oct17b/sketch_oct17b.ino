#define tmp 2000

void setup() {
  Serial.begin(19200); 
}

void loop() {
  Serial.write('A'); 
  delay(tmp);
  Serial.write('a');  
  delay(tmp);
  Serial.flush();
}

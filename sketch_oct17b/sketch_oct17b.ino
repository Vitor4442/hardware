#define TMP 2000 

void setup() {
  Serial.begin(19200);  
}

void loop() {
  Serial.write('A');
  delay(TMP);

  while (Serial.available() > 0) {
    Serial.read(); 
  }

  Serial.write('a');
  delay(TMP);

  while (Serial.available() > 0) {
    Serial.read(); 
  }
}

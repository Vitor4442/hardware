#define tmp 2000

void setup() {
  Serial.begin(19200); 
}

void loop() {
  Serial.write('A');  // Envia 'A' para o Escravo
  delay(tmp);
  Serial.write('a');  // Envia 'a' para o Escravo
  delay(tmp);
  Serial.flush();

  }

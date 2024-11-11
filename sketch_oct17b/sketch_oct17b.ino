#define tmp 2000

void setup() {
  Serial.begin(19200); 
}

void loop() {
  Serial.write('A');  // Envia 'A' para o Escravo
  delay(tmp);
  Serial.write('a');  // Envia 'a' para o Escravo
  delay(tmp);

  // Verifica se há dados enviados pelo escravo
  if (Serial.available() > 0) {
    // Lê a resposta enviada pelo escravo
    String resposta = Serial.readStringUntil('\n');
    Serial.print("Escravo respondeu: ");
    Serial.println(resposta);
  }
  
  Serial.flush();
}

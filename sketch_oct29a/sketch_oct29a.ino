#define led 13
int contador = 0;

void setup() {
  Serial.begin(19200); 
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);  // Garante que o LED inicie desligado
}

void loop() {
  if (Serial.available() > 0) {  
    char c = Serial.read();  
    digitalWrite(led, (c == 'A') ? HIGH : (c == 'a') ? LOW : LOW);
    contador++;
    imprimirASCII(c); 
  }
}


void imprimirASCII(char c) {
  int valorASCII = (int)c;  
  Serial.print("Caractere: ");
  Serial.print(c);
  Serial.print(" - ASCII: ");
  Serial.println(valorASCII);
  Serial.println(contador);
}

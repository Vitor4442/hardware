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
    imprimirHEXA(c); 
  }
}

void imprimirHEXA(char c) {
  int HEXtoASCIIdisplay = (int)c;  
  Serial.print("Caractere: ");
  Serial.print(c);
  Serial.print(" - Hexadecimal: 0x");  
  Serial.println(HEXtoASCIIdisplay, HEX);  
  Serial.println(contador);
}

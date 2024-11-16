#define led 13
int contador = 0;

void setup() {
  Serial.begin(19200); 
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW); 
}

void loop() {
  if (Serial.available() > 0) {  
    char c = Serial.read();

    digitalWrite(led, (c == 'A') ? HIGH : (c == 'a') ? LOW : LOW);

        int valorASCII = (int)c;
        int digito1, digito2;

    imprimir(valorASCII, digito1, digito2);

    
    contador++;
  }
}

void converterASCparadec(char c, int digito1, int digito2) {
  int valorASCII = (int)c;

  int dezena= valorASCII / 10;
  int unidade = valorASCII % 10;
  

  digito1  = (dezena <=9) ? (dezena + 48) : (dezena + 55);
  digito2 = (unidade <=9) ? (unidade + 48) : (unidade + 55);
}

void imprimir(int valorASCII, int digito1, int digito2) {
  Serial.print("Character ASCII: ");
  Serial.write(valorASCII);
  Serial.print("Valor em ASCII: ");
  Serial.write(digito1);
  Serial.write(digito2);
}



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
    converterASCparadec(c, digito1, digito2, 16);
    imprimir(valorASCII, digito1, digito2);

    contador++;
  }
}

void converterASCparadec(char c, int& digito1, int& digito2, int base) {
  if (base == 0) {
    base = 10; 
  }
  int valorASCII = (int)c;

  int dezena = valorASCII / base;
  int unidade = valorASCII % base;

  digito1 = (dezena <= 9) ? (dezena + 48) : (dezena + 55);
  digito2 = (unidade <= 9) ? (unidade + 48) : (unidade + 55);
}

void imprimir(int valorASCII, int digito1, int digito2) {
  Serial.print("Character ASCII: ");
  Serial.write(valorASCII);
  Serial.print(" Valor em ASCII: ");
  Serial.write(digito1);
  Serial.write(digito2);

  int contadorDigito1, contadorDigito2;
  converterASCparadec((char)contador, contadorDigito1, contadorDigito2, 16);

  Serial.print(" Valor do contador em HEX: ");
  Serial.write(contadorDigito1);
  Serial.write(contadorDigito2);
  Serial.println();
}



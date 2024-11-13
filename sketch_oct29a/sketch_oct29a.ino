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

    converterASCparadec(c);
    contador++;
  }
}


void converterASCparadec(char c) {

  int valorASCII = (int)c;

  int dezena = valorASCII / 10;
  int unidade = valorASCII % 10;

  char digito1 = '0' + dezena;
  char digito2 = '0' + unidade;

  Serial.print("Caractere: ");
  Serial.println(c); 

  Serial.print("Valor ASCII: ");
  Serial.println(valorASCII); 


  Serial.print("ASC dos digitos: ");
  Serial.write(dezena); 
  Serial.print(" e ");
  Serial.write( unidade );
}

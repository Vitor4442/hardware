#define led 13
int contador = 0;
#define tmp 2000

void setup() {
  // Inicializa a comunicação serial
  Serial.begin(19200); 
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);  // Garante que o LED inicie desligado
}

void loop() {
  // Verifica se há dados disponíveis na porta serial
  if (Serial.available() > 0) {  
    char c = Serial.read();  // Lê o próximo caractere
    
    // Controle do LED: acende se for 'A' ou apaga se for 'a'
    if (c == 'A') {
      digitalWrite(led, HIGH);
    } else if (c == 'a') {
      digitalWrite(led, LOW);
    }

    // Imprime o valor ASCII do caractere recebido e seus dígitos
    converterASCparadec(c);
    contador++;
  }

  // Parte para testar a comunicação serial e enviar os caracteres 'A' e 'a' com intervalo
  Serial.write('A'); 
  delay(tmp);
  Serial.write('a');  
  delay(tmp);
}

void converterASCparadec(char c) {
  // Converte o caractere para seu valor ASCII
  int valorASCII = (int)c;

  // Separa o valor ASCII em dezenas e unidades
  int dezena = valorASCII / 10;
  int unidade = valorASCII % 10;

  // Converte os números das dezenas e unidades para caracteres
  char digito1 = '0' + dezena;
  char digito2 = '0' + unidade;

  // Exibe as informações no monitor serial
  Serial.print("Caractere: ");
  Serial.println(c); 

  Serial.print("Valor ASCII: ");
  Serial.println(valorASCII); 


  Serial.print("ASC dos digitos: ");
  Serial.write(dezena); 
  Serial.print(" e ");
  Serial.write( unidade );
}

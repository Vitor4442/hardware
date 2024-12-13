#define MAX_REGISTROS 10
#define TEMP 2000
int indice = 0;
char respostas[MAX_REGISTROS][7]; 
int header1 = 0xEB;
int header2 = 0x90;


void setup() {
  Serial.begin(9600);
}

void loop() {
  
  enviarComando('t');
  delay(TEMP);
  receberResposta();

  enviarComando('u');
  delay(TEMP);
  receberResposta();

  enviarComando('a');
  delay(TEMP);
  receberResposta();

  enviarComando('c');
  delay(TEMP);
  receberResposta();


  delay(2000);
}

void enviarComando(char comando) {
  Serial.write(header1);
  Serial.write(header2);
  Serial.write(comando);

}

void receberResposta() {
  if (Serial.available() >= 6) {
    for (int i = 0; i < 6; i++) {
      respostas[indice][i] = Serial.read();
    }
    if (Serial.available() > 0) {
      respostas[indice][6] = Serial.read();
    }
    indice = (indice + 1) % MAX_REGISTROS;
  }
}

void exibirRespostas() {
  for (int i = 0; i < MAX_REGISTROS; i++) {
    Serial.print("Registro ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print("Header1=");
    Serial.write(respostas[i][0]);
    Serial.write(respostas[i][1]);
    Serial.print(" ");
    Serial.print("Temp=");
    Serial.write(respostas[i][2]);
    Serial.write(respostas[i][3]);
    Serial.print(" ");
    Serial.print("Umidade=");
    Serial.write(respostas[i][4]);
    Serial.write(respostas[i][5]);
    Serial.print(" ");
    Serial.print("Contador=");
    Serial.println(respostas[i][6]);
  }
}
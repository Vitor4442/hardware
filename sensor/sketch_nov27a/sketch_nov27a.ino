#include <DHT.h>
#define DHTPIN 2
#define DHTTYPE DHT22
#define ESTADO_1 1
#define ESTADO_2 2
#define ESTADO_3 3
#define ESTADO_4 4

DHT dht(DHTPIN, DHTTYPE);
char dados[6];
int indice = 0;
int contador = 0;
int ControlEstado = 0;

void converterASCparadec(int valor, char& digito1, char& digito2, int base) {
  if (base != 16) {
    Serial.println("Base inválida! Use apenas base 16.");
    return;
  }

  int dezena = valor / base;
  int unidade = valor % base;

  digito1 = (dezena <= 9) ? (dezena + '0') : (dezena - 10 + 'A');
  digito2 = (unidade <= 9) ? (unidade + '0') : (unidade - 10 + 'A');
}

void processarMensagem(char dado) {
  char umidDig1, umidDig2;
  char tempDig1, tempDig2;
  int umidade = dht.readHumidity();
  int temperatura = dht.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor!");
    return;
  }

  converterASCparadec(umidade, umidDig1, umidDig2, 16);
  converterASCparadec(temperatura, tempDig1, tempDig2, 16);

  char header1 = 'A';
  char header2 = 'B';

  switch (dado) {
    case 't':
      Serial.println("Enviando temperatura:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.write(tempDig1);
      Serial.write(tempDig2);
      break;
    case 'u':
      Serial.println("Enviando umidade:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.write(umidDig1);
      Serial.write(umidDig2);
      break;
    case 'a':
      Serial.println("Enviando td:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.write(umidDig1);
      Serial.write(umidDig2);
      Serial.write(tempDig1);
      Serial.write(tempDig2);
      break;
    case 'c':
      Serial.println("Enviando contador:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.print(contador);
      break;
    default:
      Serial.println("Comando inválido!");
      break;
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando leitura do DHT22...");
  dht.begin();
}

void loop() {
  if (Serial.available()) {
    char msg_tipo = Serial.read();

    switch (ControlEstado) {
      case ESTADO_1:
        ControlEstado = (msg_tipo == 0xEB) ? ESTADO_2 : 0;
        break;
      case ESTADO_2:
        ControlEstado = (msg_tipo == 0x90) ? ESTADO_3 : 0;
        break;
      case ESTADO_3:
        processarMensagem(msg_tipo);
        ControlEstado = 0;
        break;
      default:
        ControlEstado = 0;
        break;
    }
  }

  contador++;
  delay(2000);
}

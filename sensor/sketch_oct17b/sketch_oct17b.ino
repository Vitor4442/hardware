// === ARDUINO ESCRAVO ===
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
#define ESTADO_1 1
#define ESTADO_2 2
#define ESTADO_3 3
#define ESTADO_4 4
#define ESTADO_5 5

DHT dht(DHTPIN, DHTTYPE);
char sum = 0;
char proxima_leitura = 0;
char dados[6];
int indice = 0;
int contador = 0;
int ControlEstado = ESTADO_1;

// Função para converter decimal para ASCII hexadecimal
void converterASCparadec(int valor, char& digito1, char& digito2, int base) {
  int dezena = valor / base;
  int unidade = valor % base;
  digito1 = (dezena <= 9) ? (dezena + '0') : (dezena - 10 + 'A');
  digito2 = (unidade <= 9) ? (unidade + '0') : (unidade - 10 + 'A');
}

// Função para calcular checksum (soma simples)
byte calcularChecksum(char* dados, int tamanho) {
  byte checksum = 0;
  for (int i = 0; i < tamanho; i++) {
    checksum += dados[i];
  }
  return checksum;
}

void processarMensagem(char msg_tipo) {
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

  char payload[4] = { umidDig1, umidDig2, tempDig1, tempDig2 };
  byte checksum = calcularChecksum(payload, 4);

  char header1 = 0xEB;
  char header2 = 0x90;

  Serial.write(header1);
  Serial.write(header2);

  switch (msg_tipo) {
    case 't':
      Serial.write(tempDig1);
      Serial.write(tempDig2);
      break;
    case 'u':
      Serial.write(umidDig1);
      Serial.write(umidDig2);
      break;
    case 'a':
      Serial.write(umidDig1);
      Serial.write(umidDig2);
      Serial.write(tempDig1);
      Serial.write(tempDig2);
      break;
    case 'c':
      Serial.print(contador);
      break;
    default:
      Serial.println("Comando inválido!");
      return;
  }
  Serial.write(checksum); // Envia o checksum
}

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  if (Serial.available()) {
    byte dado_recebido = Serial.read();
    switch (ControlEstado) {
      case ESTADO_1:
        ControlEstado = (dado_recebido == 0xEB) ? ESTADO_2 : ESTADO_1;
        break;

      case ESTADO_2:
        ControlEstado = (dado_recebido == 0x90) ? ESTADO_3 : ESTADO_1;
        break;

      case ESTADO_3:
        proxima_leitura = dado_recebido;
        sum += dado_recebido;
        ControlEstado = ESTADO_4;
        break;

      case ESTADO_4:
        contador = dado_recebido;
        sum += dado_recebido;
        ControlEstado = ESTADO_5;
        break;

      case ESTADO_5:
        if (dado_recebido == sum) {
          processarMensagem(proxima_leitura);
        } else {
          Serial.println("Checksum inválido!");
        }
        ControlEstado = ESTADO_1;
        sum = 0;
        break;
    }
  }
  contador++;
  delay(2000);
}

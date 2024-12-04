#include <DHT.h>
#define MAX_REGISTROS 10
#define DHTPIN 2      
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);
char dados[MAX_REGISTROS][4];
int indice = 0;

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

void imprimir(int umidade, int temperatura) {
  char umidDig1, umidDig2;
  char tempDig1, tempDig2;

  converterASCparadec(umidade, umidDig1, umidDig2, 16);
  converterASCparadec(temperatura, tempDig1, tempDig2, 16);

  dados[indice][0] = umidDig1;
  dados[indice][1] = umidDig2;
  dados[indice][2] = tempDig1;
  dados[indice][3] = tempDig2;

  indice = (indice + 1) % MAX_REGISTROS; 

  Serial.println("\n=== Dados Armazenados ===");
  for (int i = 0; i < MAX_REGISTROS; i++) {
    Serial.print("Registro ");
    Serial.print(i);
    Serial.print(": Umidade= ");
    Serial.write(dados[i][0]);
    Serial.write(dados[i][1]);
    Serial.print(", Temperatura= ");
    Serial.write(dados[i][2]);
    Serial.write(dados[i][3]);
    Serial.println();
  }
  Serial.println("=========================\n");
}

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando leitura do DHT22...");
  dht.begin(); 
}

void loop() {
  delay(2000);

  int umidade = dht.readHumidity();
  int temperatura = dht.readTemperature();

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor!");
    return;
  }

  imprimir(umidade, temperatura);
}

#include <DHT.h>

#define DHTPIN 2      
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);


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

  Serial.print("Umidade em Hexadecimal: ");
  Serial.write(umidDig1);
  Serial.write(umidDig2);
  Serial.write('\n'); 

  Serial.print("Temperatura em Hexadecimal: ");
  Serial.write(tempDig1);
  Serial.write(tempDig2);
  Serial.write('\n'); 
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

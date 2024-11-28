#include <DHT.h>

#define DHTPIN 2      
#define DHTTYPE DHT22  

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando leitura do DHT22...");
  
  dht.begin(); 
}

void loop() {
  delay(2000);

  float umidade = dht.readHumidity();
  
  float temperatura = dht.readTemperature();
  
  float tempFahrenheit = dht.readTemperature(true);

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor!");
    return;
  }

  Serial.print("Umidade: ");
  Serial.print(umidade);
  Serial.println("%");

  Serial.print("Temperatura: ");
  Serial.print(temperatura);
  Serial.println("°C");

  Serial.print("Temperatura: ");
  Serial.print(tempFahrenheit);
  Serial.println("°F");
}
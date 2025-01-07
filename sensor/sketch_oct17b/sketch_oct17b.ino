#include <DHT.h>

#define DHTPIN 2                  // Pino de leitura do sensor DHT22
#define DHTTYPE DHT22             // Tipo do sensor
#define ESTADO_1 1                // Estado 1 do sistema
#define ESTADO_2 2                // Estado 2 do sistema
#define ESTADO_3 3                // Estado 3 do sistema
#define ESTADO_4 4                // Estado 4 do sistema

DHT dht(DHTPIN, DHTTYPE);       // Inicializa o objeto DHT
char dados[6];                  // Array para armazenar dados recebidos
int indice = 0;                 // Índice para navegação dos registros
int contador = 0;               // Contador de mensagens enviadas
int ControlEstado = ESTADO_1;   // Controle do estado do sistema

// Função para converter valor decimal para hexa
void converterASCparadec(int valor, char& digito1, char& digito2, int base) {
  if (base != 16) {
    Serial.println("Base inválida! Use apenas base 16.");
    return;
  }

  int dezena = valor / base;    // Calcula a dezena
  int unidade = valor % base;   // Calcula a unidade

  // Converte para o formato hexa
  digito1 = (dezena <= 9) ? (dezena + '0') : (dezena - 10 + 'A');
  digito2 = (unidade <= 9) ? (unidade + '0') : (unidade - 10 + 'A');
}

// Função para processar e enviar mensagens de acordo com o tipo
void processarMensagem(char msg_tipo) {
  char umidDig1, umidDig2;
  char tempDig1, tempDig2;

  int umidade = dht.readHumidity();  // Lê a umidade
  int temperatura = dht.readTemperature();  // Lê a temperatura

  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha ao ler o sensor!");
    return;
  }

  // Converte os valores para ASCII em base 16
  converterASCparadec(umidade, umidDig1, umidDig2, 16);
  converterASCparadec(temperatura, tempDig1, tempDig2, 16);

  char header1 = 0xEB;    // Cabeçalho 1
  char header2 = 0x90;    // Cabeçalho 2

  // Envia dados de acordo com o tipo da mensagem
  switch (msg_tipo) {
    case 't':  // Envia temperatura
      Serial.println("Enviando temperatura:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.write(tempDig1);
      Serial.write(tempDig2);
      break;
      
    case 'u':  // Envia umidade
      Serial.println("Enviando umidade:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.write(umidDig1);
      Serial.write(umidDig2);
      break;
      
    case 'a':  // Envia todos os dados (temperatura e umidade)
      Serial.println("Enviando todos os dados:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.write(umidDig1);
      Serial.write(umidDig2);
      Serial.write(tempDig1);
      Serial.write(tempDig2);
      break;
      
    case 'c':  // Envia contador
      Serial.println("Enviando contador:");
      Serial.write(header1);
      Serial.write(header2);
      Serial.print(contador);
      break;

    default:  // Comando inválido
      Serial.println("Comando inválido!");
      break;
  }
}

void setup() {
  Serial.begin(9600);      // Inicializa a comunicação serial a 9600 bps
  Serial.println("Iniciando leitura do DHT22...");
  dht.begin();             // Inicializa o sensor DHT22
}

void loop() {
  if (Serial.available()) {  // Verifica se há dados disponíveis para leitura
    byte dados = Serial.read() ;  // Lê um byte de dados
    Serial.print("Recebido: ");
    Serial.print(dados, HEX);         // Exibe o dado recebido
    Serial.print("Estado atual: ");
    Serial.println(ControlEstado);  // Exibe o estado atual

    switch (ControlEstado) {  // Controla os estados do sistema
      case ESTADO_1:
        // Se o dado recebido for 0xEB, passa para o estado 2
        ControlEstado = (dados == 0xEB) ? ESTADO_2 : ESTADO_1;
        break;

      case ESTADO_2:
        // Se o dado recebido for 0x90, passa para o estado 3
        ControlEstado = (dados == 0x90) ? ESTADO_3 : ESTADO_1;
        break;

      case ESTADO_3:
        processarMensagem(dados);  // Processa a mensagem de acordo com o tipo
        ControlEstado = ESTADO_4;  // Passa para o estado 4
        break;

      case ESTADO_4:
        Serial.println(dados);  // Exibe o dado recebido no estado 4
        ControlEstado = ESTADO_1;  // Volta ao estado 1
        break;

      default:
        break;
    }
  }
  
  contador++;  // Incrementa o contador
  delay(2000);  // Atraso de 2 segundos antes de repetir o loop
}

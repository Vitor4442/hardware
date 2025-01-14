#define MAX_REGISTROS 10       // Número máximo de registros a serem armazenados
#define TEMP_D 2000            // Tempo de delay entre os comandos (em milissegundos)

char sum = 0;
char tipo_mensagem[4] = {'t', 'u', 'a', 'c'};  // Corrigido para array de caracteres
int indice = 0;                // Índice para o registro atual
char respostas[7];             // Array para armazenar as respostas recebidas
int contador_m = 0;            // Contador para os comandos enviados
byte valorHex = 0xEB;          // Valor hexadecimal 1 para o comando
byte valorHex2 = 0x90;         // Valor hexadecimal 2 para o comando

void setup() {
  Serial.begin(9600);          // Inicializa a comunicação serial a 9600 bps
}

void loop() {
  for (int i = 0; i < 4; i++) {
    sum = 0;

    Serial.write(valorHex);
    delay(TEMP_D);

    Serial.write(valorHex2);
    delay(TEMP_D);

    Serial.write(tipo_mensagem[i]);
    sum += tipo_mensagem[i];  // Corrigido para somar o caractere correto
    delay(TEMP_D);
    receberResposta();

    // Envia comando baseado no contador_m e recebe a resposta
    Serial.println(contador_m);
    sum += contador_m;
    delay(TEMP_D);
    receberResposta();

    Serial.write(sum);
    delay(TEMP_D);
    receberResposta();

    contador_m++;  // Incrementa o contador para o próximo comando
  }

  exibirRespostas();  // Exibe as respostas após o loop
}

// Função para receber e armazenar as respostas
void receberResposta() {
  if (Serial.available() >= 6) {  // Verifica se há pelo menos 6 bytes disponíveis
    for (int i = 0; i < 6; i++) {
      respostas[i] = Serial.read();  // Lê a resposta byte a byte
    }
    if (Serial.available() > 0) {
      respostas[6] = Serial.read();  // Lê um byte extra se houver
    }
    indice = (indice + 1) % MAX_REGISTROS;  // Atualiza o índice de registros
  }
}

// Função para exibir as respostas armazenadas
void exibirRespostas() {
  for (int i = 0; i < MAX_REGISTROS; i++) {  // Exibe cada registro armazenado
    Serial.print("Registro ");
    Serial.print(i);
    Serial.print(": ");
    Serial.print("Header1=");
    Serial.write(respostas[0]);
    Serial.write(respostas[1]);
    Serial.print(" ");
    Serial.print("Temp=");
    Serial.write(respostas[2]);
    Serial.write(respostas[3]);
    Serial.print(" ");
    Serial.print("Umidade=");
    Serial.write(respostas[4]);
    Serial.write(respostas[5]);
    Serial.print(" ");
    Serial.print("Contador=");
    Serial.println(respostas[6]);
  }
}

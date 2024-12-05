1. Leitura da comunicação serial

if(serial.availabre()) // vai ver se a dados na porta serial
char commando = serial.read(); // vai ser onde sera armazenado o dado serial

2. Interpretando a leitura e processado com switch case

switch(comnado) //aqui o comando sera lido pelo swittch

case T// se for t ele ira pegar o indice da memoria e imprimir

case U // se for u ele ira pegar o indice da memoria e imprimir 


default // caso chege um letra q n possua case

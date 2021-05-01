/*

JOGO DA MEMORIA 



Pedro Dib @2021

inspirado em: http://jeknowledge.github.io/academy-articles/jogo-da-memoria
*/

int ledPins[] = {7,8,9,10,11,12};     // Array contendo os pinos dos leds
int numLeds = 6;                      // Quantos leds estão conectados, determina quantos leds são usados no jogo
int gameState = 0;                    // Estado atual do jogo
int lvl = 1;                          // Nível atual do jogo, sendo 0 - Início, 1 - Rodada e 2 - Game Over

void setup() {
  Serial.begin(9600);               // Inicia o serial
  for(int i = 0; i < numLeds; i++){ // Para cada led, configura o pino para output
    pinMode(ledPins[i], OUTPUT);
  } 
  randomSeed(analogRead(0));        // Inicia o estado atual do gerador de números aleatórios
}

void loop() {
  switch (gameState) {    // Gerencia o estado atual do jogo
    case 0: {
      /*
        Nesse estado, acontece os eventos:
          - Mostra a mensagem de boas vindas no serial;
          - Animação dos leds ciclo 5x;
          - Pisca os leds 2x;
          - Espera o input inicial do jogador atual;
          - Muda o estado do jogo para 1 - Rodada.
      */
      Serial.println("Bem vindo ao Jogo da Memória!");
      cicleLeds(5, 50);
      blinkLeds(2);
      Serial.println("Pressione qualquer tecla para começar!");
      readSerial();
      Serial.println("");
      gameState = 1;
      break;
    }
    case 1: {
      /*
        Nesse estado, acontece os eventos:
          - Mostra o nível atual;
          - Contagem antes de começar a rodada, mostrando sequencialmente as mensagems e piscando os leds;
          - Gera a sequência dos leds e pisca os leds correspondentes;
          - Depois de acabar de mostrar a sequência, espera a resposta do usuário;
          - Caso a resposta seja igual á sequência gerada:
            - Adiciona um ao nível atual;
            - Mostra a mensagem que o jogador acertou;
            - Animação dos leds ciclo 5x;
            - Pisca os leds 2x.
          - Caso a resposta não seja igual á sequência gerada:
            - Mostra a mensagem que o jogador errou;
            - Animação dos leds ciclo 5x, rápido;
            - Pisca os leds 2x;
            - Muda o estado do jogo para 2 - Game Over.
      */
      Serial.print("Nível ");
      Serial.println(lvl);
      Serial.println("Memorize...");
      blinkLeds(2);
      delay(500);
      Serial.println("O...");
      blinkLeds(2);
      delay(500);
      Serial.println("Padrão!");
      Serial.println("");
      String sequence = generateSequence(lvl * 2 + 1);
      String aswner = readSerial();
      //Serial.println(String("Desired: ") + sequence + String(" Received: ") + aswner);
      Serial.println("");
      if (aswner == sequence) {
        lvl++;
        Serial.println("Correto!");
        Serial.println("");
        cicleLeds(5, 50);
        blinkLeds(2);
        delay(500);
      } else {
        Serial.println("Erroooou :(");
        Serial.println("");
        cicleLeds(5, 25);
        blinkLeds(2);
        delay(500);
        gameState = 2;
      }
      break;
    }
    case 2: {
      /*
        Nesse estado, acontece os eventos:
          - Mostra a mensagem de Game Over;
          - Mostra quantas vezes o jogador acertou;
          - Animação dos leds ciclo 10x, rápido;
          - Muda o estado do jogo para 0 - Início
      */
      Serial.println("Game over");
      Serial.print("Você acertou ");
      Serial.print(lvl - 1);
      Serial.println(" Vezes!");
      Serial.println("");
      cicleLeds(10, 25);
      gameState = 0;
    }
  }
}

// Ciclo entre os leds, com delay entre cada digitalWrite
void cicleLeds(int times, int perLedDelay) {
  for (int j = 0; j < times; j++) {     // Repete n vezes
    for (int i = 0; i < numLeds; i++) { // Para cada led
      digitalWrite(ledPins[i], HIGH);   // Acende o led
      delay(perLedDelay);               // Espera o delay específicado
    }
    for (int i = 0; i < numLeds; i++) { // Para cada led
      digitalWrite(ledPins[i], LOW);    // Apaga o led
      delay(perLedDelay);               // Espera o delay específicado
    }
  }
}

// Pisca todos os leds de uma vez, sem delay entre cada digitalWrite
void blinkLeds(int times){
  for (int j = 0; j < times; j++) {     // Repete n vezes
    for (int i = 0; i < numLeds; i++) { // Para cada led
      digitalWrite(ledPins[i], HIGH);   // Acende o led
    }
    delay(100);                         // Espera 0,1 segundos
    for (int i = 0; i < numLeds; i++) { // Para cada led
      digitalWrite(ledPins[i], LOW);    // Apaga o led
    }
    delay(100);                         // Espera 0,1 segundos
  }
}

// Gera uma sequência de determinado tamanho
String generateSequence(int size) {
  String sequenceStr = "";                  // Sequência gerada
  
  for (int i = 0; i < size; i++) {          // Para o tamanho específicado
    int number = random(numLeds);           // Gera um número entre 0 - (Número de leds - 1) (o número máximo é descartado).
    sequenceStr += (number + 1);            // Adiciona o número para a sequência

    digitalWrite(ledPins[number], HIGH);    // Acende o respectivo led
    delay(500);                             // Espera meio segundo
    digitalWrite(ledPins[number], LOW);     // Apaga o respectivo led
    delay(500);                             // Espera meio segundo
  }
  
  return sequenceStr;
}

// Lê a porta serial
String readSerial(){
  Serial.println("Insira sua resposta: ");

  // Aguardar a resposta do usuario
  while (Serial.available() == 0)
  {}

  // Retorna o valor introduzido pelo utilizador no Serial Monitor
  if (Serial.available())
  {
    return Serial.readString();
  }
}

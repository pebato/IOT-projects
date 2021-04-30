/*

JOGO DA MEMORIA 



Pedro Dib @2021

inspirado em: http://jeknowledge.github.io/academy-articles/jogo-da-memoria
*/

String recebido;
String sequenciaNumerica = "";
int led;
long numeroGerado;
char stateGame = 0;
int sequencia;


void setup() {
  Serial.begin(9600);
  for(int led = 8; led <= 10; led++){
    pinMode(led, OUTPUT);
  } 
  randomSeed(analogRead(0));

}
void loop() {
  switch (stateGame) {
    case 0:
      Serial.println("INICIO");
      Serial.println("Comecar? (s/n)");
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo comecando...");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
    case 1:
      Serial.println("Nivel 1");
      geraSequencia(1000, 3); 
      leserial();
      if (recebido == sequenciaNumerica){
        stateGame = 2;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Errou!"); 
        piscaled(300,5);     
      }
      break;
    case 2:
      Serial.println("* Nivel 2 *");
      geraSequencia(1000, 5); 
      leserial();
      if (recebido == sequenciaNumerica){
        stateGame = 2;
        Serial.println("Parabens! proximo nivel.");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Errou!"); 
        piscaled(300,5);     
      }
      break;
    case 3:
      Serial.println("Game Over"); 
      piscaled(100,5);
      stateGame = 4;
      break;
    case 4:
      Serial.println("jogar novamente? (s/n)"); 
      leserial();
      if (recebido.equalsIgnoreCase("s")){
        stateGame = 1;
        Serial.println("Jogo comecando...");
        piscaled(1000,3);
      } else {
        stateGame = 3;
        Serial.println("Jogo nao iniciado"); 
        piscaled(300,5);     
      }
      break;
  }
}

void leserial(){

  Serial.println("Insira sua resposta");

  while (Serial.available() == 0)
  {}

  if (Serial.available())
  {
    recebido = Serial.readString();
  }
}

void piscaled(int tempo, int vezes){
  for(int i = 0;i < vezes; i++){
    for(int led = 8; led <= 10; led++){
      digitalWrite(led, HIGH);
    }
    delay(tempo);
    for(int led = 8; led <= 10; led++){
      digitalWrite(led, LOW);
    }
    delay(tempo);
  }
}

void geraSequencia (int tempo, int sequencia){
  int ordemLeds[sequencia];

  // Gerar sequencia aleatoria
  for (int i = 0; i < sequencia; i++){
    numeroGerado = random(1, 4);
    ordemLeds[i] = numeroGerado;
  }

  // Inicialmente, a String sequenciaNumerica é uma String vazia
  sequenciaNumerica = "";

  // Pisca os LEDs na sequencia gerada
  for (int j = 0; j < sequencia; j++){
    led = ordemLeds[j];
    if (led == 1){
      digitalWrite(8, HIGH);
      delay(tempo);
      digitalWrite(8, LOW);
      delay(tempo);
    }else if (led == 2){
      digitalWrite(9, HIGH);
      delay(tempo);
      digitalWrite(9, LOW);
      delay(tempo);
    }else if (led == 3){
      digitalWrite(10, HIGH);
      delay(tempo);
      digitalWrite(10, LOW);
      delay(tempo);
    }
    // Converte a lista numa String   
    sequenciaNumerica = sequenciaNumerica + led;
  }
}






#include <Ultrasonic.h>	// Bilbioteca do sensor ultrasônico

HC_SR04 sensorCapsula(4, 5); 	// Inicia o sensor do compartimento da cápsula de café
int servoCapsula = 9;			// Pino do servo do compartimento da cápsula de café

HC_SR04 sensorTamano(2, 3);	// Inicia o sensor do tamanho do café
int servoDispenser = 10;		// Pino do servo do dispensador de café

void setup() {
	Serial.begin(9600);		// Inicia o serial
	pinMode(servoCapsula, OUTPUT);	// Inicia o pino do servoCapsula como OUTPUT
	pinMode(servoDispenser, OUTPUT);	// Inicia o pino do servoDispenser como OUTPUT
}

void loop(){
	int capsulaSensorDist = sensorCapsula.distance();	// Lê a distância do sensor do compartimento da cápsula
	int tamanhoSensorDist = sensorTamano.distance();	// Lê a distância do sensor do tamanho do café
	
	if (capsulaSensorDist < 20) {		// Caso a distância detectada da cápsula seja menor que 20 cm
		servoPos(servoCapsula, 90);	// Abre o compartimento
		if (tamanhoSensorDist < 30) {			// Caso a distância detectada do tamanho do café seja menor que 30 cm
			servoPos(servoDispenser, 180);	// Café curto
		} else {								// Caso contrário
			servoPos(servoDispenser, 0);		// Café longo
		}
	} else {							// Caso contrário
		servoPos(servoCapsula, 0);	// Fecha o compartimento
		servoPos(servoDispenser, 90);	// Reseta o servo do dispensador de café
	}
	
	Serial.println(String("Distância cápsula: ") + capsulaSensorDist);
	Serial.println(String("Distância tamanho: ") + tamanhoSensorDist);
	
	delay(50);	// Espera 15 milisegundos
}

//Função que controla a posição do servo motor. 
void servoPos (int servo, int pos)
{
  int microPulso = map(pos, 0,180,1000,2000);
  digitalWrite(servo, HIGH);
  delayMicroseconds(microPulso);
  digitalWrite(servo, LOW);
  delay(10);                   
}




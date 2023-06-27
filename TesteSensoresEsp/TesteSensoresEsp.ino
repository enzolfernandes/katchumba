#include <Arduino.h>

    //infravermelhos
int infraTeste = 26;
//int infra1 = 25;
int leituraInfraTeste = 0;
//int leituraInfra1 = 0;
//int infra2 = 0;
//int infra3 = 0;

   //Configuração pwm da Camis
//const int freq = 30000; 
//const int pwmChannel = 0;
//const int pwmChannel2 = 1;
//const int resolution = 8;
//int dutyCycle = 100;
//int cicloTrabalho = 100;

void setup() {

    //setando as saidas
pinMode(infraTeste,INPUT);
//pinMode(infra1,INPUT);

Serial.begin(9600);

}

void loop() {
    //lendo e escrevendo os dados do infra

 leituraInfraTeste = analogRead(infraTeste);
 Serial.println(leituraInfraTeste);

delay(50);
  
// leituraInfra1 = analogRead(leituraInfra1);
// Serial.println(leituraInfra1);

// delay(1000);

}

// infra da direita ler branco e acionar os dois motores pra frente

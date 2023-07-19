#include <Arduino.h>

    //infravermelhos
int infraEsquerdo = 12;
int infraCE = 14;
int infraC = 27;
int infraCD = 26;
int infraDireito = 25;
//int infra1 = 25;
int leituraInfraEsquerdo = 0;
int leituraInfraCE = 0;
int leituraInfraC = 0;
int leituraInfraCD = 0;
int leituraInfraDireito = 0;
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
pinMode(infraEsquerdo,INPUT);
pinMode(infraCE,INPUT);
pinMode(infraC,INPUT);
pinMode(infraCD,INPUT);
pinMode(infraDireito,INPUT);
//pinMode(infra1,INPUT);

Serial.begin(115200);

}

void loop() {
    //lendo e escrevendo os dados do infra

 leituraInfraEsquerdo = analogRead(infraEsquerdo);
 Serial.print("Sensor Esquerdo: ");
 Serial.println(leituraInfraEsquerdo);
  leituraInfraCE = analogRead(infraCE);
  Serial.print("Sensor Centro Esquerdo: ");
 Serial.println(leituraInfraCE);
   leituraInfraC = analogRead(infraC);
     Serial.print("Sensor Centro: ");
 Serial.println(leituraInfraC);
   leituraInfraCD = analogRead(infraCD);
  Serial.print("Sensor Centro Direito: ");
 Serial.println(leituraInfraCD);
  leituraInfraDireito = analogRead(infraDireito);
  Serial.print("Sensor Direito: ");
 Serial.println(leituraInfraDireito);
 Serial.println("----------");
delay(500);
  
// leituraInfra1 = analogRead(leituraInfra1);
// Serial.println(leituraInfra1);

// delay(1000);

}

// infra da direita ler branco e acionar os dois motores pra frente

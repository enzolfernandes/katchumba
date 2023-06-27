 #include <Arduino.h>

// Motor A Esquerdo
int motorEsquerdoPin1 = 5; 
int motorEsquerdoPin2 = 18; 
int enableEsquedoPin = 19;

int teste = 0;

// Motor B Direito
int motorDireitoPin1 = 21; 
int motorDireitoPin2 = 22; 
int enableDireitoPin = 23;

//infravermelhos 
int infracentroDireita = 27;
int infracentro = 26;
int infracentroEsquerda = 25;
int infraDireita = 33;
int infraEsquerda = 32;

// Propriedades do PWM
const int freq = 1000;
const int pwmChannelEsquerdo = 0;
const int pwmChannelDireito = 1;
const int resolution = 8;

// Demais variaveis 
int erro = 0;
int marcaDir = 0;
int marcaEsq = 0;
int velocidadeMax = 60;
int velocidade_inicial = 80;

void setup() {
  // put your setup code here, to run once:
  
  PinMode(motorEsquerdoPin1, OUTPUT);
  PinMode(motorEsquerdoPin2, OUTPUT);
  PinMode(motorDireitoPin1, OUTPUT);
  PinMode(motorDireitoPin2, OUTPUT);

  PinMode(infraCentroDireita, INPUT);
  PinMode(infraCentro, INPUT);
  PinMode(infraCentroEsquerda, INPUT);
  PinMode(infraDireita, INPUT);
  PinMode(infraEsquerda, INPUT);

  PinMode(enableEsquedoPin, OUTPUT);
  PinMode(enableDireitoPin, OUTPUT);

  ledcSetup(pwmChannelEsquerdosquerdo, freq, resolution);
  ledcSetup(pwmChannelD, freq, resolution);
  
  ledcAttachPin(enableEsquedoPin, pwmChannelEsquerdosquerdo);
  ledcAttachPin(enableDireitoPin, pwmChannelD);

  delay(1000);

// torque inicial
  digitalWrite(motorEsquerdoPin1, HIGH);
  digitalWrite(motorEsquerdoPin2, LOW);
  ledcWrite(pwmChannelEsquerdo, velocidade_inicial);

  digitalWrite(motorDireitoPin1, HIGH);
  digitalWrite(motorDireitoPin2, LOW);
  ledcWrite(pwmChannelDireito, velocidade_inicial);
  delay(500);

}

void leituraSensores(){

  leituraInfra[centroDireita] = analogRead(infraCentroDireita);
  leituraInfra[centro] = analogRead(infraCentro);
  leituraInfra[centroEsquerda] = analogRead(infraCentroEsquerda); 
  leituraInfra[Direita] = digitalRead(infraDireita);
  leituraInfra[Esquerda] = digitalRead(infraEsquerda);
}

void leituraMarcas(){
  if(leituraInfra[Direita] == 1){
    marcaDir = marcaDir + 1;
  }
  if(leituraInfra[Esquerda] == 1){
    marcaEsq = marcaEsq + 1; 
  }
}

int leituraErro(){

  // Caso 000 111 000
  if(200 <= leituraInfra[centroDireita] <= 600 && 3200 <= leituraInfra[centro] <= 4000 && 200 <= leituraInfra[centroEsquerda] <= 600){
    erro = 0;
  }
  // Caso 000 011 100
  if(200 <= leituraInfra[centroDireita] <= 600 && 2600 <= leituraInfra[centro] <= 3900 && 1000 <= leituraInfra[centroEsquerda] <= 2400){
    erro = 1;
  }
  // Caso 000 001 110
  if(200 <= leituraInfra[centroDireita] <= 600 && 1300 <= leituraInfra[centro] <= 2000 && 1900 <= leituraInfra[centroEsquerda] <= 3500){
    erro = 2;
  }
  // Caso 000 000 111
  if(200 <= leituraInfra[centroDireita] <= 600 && 200 <= leituraInfra[centro] <= 600 && 3200 <= leituraInfra[centroEsquerda] <= 4000){
    erro = 3;
  }
  // Caso 000 000 011
  if(200 <= leituraInfra[centroDireita] <= 600 && 200 <= leituraInfra[centro] <= 600 && 2600 <= leituraInfra[centroEsquerda] <= 3900){
    erro = 4;
  }
  // Caso 000 000 001
  if(200 <= leituraInfra[centroDireita] <= 600 && 200 <= leituraInfra[centro] <= 600 && 1300 <= leituraInfra[centroEsquerda] <= 2000){
    erro = 5;
  }

  // Caso 001 110 000
  if(1300 <= leituraInfra[centroDireita] <= 2000 && 1900 <= leituraInfra[centro] <= 3500 && 200 <= leituraInfra[centroEsquerda] <= 500){
    erro = -1;
  }
  // Caso 011 100 000
  if(2600 <= leituraInfracentroDireita] <= 3900 && 1000 <= leituraInfra[centro] <= 2400 && 200 <= leituraInfra[centroEsquerda] <= 600){
    erro = -2;
  }
  // Caso 111 000 000
  if(3200 <= leituraInfra[centroDireita] <= 4000 && 200 <= leituraInfra[centro] <= 600 && 200 <= leituraInfra[centroEsquerda] <= 600){
    erro = -3;
  }
  // Caso 011 000 000
  if(2600 <= leituraInfra[centroDireita] <= 3900 && 200 <= leituraInfra[centro] <= 600 && 200 <= leituraInfra[centroEsquerda] <= 600){
    erro = -4;
  }
  // Caso 100 000 000
  if(1000 <= leituraInfra[centroDireita] <= 2400 && 200 <= leituraInfra[centro] <= 600 && 200 <= leituraInfra[centroEsquerda] <= 600){
    erro = -5;
  }
  if(1300 <= leituraInfra[centroDireita] <= 2000 && 1300 <= leituraInfra[centro] <= 2000 && 1300 <= leituraInfra[centroEsquerda] <= 2000){
    erro = 0;
  }
  return erro;
}

void setMotores(int esq, int dir){

  // if(marcaEsq%2 == 0){

    digitalWrite(motorEsquerdoPin1, HIGH);
    digitalWrite(motorEsquerdoPin2, LOW);
    ledcWrite(pwmChannelEsquerdo, dir);

    digitalWrite(motorDireitoPin1, HIGH);
    digitalWrite(motorDireitoPin2, LOW);
    ledcWrite(pwmChannelDireito, esq);
    delay(90);

    // delay(90);
  
  }
  
void marcas(){
  if(marcaEsq%2 != 0){
    // Curvas
    if(erro > 0){
      // curva para a Direita

    }
    else{
      // curva para a Esquerda

    }
  }

  if(marcaDir == 2){
    // parar o seguidor
    for(int i = 1; i<0; i=i-10){
  
    digitalWrite(motorEsquerdoPin1, HIGH);
    digitalWrite(motorEsquerdoPin2, LOW);
    ledcWrite(pwmChannelEsquerdo, i);

    digitalWrite(motorDireitoPin1, HIGH);
    digitalWrite(motorDireitoPin2, LOW);
    ledcWrite(pwmChannelDireito, i);

    delay(50);

    }
  }
} 

void curvas(){
  
  // correção para a direita
  if (erro == 0){
    setMotores(velocidadeMax, velocidadeMax);
  }
  if (erro == 1){
    setMotores(velocidadeMax, 0.7 * velocidadeMax);
  }
  if (erro == 2){
    setMotores(velocidadeMax, 0.6 * velocidadeMax);
  }
  if (erro == 3){
    setMotores(velocidadeMax, velocidadeMax * 0.5);
  }
  if (erro == 4){
    setMotores(velocidadeMax, velocidadeMax*0.45);
  }
  if (erro == 5){
    setMotores(velocidadeMax, velocidadeMax * 0.4);
  }

  // Correção para a esquerda
  if (erro == -1){
    setMotores(velocidadeMax * 0.7, velocidadeMax);
  }
  if (erro == -2){
    setMotores(velocidadeMax * 0.6, velocidadeMax);
  }
  if (erro == -3){
    setMotores(velocidadeMax * 0.5, velocidadeMax);
  }
  if (erro == -4){
    setMotores(velocidadeMax * 0.45, velocidadeMax);
  }
  if (erro == -5){
    setMotores(velocidadeMax * 0.4, velocidadeMax);
  }

}

void loop() {

  leituraSensores();
  leituraMarcas();
  leituraErro();
  curvas();

}
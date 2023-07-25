// ! Modos
//* Enquanto a linha abaixo for um comentário, a referente parte não será compilada
 #define _DEBUG_

#include <Arduino.h>

// Constantes para ajuste do controle
constexpr const short baseSpeed = 155; // Resolução do Arduino: 8 bits
                                       // Resolução do ESP32: 10 bits
 //definindo velocidades
short speedLeft = 235;
short speedRight = baseSpeed;
constexpr const float turnRatio = 0.2;
short black  = 2999; //
short blackCL = 0; //
short blackCR = 0; //
constexpr const short white  = 3000; //
 //
short lapMarker = 0;
short curve;

// Variáveis para controle do estado do sensor de marcação
bool rightSensorDetected = false;
bool leftSensorDetected = false;

// Definição dos pinos dos sensores e dos motores
constexpr const short sensorCenterLeft = 14;
constexpr const short sensorCenter = 27;
constexpr const short sensorCenterRight = 26;

constexpr const short sensorRight = 25;
constexpr const short sensorLeft = 12;

constexpr const short motorLeftA = 22;
constexpr const short motorLeftB = 23;
constexpr const short motorLeftEnable = 4;

constexpr const short motorRightA = 32;
constexpr const short motorRightB = 35;
constexpr const short motorRightEnable = 33;

#include "functions.cpp"

void setup()
{
#ifdef _DEBUG_
  Serial.begin(115200);
#endif

  // Configuração dos pinos dos sensores como entrada
  pinMode(sensorCenterLeft, INPUT);
  pinMode(sensorCenter, INPUT);
  pinMode(sensorCenterRight, INPUT);
  pinMode(sensorRight, INPUT);
  pinMode(sensorLeft, INPUT);

  // Configuração dos pinos dos motores como saída
  pinMode(motorLeftA, OUTPUT);
  pinMode(motorLeftB, OUTPUT);
  pinMode(motorLeftEnable, OUTPUT);
  pinMode(motorRightA, OUTPUT);
  pinMode(motorRightB, OUTPUT);
  pinMode(motorRightEnable, OUTPUT);

  delay(1000);
}

void loop()
{

  

  blackCL = black;
  blackCR = black;

  // Leitura dos sensores
  short sensorCenterLeftValue = analogRead(sensorCenterLeft);
  short sensorCenterValue = analogRead(sensorCenter);
  short sensorCenterRightValue = analogRead(sensorCenterRight);
  short sensorRightValue = analogRead(sensorRight);
  short sensorLeftValue = analogRead(sensorLeft);

#ifdef _DEBUG_
  Serial.println("---------");

  Serial.print("sensorCenterLeftValue: ");
  Serial.println(sensorCenterLeftValue);
  Serial.print("sensorCenterValue: ");
  Serial.println(sensorCenterValue);
  Serial.print("sensorCenterRightValue: ");
  Serial.println(sensorCenterRightValue);

  Serial.println();
#endif

    //define um novo minimo se o central estiver lendo branco
  if (sensorCenterValue > 3500 && sensorCenterLeftValue < 1500){

      blackCL = sensorCenterLeftValue;

  }

  if (sensorCenterLeftValue > 3500 && sensorCenterRightValue < 1500){

      blackCR = sensorCenterRightValue;

  }

#ifdef _DEBUG_
  Serial.print("black: ");
  Serial.println(black);

  Serial.println();

  Serial.print("blackCL: ");
  Serial.println(blackCL);

  Serial.println();

  Serial.print("blackCR: ");
  Serial.println(blackCR);

  Serial.println();
#endif

  //parar robo 
  if ((sensorLeftValue > white) && (sensorRightValue < black))  //troquei right com left pq a faixa de parada (lap) é a da esquerda, a da direita é apenas curva
  {
    lapMarker = lapMarker + 1;
  }
  else if (lapMarker >= 2)
  {
    stopRobot();
  }

#ifdef _DEBUG_
  Serial.print("lapMarker: ");
  Serial.println(lapMarker);

  Serial.println();
#endif

  // Verificação se o robô está na linha com os sensores centrais
 // bool onTrack = (sensorCenterLeftValue > white  && sensorCenterValue > white && sensorCenterRightValue > white);

    bool onTrack = (sensorCenterLeftValue > blackCL && sensorCenterValue > white && sensorCenterRightValue > blackCR); //talvez mudar o white e mudar para um valor especifico dos sensores laterais resolva

  // Cálculo do erro
 // float error = sensorCenterValue - ((sensorCenterLeftValue + sensorCenterRightValue) / 2);

//ajuste grosso

   short errorcenterleft = sensorCenterLeftValue / sensorCenterValue;
   short errorcenterright = sensorCenterRightValue / sensorCenterValue;
   short errorcenterLR = errorcenterleft / errorcenterright;
   short errorcenterRL = errorcenterright / errorcenterleft;  

if(sensorCenterValue != white ){

        if(errorcenterleft > 1){

              speedLeft = baseSpeed;
              speedRight =  baseSpeed * errorcenterLR;

        }else if(errorcenterright > 1){

          speedLeft = baseSpeed * errorcenterRL;
          speedRight = baseSpeed;
        }else{

    speedLeft = 255; speedRight = 0;


}
}



//ajuste fino
  short errorL = sensorCenterValue / sensorCenterLeftValue;
  short errorR = sensorCenterValue / sensorCenterRightValue;
  short errorLR = errorL/errorR;
  short errorRL = errorR/errorL;

// ajuste fino
  if (errorLR != 1){
      
   if(errorLR > 1){ //ta mais pra direita; acelera motor direito e retarda motor esquerdo

      short speedLeft = baseSpeed;
      short speedRight = baseSpeed/errorLR;

   }  

 else{  //ta mais pra esquerda; aceleta motor esquerdo e retarda motor direito

    short speedLeft = baseSpeed/errorRL;
    short speedRight = baseSpeed;
  }
  }else{ //igual a 1

      short speedLeft  = baseSpeed;
      short speedRight = baseSpeed;

  } 


  
    
  
short speedLeft  = baseSpeed;
short speedRight = baseSpeed;

   // Limitação da velocidade dos motores
  speedLeft = constrain(speedLeft, 0, baseSpeed);
  speedRight = constrain(speedRight, 0, baseSpeed);

  // Cálculo da correção para manter o robô na linha
 // float correction = error * turnRatio;
  // Atualização da velocidade dos motores
  //short speedLeft = baseSpeed - correction;
  //short speedRight = baseSpeed - correction;



  // Controle dos motores
  controlMotor1(speedLeft);
  controlMotor2(speedRight);

#ifdef _DEBUG_
  Serial.print("onTrack: ");
  Serial.println(onTrack);

  Serial.print("errorR: ");
  Serial.println(errorR);

  Serial.print("errorL: ");
  Serial.println(errorL);

  Serial.print("errorLR: ");
  Serial.println(errorLR);

//  Serial.print("correction: ");
//  Serial.println(correction);

  Serial.print("speedLeft: ");
  Serial.println(speedLeft);
  Serial.print("speedRight: ");
  Serial.println(speedRight);

  Serial.println();
#endif

#ifdef _DEBUG_
  delay(500);
#endif
}
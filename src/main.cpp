///// TODO: Ajustar motores de forma unilateral
/*
Como?
- Erro Direto corrige motor esquerdo somente
- Erro Esquerdo corrige motor esquerdo somente
*/

// ! Modos
//* Enquanto a linha abaixo não for um comentário, a referente parte não será compilada
#define _DEBUG_

#include <Arduino.h>

// Constantes para ajuste do controle
constexpr const unsigned int baseSpeed = 65535; // Resolução da GPIO ESP32: 16 bits (0 a 65535)
constexpr const float turnRatio = 0.2;
constexpr const short white = 3800;
constexpr const short black = 3799;
short lapMarker = 0;

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
}

void loop()
{
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

  if ((sensorRightValue >= white) && (sensorLeftValue <= black))
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

  // Verificação se o robô está na linha com o sensor central
  bool onTrack = (sensorCenterValue >= white);

  // Cálculo de diferença
  /*
  -: que que sejam o mais próximo ambos os valores
  +: Quero que eles sejam o mais diferentes o possível
  */
  float differenceLeft = (sensorCenterValue - sensorCenterLeftValue);
  float differenceRight = (sensorCenterValue - sensorCenterRightValue);
  float differenceCenter = (sensorCenterValue - ((sensorCenterLeftValue + sensorCenterRightValue) / 2)); // Talvez não tenha utilidade

  // Cálculo da correção para manter o robô na linha
  // Sensores center left e center right estão muito longe do centro logo a correção não pode ter um valor significativo
  float correctionLeft = differenceLeft * turnRatio;
  float correctionRight = differenceRight * turnRatio;
  float correctionCenter = differenceCenter * turnRatio; // Talvez não tenha utilidade

  // Atualização da velocidade dos motores
  // Quero que ele se afaste do branco, logo o motor oposto deve agir caso ele se aproxime
  unsigned int speedLeft = baseSpeed - correctionRight;
  unsigned int speedRight = baseSpeed - correctionLeft;

  // Limitação da velocidade dos motores
  speedLeft = constrain(speedLeft, 0, baseSpeed);
  speedRight = constrain(speedRight, 0, baseSpeed);

  // Controle dos motores
  controlMotor1(speedLeft);
  controlMotor2(speedRight);

#ifdef _DEBUG_
  Serial.print("onTrack: ");
  Serial.println(onTrack);

  Serial.println();

  Serial.print("differenceLeft: ");
  Serial.println(differenceLeft);
  Serial.print("differenceRight: ");
  Serial.println(differenceRight);
  Serial.print("differenceCenter: ");
  Serial.println(differenceCenter);

  Serial.println();

  Serial.print("correctionLeft: ");
  Serial.println(correctionLeft);
  Serial.print("correctionRight: ");
  Serial.println(correctionRight);
  Serial.print("correctionCenter: ");
  Serial.println(correctionCenter);

  Serial.println();

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
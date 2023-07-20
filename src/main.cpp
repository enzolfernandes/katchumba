// ! Modos
//* Enquanto a linha abaixo não for um comentário, a referente parte não será compilada
#define _DEBUG_

#include <Arduino.h>

// Constantes para ajuste do controle
constexpr const short baseSpeed = 255;
constexpr const float turnRatio = 0.8;
constexpr const short white = 3000;
constexpr const short black = 150;
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
  // Alocação de todos os timers
  //* Por padrão, a biblioteca ESP32PWM reserva apenas o Timer 0 para uso. Usando a definição abaixo é permitida a alocação de todos os timers (0, 1, 2 e 3) para uso com a biblioteca.
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);

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

  if ((sensorRightValue > white) && (sensorLeftValue < black))
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
  bool onTrack = (sensorCenterLeftValue > white && sensorCenterValue > white && sensorCenterRightValue > white);

  // Cálculo do erro
  float error = sensorCenterValue - ((sensorCenterLeftValue + sensorCenterRightValue) / 2);

  // Cálculo da correção para manter o robô na linha
  float correction = error * turnRatio;

  // Atualização da velocidade dos motores
  short speedLeft = baseSpeed - correction;
  short speedRight = baseSpeed - correction;

  // Limitação da velocidade dos motores
  speedLeft = constrain(speedLeft, 0, 255);
  speedRight = constrain(speedRight, 0, 255);

  // Controle dos motores
  controlMotor1(speedLeft);
  controlMotor2(speedRight);

#ifdef _DEBUG_
  Serial.print("onTrack: ");
  Serial.println(onTrack);

  Serial.print("error: ");
  Serial.println(error);

  Serial.print("correction: ");
  Serial.println(correction);

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
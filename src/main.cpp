// ! Modos
//* Enquanto a linha abaixo não for um comentário, a referente parte não será compilada
#define _DEBUG_

#include <Arduino.h>

// Constantes para ajuste do controle
constexpr const short sensorMaxValue = 4095;
constexpr const short sensorMinValue = 75;
constexpr const short baseSpeed = 120; // Resolução da GPIO ESP32: 16 bits (0 a 65535)
constexpr const float turnRatio = 0.5;
constexpr const float ajustRatio = 2;
constexpr const short white = 3000;
constexpr const short black = 1500;
short lapMarker = 0;
short curveWarning = 0;
constexpr const short startTime = 5000; // ms

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
constexpr const short motorRightB = 35; //! Não pode Ser usado pois é só INPUT
constexpr const short motorRightEnable = 33;

short speedLeft = 0;
short speedRight = 0;

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
  pinMode(motorRightEnable, OUTPUT);

  // Tempo para começar
  delay(startTime);

#ifdef _DEBUG_
  Serial.println("---------");

  Serial.println("START");
#endif
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

  Serial.print("sensorLeftValue: ");
  Serial.println(sensorLeftValue);
  Serial.print("sensorRightValue: ");
  Serial.println(sensorRightValue);

  Serial.println();

#endif

  // Detecção no sensor de volta (Direito)
  if ((sensorRightValue >= white) && (sensorLeftValue <= black))
  {
    while (sensorRightValue > black)
    {
      sensorCenterLeftValue = analogRead(sensorCenterLeft);
      sensorCenterValue = analogRead(sensorCenter);
      sensorCenterRightValue = analogRead(sensorCenterRight);
      sensorRightValue = analogRead(sensorRight);
      sensorLeftValue = analogRead(sensorLeft);
    }
    lapMarker = lapMarker + 1;
  }

  // Detecção no sensor de curva (Esquerdo)

  if ((sensorLeftValue >= white) && (sensorRightValue <= black))
  {
    while (sensorLeftValue > black)
    {
      sensorCenterLeftValue = analogRead(sensorCenterLeft);
      sensorCenterValue = analogRead(sensorCenter);
      sensorCenterRightValue = analogRead(sensorCenterRight);
      sensorRightValue = analogRead(sensorRight);
      sensorLeftValue = analogRead(sensorLeft);
#ifdef _DEBUG_
      Serial.println("MARCACAO ESQUERDA");
#endif
    }
    curveWarning = curveWarning + 1;
  }

  // Verificação se o robô está na linha com o sensor central
  bool onTrack = (sensorCenterValue >= white) && (sensorCenterLeftValue <= black) && (sensorCenterRightValue <= black);

  // Saida do trajeto
  bool offTrack = (sensorCenterValue <= black) && (sensorCenterLeftValue <= black) && (sensorCenterRightValue <= black);

#ifdef _DEBUG_

  Serial.print("lapMarker: ");
  Serial.println(lapMarker);
  Serial.print("onTrack: ");
  Serial.println(onTrack);
  Serial.print("curveWarning: ");
  Serial.println(curveWarning);
  Serial.print("offTrack: ");
  Serial.println(offTrack);

  Serial.println();
#endif

  if (offTrack == 1)
  {
    // TODO: Colocar loop infinito
    stopRobot();
#ifdef _DEBUG_
    Serial.println("OFFTRACK");
#endif
  }
  else if (onTrack == 1)
  {
    controlMotorLeft(baseSpeed);
    controlMotorRight(baseSpeed);

#ifdef _DEBUG_
    Serial.println("ONTRACK");
#endif
  }
  else if (onTrack == 0)
  {
    // Cálculo de Erro
    /*
    -: que que sejam o mais próximo ambos os valores
    +: Quero que eles sejam o mais diferentes o possível
    */
    float differenceLeft = (black - sensorCenterLeftValue);
    float differenceRight = (black - sensorCenterRightValue);
    float differenceCenter = (sensorCenterValue - ((sensorCenterLeftValue + sensorCenterRightValue) / 2)); // Talvez não tenha utilidade

    // Cálculo da correção para manter o robô na linha
    // Correção converte valores do sensor para valores do motor
    // Sensores center left e center right estão muito longe do centro logo a correção não pode ter um valor significativo
    float correctionLeft = map(differenceLeft, sensorMinValue, sensorMaxValue, 0, baseSpeed) * ajustRatio;
    float correctionRight = map(differenceRight, sensorMinValue, sensorMaxValue, 0, baseSpeed) * ajustRatio;
    float correctionCenter = map(differenceCenter, sensorMinValue, sensorMaxValue, 0, baseSpeed) * ajustRatio; // Talvez não tenha utilidade

    // Atualização da velocidade dos motores
    // Quero que ele se afaste do branco, logo o motor do mesmo lado deve reduzir a velocidade deve agir ele se aproxime
    // Limitação da velocidade dos motores para valores cabíveis
    speedLeft = constrain((baseSpeed - correctionRight), 0, baseSpeed);
    speedRight = constrain((baseSpeed - correctionLeft), 0, baseSpeed);

#ifdef _DEBUG_

    Serial.println("TRACK AJUST");

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
#endif

    if ((curveWarning % 2) != 0) // Valor impar, ou seja início da curva
    {
#ifdef _DEBUG_
      Serial.println("CURVE");
#endif
      speedLeft = turnRatio * speedLeft;
      speedRight = turnRatio * speedRight;
      controlMotorLeft(speedLeft);
      controlMotorRight(speedRight);
    }
    else
    {
#ifdef _DEBUG_
      Serial.println("LINE");
#endif
      controlMotorLeft(speedLeft);
      controlMotorRight(speedRight);
    }
  }

  if (lapMarker == 2)
  {
    delay(250);
    stopRobot();
  }
#ifdef _DEBUG_
  delay(50);
#endif
}
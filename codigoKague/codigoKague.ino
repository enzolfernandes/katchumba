// Constantes para ajuste do controle
const int baseSpeed = 255;
const float turnCorrection = 0.8;
const float turnRatio = 0.6;
const int white = 3000;
const int black = 150;
int lapMarker = 0;
int turnMarker = 0;

// Variáveis para controle do estado do sensor de marcação
bool rightSensorDetected = false;
bool leftSensorDetected = false;

// Definição dos pinos dos sensores e dos motores
const int sensorCenterLeft = 14;
const int sensorCenter = 27;
const int sensorCenterRight = 26;
const int sensorRight = 25;
const int sensorLeft = 12;
const int motorLeftA = 22;
const int motorLeftB = 23;
const int motorLeftEnable = 4;
const int motorRightA = 32;
const int motorRightB = 35;
const int motorRightEnable = 33;


// Variáveis para controle do PWM
const int freq = 30000;
const int pwmChannelLeft = 0;
const int resolution = 8;
const int pwmChannelRight = 0;


void setup() {
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

  // Configuração das funcionalidades do ledc
  ledcSetup(pwmChannelLeft, freq, resolution);
  ledcSetup(pwmChannelRight, freq, resolution);
  
  // Vincular o canal ao pino
  ledcAttachPin(motorLeftEnable, pwmChannelLeft);
  ledcAttachPin(motorRightEnable, pwmChannelRight);
}

void loop() {
  // Leitura dos sensores
  int sensorCenterLeftValue = analogRead(sensorCenterLeft);
  int sensorCenterValue = analogRead(sensorCenter);
  int sensorCenterRightValue = analogRead(sensorCenterRight);
  int sensorRightValue = analogRead(sensorRight);
  int sensorLeftValue = analogRead(sensorLeft);

  if ((sensorRightValue >= white) && (sensorLeftValue <= black)) {
    lapMarker = lapMarker + 1;
    if (lapMarker >= 2) {
      stopRobot();
    }
  }

  // Verificação se o robô está na linha com os sensores centrais
  bool onTrack = (sensorCenterLeftValue > white && sensorCenterValue > white && sensorCenterRightValue > white);

  if (onTrack == true) {
    // Controle dos motores
    controlMotorLeft(baseSpeed);
    controlMotorRight(baseSpeed);
  } else {
    // Cálculo do erro
    int errorLeft = sensorCenterValue - sensorCenterLeftValue;
    int errorRight = sensorCenterValue - sensorCenterRightValue;

    // Cálculo da correção para manter o robô na linha
    int correctionLeft = errorLeft * turnCorrection;
    int correctionRight = errorRight * turnCorrection;

    // Atualização da velocidade dos motores
    int speedLeft = baseSpeed - correctionLeft;
    int speedRight = baseSpeed - correctionRight;

    // Limitação da velocidade dos motores DA PRA SUBSTITUIR POR MAP + CONSTRAIN
    if (speedLeft < 0) speedLeft = 0;
    if (speedLeft > baseSpeed) speedLeft = baseSpeed;
    if (speedRight < 0) speedRight = 0;
    if (speedRight > baseSpeed) speedRight = baseSpeed;

    if ((sensorLeftValue >= white) && (sensorRightValue <= black)) {
      turnMarker = turnMarker + 1;
    }

    if (turnMarker % 2 == 1) {   //Números impares representam curvas
    speedLeft = speedLeft * turnRatio;
    speedRight = speedRight * turnRatio;
  }

  // Controle dos motores
  controlMotorLeft(speedLeft);
  controlMotorRight(speedRight);
}

}

// Função para controlar o motor 1
void controlMotorLeft(int speed) {
  ledcWrite(pwmChannelLeft, speed);  
  digitalWrite(motorLeftA, HIGH);
  digitalWrite(motorLeftB, LOW);
}

// Função para controlar o motor 2
void controlMotorRight(int speed) {
  ledcWrite(pwmChannelRight, speed);  
  digitalWrite(motorRightA, HIGH);
  digitalWrite(motorRightB, LOW);
}

// Função para parar o robô
void stopRobot() {
  while (true) {
    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, LOW);
    digitalWrite(motorRightA, LOW);
    digitalWrite(motorRightB, LOW);
  }
}

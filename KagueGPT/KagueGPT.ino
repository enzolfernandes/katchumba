// Constantes para ajuste do controle
const int baseSpeed = 255;
const float turnRatio = 0.8;
const int white = 3000;
const int black = 150;
int lapMarker = 0;

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

// Constantes para ajuste do controle
//const int baseSpeed = 255;//Valor referente ao arduino, pesquisar equivalente ESP
//const float turnRatio = 0.8;

// Variáveis para controle do estado do sensor de marcação
//bool rightSensorDetected = false;
//bool leftSensorDetected = false;

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
}

void loop() {
  // Leitura dos sensores
  int sensorCenterLeftValue = analogRead(sensorCenterLeft);
  int sensorCenterValue = analogRead(sensorCenter);
  int sensorCenterRightValue = analogRead(sensorCenterRight);
  int sensorRightValue = analogRead(sensorRight);
  int sensorLeftValue = analogRead(sensorLeft);

  if ((sensorRightValue > white) && (sensorLeft < black)){
    lapMarker = lapMarker + 1;
  } else if (lapMarker >= 2){
    stopRobot();
  }

  // Ialvez utilizar isso para marcação esquerda
//  if ((!rightSensorDetected && sensorRightValue > white)&&() ){
//    rightSensorDetected = true;
//  } else if (rightSensorDetected && sensorRightValue < white) {
//    rightSensorDetected = false;
//  }

  // Verificação se o robô está na linha com os sensores centrais
  bool onTrack = (sensorCenterLeftValue > white && sensorCenterValue > white && sensorCenterRightValue > white);

  // Cálculo do erro
  int error = sensorCenterValue - ((sensorCenterLeftValue + sensorCenterRightValue) / 2);

  // Cálculo da correção para manter o robô na linha
  int correction = error * turnRatio;

  // Atualização da velocidade dos motores
  int speedLeft = baseSpeed - correction;
  int speedRight = baseSpeed - correction;

  // Limitação da velocidade dos motores
  if (speedLeft < 0) speedLeft = 0;
  if (speedLeft > baseSpeed) speedLeft = baseSpeed;
  if (speedRight < 0) speedRight = 0;
  if (speedRight > baseSpeed) speedRight = baseSpeed;

  // Verificação do estado dos sensores de marcação e parada do robô se necessário
  if (rightSensorDetected && leftSensorDetected) {
    // Fim da pista
    stopRobot();
    return;
  } else if (leftSensorDetected) {
    // Início ou fim da curva
    stopMotor1();
  } else if (rightSensorDetected) {
    // Início ou fim da pista
    stopMotor2();
  }

  // Controle dos motores
  controlMotor1(speedLeft);
  controlMotor2(speedRight);
}

// Função para controlar o motor 1
void controlMotor1(int speed) {
  digitalWrite(motorLeftA, speed > 0 ? HIGH : LOW);
  digitalWrite(motorLeftB, LOW);
  analogWrite(motorLeftEnable, abs(speed));
}

// Função para controlar o motor 2
void controlMotor2(int speed) {
  digitalWrite(motorRightA, speed > 0 ? HIGH : LOW);
  digitalWrite(motorRightB, LOW);
  analogWrite(motorRightEnable, abs(speed));
}

// Função para parar o robô
void stopRobot() {
  while (true){
  digitalWrite(motorLeftA, LOW);
  digitalWrite(motorLeftB, LOW);
  digitalWrite(motorRightA, LOW);
  digitalWrite(motorRightB, LOW);
  }
}
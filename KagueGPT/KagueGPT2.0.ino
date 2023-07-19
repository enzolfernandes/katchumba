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

void setup()
{
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

  if ((sensorRightValue > white) && (sensorLeftValue < black))
  {
    lapMarker = lapMarker + 1;
  }
  else if (lapMarker >= 2)
  {
    stopRobot();
  }

  // Verificação se o robô está na linha com os sensores centrais
  bool onTrack = (sensorCenterLeftValue > white && sensorCenterValue > white && sensorCenterRightValue > white);

  // Cálculo do erro
  short error = sensorCenterValue - ((sensorCenterLeftValue + sensorCenterRightValue) / 2);

  // Cálculo da correção para manter o robô na linha
  short correction = error * turnRatio;

  // Atualização da velocidade dos motores
  short speedLeft = baseSpeed - correction;
  short speedRight = baseSpeed - correction;

  // Limitação da velocidade dos motores
  if (speedLeft < 0)
    speedLeft = 0;
  if (speedLeft > baseSpeed)
    speedLeft = baseSpeed;
  if (speedRight < 0)
    speedRight = 0;
  if (speedRight > baseSpeed)
    speedRight = baseSpeed;

  // Controle dos motores
  controlMotor1(speedLeft);
  controlMotor2(speedRight);
}

// Função para controlar o motor 1
void controlMotor1(short speed)
{
  digitalWrite(motorLeftA, speed > 0 ? HIGH : LOW);
  digitalWrite(motorLeftB, LOW);
  analogWrite(motorLeftEnable, abs(speed));
}

// Função para controlar o motor 2
void controlMotor2(short speed)
{
  digitalWrite(motorRightA, speed > 0 ? HIGH : LOW);
  digitalWrite(motorRightB, LOW);
  analogWrite(motorRightEnable, abs(speed));
}

// Função para parar o robô
void stopRobot()
{
  while (true)
  {
    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, LOW);
    digitalWrite(motorRightA, LOW);
    digitalWrite(motorRightB, LOW);
  }
}

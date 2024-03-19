#include <QTRSensors.h>
//#include <esp32>
#include <Arduino.h>

//#define NUM_SENSORS 8      // Número de sensores no QTR-8 RC
#define NUM_SENSORS 4      // Número de sensores no QTR-8 RC teste
#define TIMEOUT 2500        // Tempo máximo permitido para a leitura de um sensor
#define EMITTER_PIN 3       // Pino do emissor do sensor QTR

QTRSensors qtr;

void setup() {
  Serial.begin(115200);
  qtr.setTypeRC();     
  qtr.setSensorPins((const uint8_t[]){2, 4, 5, 6}, NUM_SENSORS);      // Configurar o tipo de sensor como QTR-RC teste
  //qtr.setSensorPins((const uint8_t[]){2, 4, 5, 6, 7, 8, 9, 10}, NUM_SENSORS);
  qtr.setEmitterPin(EMITTER_PIN);
  qtr.setTimeout(TIMEOUT);

  //MOTORES  
    pinMode(motor1a, OUTPUT);
    pinMode(motor1b, OUTPUT);

  // Calibrar os sensores
  Serial.println("Calibrando os sensores. Mantenha os sensores sobre uma superfície branca ou preta.");
  delay(1000);
  for (int i = 0; i < 400; i++) {
    qtr.calibrate();
    delay(5);
  }
  Serial.println("Calibração concluída!");
  delay(1000);
}

void loop() {
  uint16_t sensorValues[NUM_SENSORS];
  qtr.read(sensorValues);

  // Mostrar os valores lidos
  Serial.print("Valores dos sensores: ");
  for (int i = 0; i < NUM_SENSORS; i++) {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();
  delay(500);
}
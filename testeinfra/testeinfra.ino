int infra1 = 25;
int infra2 = 26;
int leitura1 = 0;
int leitura2 = 0;

void setup() {

    pinMode(infra1, INPUT);
    pinMode(infra2, INPUT);

    serial.begin(9600);

  
}

void loop() {
  
    leitura1 = analogRead(infra1);
    leitura2 = analogRead(infra2);

    Serial.println(leitura1);
    delay(500);
    Serial.println(leitura2);
    delay(500);
}

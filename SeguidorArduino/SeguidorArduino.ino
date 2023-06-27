int motor1a = A3;  //motor da direita sentido horario
int motor1b = A4;  //motor da direita sentido anti-horario
int enable1 = 11;  //enable motor 1

int motor2a = A5;  //motor da esquerda sentido horario
int motor2b = A6;  //motor da esquerda sentido anti-horario
int enable2 = 12;  //enable motor 2

int pinInfrav1 = 7;  //infravermelho do centro-direita
int pinInfrav2 = 6;  //infravermelho centro
int pinInfrav3 = 5;  //infravermelho do centro-esquerda
int pinInfrav4 = 9;  //infravermelho estrema-direita
int pinInfrav5 = 3; //infravermelho extrema-esquerda

//transforma o input no infravermelho em um valor booleano

//centrais:
bool infraValor1;
bool infraValor2;
bool infraValor3;

//laterais
bool infraValor4; //direita
bool infraValor5; //esquerda
int cont = 0; //cont da direita
int cont2 = 0; //cont da esquerda
int x, y;

void setup() {

  Serial.begin(11520);  //de acordo com o arduino

  //os motores recebem informacao

  pinMode(motor1a, OUTPUT);
  pinMode(motor1b, OUTPUT);

  pinMode(motor2a, OUTPUT);
  pinMode(motor2b, OUTPUT);

  //os infravermelhos dao informacao

  pinMode(pinInfrav1, INPUT);
  pinMode(pinInfrav2, INPUT);
  pinMode(pinInfrav3, INPUT);
  pinMode(pinInfrav4, INPUT);
  pinMode(pinInfrav5, INPUT);

  //os enable

  pinMode(enable1, OUTPUT);
  pinMode(enable2, OUTPUT);

}

void emFrente();
void emFrente2();
void Parar();
void linhaEsquerdaD();
void linhaEsquerdaE();
void inicioFim();

void loop() {
  //ler o valor nos infravermelhos (0=branco e 1=preto)

  infraValor1 = digitalRead(pinInfrav1);
  infraValor2 = digitalRead(pinInfrav2);
  infraValor3 = digitalRead(pinInfrav3);
  infraValor4 = digitalRead(pinInfrav4);
  infraValor5 = digitalRead(pinInfrav5);

  if (infraValor1 == 1 && infraValor2 == 0 || infraValor3 == 1 && infraValor4 == 1 || infraValor5 == 1) { //em frente
    emFrente();
  }

  else if (infraValor1 == 1 && infraValor2 == 0 || infraValor3 == 0 && infraValor4 == 0 || infraValor5 == 1) { //a direita
    linhaEsquerdaD();
  }

  else if (infraValor1 == 0 && infraValor2 == 0 || infraValor3 == 1 && infraValor4 == 0 || infraValor5 == 1) { //a esquerda
    linhaEsquerdaE();
  }

  else if (infraValor1 == 0 && infraValor2 == 0 || infraValor3 == 0 && infraValor4 == 0 || infraValor5 == 0) { //cruzamento
    emFrente2();
  }
  else if (infraValor1 == 1 && infraValor2 == 0 || infraValor3 == 1 && infraValor4 == 0 || infraValor5 == 0) {
    inicioFim();
  }
}

void emFrente() {

  analogWrite(motor1a, 255);
  analogWrite(motor1b, 0);

  analogWrite(motor2a, 0);
  analogWrite(motor2b, 255);

}

void emFrente2() {

  analogWrite(motor1a, 255);
  analogWrite(motor1b, 0);

  analogWrite(motor2a, 0);
  analogWrite(motor2b, 255);

}

void Parar() {

  analogWrite(motor1a, 0);
  analogWrite(motor1b, 0);

  analogWrite(motor2a, 0);
  analogWrite(motor2b, 0);

}

void inicioFim() {
  cont = cont + 1;
  if (cont = 2) {
    ;
    Parar();
  }

}

void linhaEsquerdaE() {
  cont2 = cont2 + 1;
  x = cont2 % 2;
  if (x = 1) {
    analogWrite(motor1a, 245);
    analogWrite(motor1b, 0);

    analogWrite(motor2a, 0);
    analogWrite(motor2b, 0);
  }
  else {
    analogWrite(motor1a, 255);
    analogWrite(motor1b, 0);

    analogWrite(motor2a, 0);
    analogWrite(motor2b, 255);
  }
}

  void linhaEsquerdaD() {
    cont2 = cont2 + 1;
    y = cont2 % 2;
    if (y = 1) {
      digitalWrite(motor1a, HIGH);
      digitalWrite(motor1b, LOW);

      digitalWrite(motor2a, LOW);
      digitalWrite(motor2b, LOW);
    }
    else {
      analogWrite(motor1a, HIGH);
      analogWrite(motor1b, LOW);

      analogWrite(motor2a, HIGH);
      analogWrite(motor2b, LOW);
    }
  }

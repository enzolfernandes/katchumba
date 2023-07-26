// Função para controlar o motor 1
void controlMotorLeft(short speed)
{
    digitalWrite(motorLeftA, HIGH);
    digitalWrite(motorLeftB, LOW);
    analogWrite(motorLeftEnable, speed);
}

// Função para controlar o motor 2
void controlMotorRight(short speed)
{
    digitalWrite(motorRightA, HIGH);
    //digitalWrite(motorRightB, LOW);
    analogWrite(motorRightEnable, speed);
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

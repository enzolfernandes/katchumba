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
    analogWrite(motorRightEnable, speed);
}

void stopMotorLeft()
{
    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, LOW);
}

void stopMotorRight()
{
    digitalWrite(motorRightA, LOW);
}

// Função para parar o robô
void stopRobot()
{
    while (true)
    {
        stopMotorLeft();
        stopMotorRight();
    }
}
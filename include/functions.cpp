// Função para controlar o motor 1
void controlMotor1(unsigned int speed)
{
    digitalWrite(motorLeftA, speed > 0 ? HIGH : LOW);
    digitalWrite(motorLeftB, LOW);
    analogWrite(motorLeftEnable, speed);
}

// Função para controlar o motor 2
void controlMotor2(unsigned int speed)
{
    digitalWrite(motorRightA, speed > 0 ? HIGH : LOW);
    digitalWrite(motorRightB, LOW);
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

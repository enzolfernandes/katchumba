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

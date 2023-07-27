// Função para controlar o motor 1
void controlMotorLeft(short speed)
{
    digitalWrite(motorLeftA, HIGH);
    digitalWrite(motorLeftB, LOW);
    analogWrite(motorLeftEnable, speed);
#ifdef _DEBUG_
    Serial.print("speedLeft: ");
    Serial.println(speed);
#endif
}

// Função para controlar o motor 2
void controlMotorRight(short speed)
{
    digitalWrite(motorRightA, HIGH);
    analogWrite(motorRightEnable, speed);
#ifdef _DEBUG_
    Serial.print("speedRight: ");
    Serial.println(speed);
    Serial.println();
#endif
}

void stopMotorLeft()
{
    digitalWrite(motorLeftA, LOW);
    digitalWrite(motorLeftB, LOW);

#ifdef _DEBUG_
    Serial.print("speedLeft: ");
    Serial.println(0);
#endif
}

void stopMotorRight()
{
    digitalWrite(motorRightA, LOW);

#ifdef _DEBUG_
    Serial.print("speedRight: ");
    Serial.println(0);
    Serial.println();
#endif
}

// Função para parar o robô
void stopRobot()
{
    stopMotorLeft();
    stopMotorRight();
}
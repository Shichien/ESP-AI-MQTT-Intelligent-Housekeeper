//
// Created by Deralive (10235101526) on 2024/9/9.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "HCSR04.h"

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

void initHCSR04() {
    pinMode(FAN_PIN_A, OUTPUT);
    pinMode(FAN_PIN_B, OUTPUT);
    digitalWrite(FAN_PIN_A, HIGH);
}

void loopHCSR04() {
    int distance = sonar.ping_cm();

    // 输出距离
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance < 10)
    {
        digitalWrite(FAN_PIN_B,LOW);
    } else
    {
        digitalWrite(FAN_PIN_A,LOW);
    }
}
//
// Created by Deralive (10235101526) on 2024/8/31.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "MG90Servo.h"

Servo myservo;

void initMG90() {
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	myservo.setPeriodHertz(50);  // 标准 50Hz 舵机
	myservo.attach(32, 1000, 2000);  // 设置舵机连接到 GPIO 33，并设置脉冲宽度范围
}


void loopMG90() {
	for (float posDegrees = 0; posDegrees <= 180; posDegrees += 0.5) {
		myservo.write(posDegrees);
		Serial.println(posDegrees);
		delay(10);
	}

	for (float posDegrees = 180; posDegrees >= 0; posDegrees -= 0.5) {
		myservo.write(posDegrees);
		Serial.println(posDegrees);
		delay(10);
	}

	delay(2000);
}

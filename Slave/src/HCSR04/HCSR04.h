//
// Created by Deralive (10235101526) on 2024/9/9.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#ifndef HCSR04_H
#define HCSR04_H

#include <NewPing.h>
#include "../configuration.h"

#define TRIG_PIN 5
#define ECHO_PIN 18
#define MAX_DISTANCE 200 // 最大检测距离 200 cm
#define FAN_PIN_A 4
#define FAN_PIN_B 2

void initHCSR04();
void loopHCSR04();

#endif //HCSR04_H

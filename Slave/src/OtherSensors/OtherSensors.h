//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#ifndef OTHERSENSORS_H
#define OTHERSENSORS_H

#include "configuration.h"

void initLM393();
void loopLM393();

void initFire();
void loopFire();

void initRaindrop();
void loopRaindrop();

void combineLoop();

#endif //OHTERSENSORS_H

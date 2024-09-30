//
// Created by Deralive (10235101526) on 2024/8/31.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#ifndef SNAKE_H
#define SNAKE_H

#include "configuration.h"
#include "MPU6050/MPU6050.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1

#define SNAKE_MAX_LENGTH 100
#define SNAKE_INITIAL_LENGTH 5

extern int snakeX[SNAKE_MAX_LENGTH];
extern int snakeY[SNAKE_MAX_LENGTH];
extern int snakeLength;

extern int foodX, foodY;

enum Direction {UP, DOWN, LEFT, RIGHT};
extern Direction dir;

extern bool gameOver;

void initSnake();
void loopSnake();
void spawnFood();
void updateSnake();
void checkCollision();
void drawGame();
void resetGame();
void I2CScanner();

#endif //SNAKE_H

//
// Created by Deralive (10235101526) on 2024/8/31.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "Snake.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Direction dir = RIGHT;
bool gameOver = false;

int snakeX[SNAKE_MAX_LENGTH] = {0};
int snakeY[SNAKE_MAX_LENGTH] = {0};
int snakeLength = SNAKE_INITIAL_LENGTH;
int foodX = 0, foodY = 0;

extern MPU6050Message mpu6050Data;

void initSnake() {
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        Serial.println(F("SSD1306 allocation failed"));
        while (1);
    }

    display.display();
    delay(2000);
    display.clearDisplay();

    for (int i = 0; i < snakeLength; i++) {
        snakeX[i] = SCREEN_WIDTH / 2 - i * 2;
        snakeY[i] = SCREEN_HEIGHT / 2;
    }

    spawnFood();
}

void loopSnake() {
    if (!gameOver) {
        updateSnake();
        checkCollision();
        drawGame();
    } else {
        display.clearDisplay();
        display.setTextSize(2);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(20, 20);
        display.print("Game Over");
        display.display();
        resetGame();
    }
}

void updateSnake() {
    // 蛇身移动
    for (int i = snakeLength - 1; i > 0; i--) {
        snakeX[i] = snakeX[i - 1];
        snakeY[i] = snakeY[i - 1];
    }

    // 通过卡尔曼滤波检测偏转角度
    if (mpu6050Data.UpAndDown > 10.0) {
        dir = DOWN;
    } else if (mpu6050Data.UpAndDown < -10.0) {
        dir = UP;
    } else if (mpu6050Data.LeftAndRight > 10.0) {
        dir = LEFT;
    } else if (mpu6050Data.LeftAndRight < -10.0) {
        dir = RIGHT;
    }

    switch (dir) {
        case UP: snakeY[0] -= 2;
            break;
        case DOWN: snakeY[0] += 2;
            break;
        case LEFT: snakeX[0] -= 2;
            break;
        case RIGHT: snakeX[0] += 2;
            break;
    }

    // 是否吃到食物
    if (snakeX[0] == foodX && snakeY[0] == foodY) {
        if (snakeLength < SNAKE_MAX_LENGTH) {
            snakeLength++;
            snakeX[snakeLength - 1] = snakeX[snakeLength - 2];
            snakeY[snakeLength - 1] = snakeY[snakeLength - 2];
        }
        spawnFood();
    }
}

void checkCollision() {
    // 墙体碰撞检测
    if (snakeX[0] < 0 || snakeX[0] >= SCREEN_WIDTH || snakeY[0] < 0 || snakeY[0] >= SCREEN_HEIGHT) {
        gameOver = true;
    }

    // 自身碰撞检测
    for (int i = 1; i < snakeLength; i++) {
        if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
            gameOver = true;
        }
    }
}

void drawGame() {
    display.clearDisplay();
    for (int i = 0; i < snakeLength; i++) {
        display.drawRect(snakeX[i], snakeY[i], 2, 2, SSD1306_WHITE);
    }
    display.drawRect(foodX, foodY, 2, 2, SSD1306_WHITE);
    display.display();
}

void spawnFood() {
    foodX = random(0, SCREEN_WIDTH / 2) * 2;
    foodY = random(0, SCREEN_HEIGHT / 2) * 2;
}

void resetGame() {
    snakeLength = SNAKE_INITIAL_LENGTH;
    for (int i = 0; i < snakeLength; i++) {
        snakeX[i] = SCREEN_WIDTH / 2 - i * 2;
        snakeY[i] = SCREEN_HEIGHT / 2;
    }
    dir = RIGHT;
    gameOver = false;
    spawnFood();
}

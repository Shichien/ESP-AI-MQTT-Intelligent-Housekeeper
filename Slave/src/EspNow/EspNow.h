//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#ifndef ESPNOW_H
#define ESPNOW_H

#include "configuration.h"
#include <WiFi.h>

void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status); // 发送回调函数
void initEspNow();

#endif //ESPNOW_H

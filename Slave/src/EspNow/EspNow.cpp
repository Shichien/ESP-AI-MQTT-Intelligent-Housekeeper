//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "EspNow.h"


// 发送回调函数
void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
    Serial.print(F("Last Packet Send Status: "));
    Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success\n--------------------\n" : "Delivery Fail\n-----------------\n");
}

void initEspNow() {
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println(F("Error initializing ESP-NOW\n"));
    }

    // 注册发送回调函数
    esp_now_register_send_cb(onDataSent);

    // 添加主机的MAC地址
    esp_now_peer_info_t peerInfo;
    memcpy(peerInfo.peer_addr, masterMACAddress, 6);
    peerInfo.channel = 0;
    peerInfo.encrypt = false;
    peerInfo.ifidx = WIFI_IF_STA;

    if (esp_now_add_peer(&peerInfo) != ESP_OK) {
        Serial.println(F("Failed to add peer/n"));
    }
}

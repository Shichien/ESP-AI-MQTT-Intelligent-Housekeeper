//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "OtherSensors.h"

void initLM393() {
    pinMode(LIGHT_PIN, INPUT);
}

void loopLM393() {
    int brightness = analogRead(LIGHT_PIN);
    otherData.brightness = 4096 - brightness;
    Serial.println("Brightness: " + String(otherData.brightness));
}

void initRaindrop() {
    pinMode(RAINDROP_PIN, INPUT);
}

void loopRaindrop() {
    int rainValue = analogRead(RAINDROP_PIN);
    otherData.rainValue = 4095 - rainValue;
    if (otherData.rainValue < 50 ) {
        isRainy = false;
        Serial.println(F("Now isn't Rainy!"));
    } else {
        isRainy = true;
        Serial.println(F("Now is Rainy!"));
    }
}

void initFire() {
    pinMode(FIRE_PIN,INPUT);
}

void loopFire() {
    int combustionValue = digitalRead(FIRE_PIN);
    otherData.combustionValue = combustionValue;
    Serial.println("CombustionValue: " + String(combustionValue));
    if (combustionValue == 1) {
        isAblaze = true;
        Serial.println(F("Now is ablaze!"));
    } else {
        isAblaze = false;
        Serial.println( "Now isn't ablaze!");
    }
}

void combineLoop() {
    loopFire();
    loopRaindrop();
    loopLM393();

    // 发送数据到主机
    esp_err_t result = esp_now_send(masterMACAddress, (uint8_t *) &otherData, sizeof(otherData));
    if (result == ESP_OK) {
        Serial.println(F("Sent Other data successfully"));
        Serial.println(F("----------------------------"));
    } else {
        Serial.println(F("Error sending the Other data"));
        Serial.println(F("----------------------------"));
    }
}




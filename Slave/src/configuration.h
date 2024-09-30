//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <Arduino.h>
#include <esp_now.h>
#include <PubSubClient.h>
#include <WiFiClient.h>

// 引脚定义 ————————————————————————————————————————————————————————————————
#define RAINDROP_PIN 33
#define MQ5_PIN 36
#define MQ135_PIN 35
#define LIGHT_PIN 34
#define DHT22_PIN 25
#define FIRE_PIN 13
#define DHTTYPE DHT22

// MQ 传感器模块 ————————————————————————————————————————————————————————————
extern const float Voltage_Resolution;        // 基准电压
extern const int ADC_Bit_Resolution;          // ADC 分辨率
extern const float RatioMQ135CleanAir;          // 纯净空气基准 RS / R0
extern const float RatioMQ5CleanAir;
extern float R0;

extern unsigned long previousMillisMPU6050;   // 上一次执行 MPU6050 的时间
extern unsigned long previousMillisDHT22;     // 上一次执行 DHT22 的时间
extern unsigned long previousMillisMQ;        // 上一次执行 MQ 时间
extern unsigned long previousMillisOther;
extern unsigned long previousMillisSnake;
extern unsigned long previousMillisMG90;
extern unsigned long previousMillisHCSR04;

extern const long intervalMPU6050;            // MPU6050 读取间隔（ms）
extern const long intervalDHT22;              // DHT22 读取间隔（ms）
extern const long intervalMQ;                 // MQ 读取间隔（ms）
extern const long intervalOther;
extern const long intervalSnake;
extern const long intervalMG90;
extern const long intervalHCSR04;

extern const String SSID;
extern const String Password;

// 基于 MQTT 数据传输
extern WiFiClient espClient;
extern PubSubClient client;
extern const String MQTT_Server; // 库不支持 String
extern const int MQTT_Port;
extern const String MQTT_Device_ID;
extern const String MQTT_Product_ID;
extern const String MQTT_Token;

// IIC 通信使用的是 ESP32 原本自身的
// #define SCL_PIN 22
// #define SDA_PIN 21

// 基于 ESP - NOW 数据传输 ——————————————————————————————————————————————————
extern uint8_t masterMACAddress[];

// 8 字节
typedef struct DHT22Message {
    float temperature;
    float humidity;
} DHT22Message;

// 12 字节
typedef struct MPU6050Message {
    float UpAndDown;
    float LeftAndRight;
    float temperature;
} MPU6050Message;

// 16 字节
typedef struct MQ5Message {
    float h2PPM;
    float ch4PPM;
    float lpgPPM;
    float flagMQ5;
} MQ5Message;

// 20 字节
typedef struct OtherMessage {
    int brightness;
    int rainValue;
    int combustionValue;
    int flagOther;
    int flagOther2;
} OtherMessage;

// 24 字节
typedef struct MQ135Message {
    float coPPM;
    float alcoholPPM;
    float co2PPM;
    float toluenePPM;  // 甲苯 浓度
    float nh4PPM;
    float acetonePPM;  // 丙酮 浓度
} MQ135Message;

extern MPU6050Message mpu6050Data;
extern DHT22Message dht22Data;
extern MQ135Message mq135Data;
extern MQ5Message mq5Data;
extern OtherMessage otherData;

// 特殊定义
extern bool isRainy;
extern bool isAblaze;
extern int Brightness;
#endif //CONFIGURATION_H

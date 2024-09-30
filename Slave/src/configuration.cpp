//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "configuration.h"

uint8_t masterMACAddress[] = {0xBC,0xDD,0xC2,0xD0,0x07,0xB4};

unsigned long previousMillisMPU6050 = 0;   // 上一次执行 MPU6050 的时间
unsigned long previousMillisDHT22 = 0;     // 上一次执行 DHT22 的时间
unsigned long previousMillisMQ = 0;        // 上一次执行 MQ 时间
unsigned long previousMillisOther = 0;     // 上一次执行其他传感器的时间
unsigned long previousMillisSnake = 0;
unsigned long previousMillisMG90 = 0;
unsigned long previousMillisHCSR04 = 0;

const long intervalMPU6050 = 50;          // MPU6050 读取间隔（ms）
const long intervalDHT22 = 5000;           // DHT22 读取间隔（ms）
const long intervalMQ = 2000;              // MQ 读取间隔（ms）
const long intervalOther = 2000;           // 其他传感器读取间隔
const long intervalSnake = 500;
const long intervalMG90 = 100; // Todo
const long intervalHCSR04 = 100;

const float Voltage_Resolution = 3.3;      // Esp32 的基准电压是 3.3V
const int ADC_Bit_Resolution = 12;         // ESP32 的 ADC 分辨率
const float RatioMQ135CleanAir = 3.6;      // 纯净空气基准 RS / R0 = 3.6 ppm
const float RatioMQ5CleanAir = 6.5;        // 纯净空气基准 RS / R0 = 6.5 ppm
float R0 = 0;

const String MQTT_Server = "mqtts.heclouds.com";
const int MQTT_Port = 1883;
const String MQTT_Device_ID = "DHT22";
const String MQTT_Product_ID = "W9TI0JaXlu";
const String MQTT_Token ="version=2018-10-31&res=products%2FW9TI0JaXlu%2Fdevices%2FDHT22&et=1759306118&method=sha256&sign=g%2Fzk%2BXWjqngMNOkegI42D0dKRZuaAQG9MXXwP4kBjAU%3D";

const String SSID = "TP-LINK_8520";
const String Password = "88488418";

MPU6050Message mpu6050Data;
DHT22Message dht22Data;
MQ135Message mq135Data;
MQ5Message mq5Data;
OtherMessage otherData;

WiFiClient espClient;
PubSubClient client(espClient);

bool isRainy = false;
bool isAblaze = false;

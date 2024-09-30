#include "MPU6050/MPU6050.h"
#include "DHT22/DHT22.h"
#include "EspNow/EspNow.h"
#include "MQ/MQ.h"
#include "OtherSensors/OtherSensors.h"
#include "Snake/Snake.h"
#include "MG90Servo/MG90Servo.h"
#include "MQTT/MQTT.h"
#include "HCSR04/HCSR04.h"

void I2CScanner();
bool wifiConnect();

void setup() {
    Serial.begin(115200);
    // 显示 IIC 通信可用地址及设备 MAC 地址
    wifiConnect();
    I2CScanner();
    Serial.println(("The MacAddress of Slave Machine is: ")+ String(WiFi.macAddress()));


    // 传感器模块初始化
    initEspNow();
    initMPU6050();
    initDHT22();
    initMQ135();
    initMQ5();
    initFire();
    initRaindrop();
    initLM393();
    initHCSR04();
    Serial.println(MQTT_Token.c_str());
    //
    // 辅助功能初始化
    initSnake();
    // initMG90();

    connectOneNet();

    Serial.println(F("-------------Init Over--------------"));
}

void loop() {
    unsigned long currentMillis = millis();
    keepOneNETConnected();

    if (!client.connected()) {
        connectOneNet();
    }

    if (currentMillis - previousMillisMPU6050 >= intervalMPU6050) {
        previousMillisMPU6050 = currentMillis;
        loopMPU6050();
    }

    if (currentMillis - previousMillisDHT22 >= intervalDHT22) {
        previousMillisDHT22 = currentMillis;
        loopDHT22();
    }

    if (currentMillis - previousMillisMQ >= intervalMQ) {
        previousMillisMQ = currentMillis;
        loopMQ135();
        loopMQ5();
    }

    if (currentMillis - previousMillisOther >= intervalOther) {
        previousMillisOther = currentMillis;
        combineLoop();
    }

    if (currentMillis - previousMillisSnake >= intervalSnake) {
        previousMillisSnake = currentMillis;
        loopSnake();
    }
    //
    // if (currentMillis - previousMillisMG90 >= intervalMG90) {
    // previousMillisMG90 = currentMillis;
    //     // loopMG90();
    // }

    if (currentMillis - previousMillisHCSR04 >= intervalHCSR04) {
        previousMillisHCSR04 = currentMillis;
        loopHCSR04();
    }

}







// 辅助函数 ——————————————————————————————————————————————————————————————————————————
void I2CScanner() {
    Wire.begin();  // 初始化I2C总线
    Serial.begin(115200);

    // 扫描所有可能的I2C地址
    for (uint8_t address = 1; address < 127; address++) {
        Wire.beginTransmission(address);
        uint8_t error = Wire.endTransmission();

        if (error == 0) {
            Serial.print("I2C device found at address 0x");
            if (address < 16) Serial.print("0");
            Serial.println(address, HEX);
        }
    }
}

bool wifiConnect() {
    WiFi.disconnect(true); // 先断开再进行连接，重新获取自动分配的IP地址

    Serial.println("Connecting to " + SSID);
    Serial.println("Password:" + Password);
    WiFi.begin(SSID, Password);
    int WifiConnectCount = 0;
    // WiFi 连接次数过多时，才算是失败
    while (WiFi.status() != WL_CONNECTED) {
        WifiConnectCount++;
        if (WifiConnectCount >= 20) {
            Serial.printf("\n-- Wifi Connect Fail! --\n");
            break;
        }
        vTaskDelay(100);
    }

    if (WiFi.status() == WL_CONNECTED) {
        // 向串口输出连接成功信息和IP地址
        Serial.printf("\n -- WiFi Connect Success! --\n");
        Serial.printf("IP address: ");
        Serial.println(WiFi.localIP()); // 这里不能用String()强转化，和库不兼容
        Serial.println("Free Heap: " + String(ESP.getFreeHeap()));
        return true;
    }
    return 0;
}

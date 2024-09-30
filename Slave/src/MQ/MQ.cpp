//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "MQ.h"

/*
    Exponential regression:
    GAS      | a      | b
    CO       | 605.18 | -3.937
    Alcohol  | 77.255 | -3.18
    CO2      | 110.47 | -2.862
    Toluen   | 44.947 | -3.445
    NH4      | 102.2  | -2.473
    Aceton   | 34.668 | -3.369
*/

MQUnifiedsensor MQ135("ESP32", Voltage_Resolution, ADC_Bit_Resolution, MQ135_PIN, "MQ-135");

MQUnifiedsensor MQ5("ESP32", Voltage_Resolution, ADC_Bit_Resolution, MQ5_PIN, "MQ-5");

void initMQ135() {
    pinMode(MQ135_PIN, INPUT);
    MQ135.setRegressionMethod(1); // 数学模型：1 是指数型 / 2 是线性

    MQ135.init();
    Serial.print("Calibrating MQ-135 sensors, please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++) {
        MQ135.update(); // 更新数据，Arduino 将从模拟引脚读取电压
        calcR0 += MQ135.calibrate(RatioMQ135CleanAir); // 使用清洁空气中的典型比值进行校准
        Serial.print(".");
    }
    R0 = calcR0 / 10;
    MQ135.setR0(calcR0 / 10); // 设置 R0 值
    Serial.println(F("  Finish calibrating!."))
;

    if (isinf(calcR0)) {
        Serial.println(F("Warning: Connection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"))
;
        while (1);
    }
    if (calcR0 == 0) {
        Serial.println(F("Warning: Connection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"))
;
        while (1);
    }
}

void loopMQ135() {
    MQ135.update();

    // 读取 CO 浓度
    MQ135.setA(605.18);
    MQ135.setB(-3.937);
    float coPPM = MQ135.readSensor();
    mq135Data.coPPM = coPPM;

    // 读取 Alcohol 浓度
    MQ135.setA(77.255);
    MQ135.setB(-3.18);
    float alcoholPPM = MQ135.readSensor();
    mq135Data.alcoholPPM = alcoholPPM;

    // 读取 CO2 浓度
    MQ135.setA(110.47);
    MQ135.setB(-2.862);
    float co2PPM = MQ135.readSensor();
    mq135Data.co2PPM = co2PPM;

    // 读取 Toluene 浓度
    MQ135.setA(44.947);
    MQ135.setB(-3.445);
    float toluenePPM = MQ135.readSensor();
    mq135Data.toluenePPM = toluenePPM;

    // 读取 NH4 浓度
    MQ135.setA(102.2);
    MQ135.setB(-2.473);
    float nh4PPM = MQ135.readSensor();
    mq135Data.nh4PPM = nh4PPM;

    // 读取 Acetone 浓度
    MQ135.setA(34.668);
    MQ135.setB(-3.369);
    float acetonePPM = MQ135.readSensor();
    mq135Data.acetonePPM = acetonePPM;

    // 打印所有结果
    Serial.print("CO: ");
    Serial.print(coPPM);
    Serial.println(F(" PPM"))
;

    Serial.print("Alcohol: ");
    Serial.print(alcoholPPM);
    Serial.println(F(" PPM"))
;

    Serial.print("CO2: ");
    Serial.print(co2PPM);
    Serial.println(F(" PPM"))
;

    Serial.print("Toluene: ");
    Serial.print(toluenePPM);
    Serial.println(F(" PPM"))
;

    Serial.print("NH4: ");
    Serial.print(nh4PPM);
    Serial.println(F(" PPM"))
;

    Serial.print("Acetone: ");
    Serial.print(acetonePPM);
    Serial.println(F(" PPM"))
;

    // 发送数据到主机
    esp_err_t result = esp_now_send(masterMACAddress, (uint8_t *) &mq135Data, sizeof(mq135Data));
    if (result == ESP_OK) {
        Serial.println(F("Sent MQ135 data successfully"));
        Serial.println(F("----------------------------"));
    } else {
        Serial.println(F("Error sending the MQ135 data"));
        Serial.println(F("----------------------------"));
    }
}

void initMQ5() {
    pinMode(MQ5_PIN, INPUT);
    MQ5.setRegressionMethod(1); // 数学模型：1 是指数型 / 2 是线性

    MQ5.init();
    Serial.print("Calibrating MQ-5 sensor, please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++) {
        MQ5.update(); // 更新数据，Arduino 将从模拟引脚读取电压
        calcR0 += MQ5.calibrate(RatioMQ5CleanAir); // 使用清洁空气中的典型比值进行校准
        Serial.print(".");
    }

    // Todo 这一步骤出现了 BUG，故调试使用 MQ135 的校准数据
    MQ5.setR0(R0); // 设置 R0 值
    Serial.println(F("  Finish calibrating!."))
;
    //
    // if (isinf(calcR0)) {
    //     Serial.println(F("Warning: Connection issue, R0 is infinite (Open circuit detected) please check your wiring and supply"))
;
    //     while (1);
    // }
    // if (calcR0 == 0) {
    //     Serial.println(F("Warning: Connection issue found, R0 is zero (Analog pin shorts to ground) please check your wiring and supply"))
;
    //     while (1);
    // }
}

void loopMQ5() {
    MQ5.update();

    // 读取 H2 浓度
    MQ5.setA(1163.8);
    MQ5.setB(-3.874);
    float h2PPM = MQ5.readSensor();
    mq5Data.h2PPM = h2PPM;

    // 读取 LPG 浓度
    MQ5.setA(80.897);
    MQ5.setB(-2.431);
    float lpgPPM = MQ5.readSensor();
    mq5Data.lpgPPM = lpgPPM;

    // 读取 CH4 浓度
    MQ5.setA(177.65);
    MQ5.setB(-2.56);
    float ch4PPM = MQ5.readSensor();
    mq5Data.ch4PPM = ch4PPM;

    // 打印所有结果
    Serial.print("H2: ");
    Serial.print(h2PPM);
    Serial.println(F(" PPM"))
;

    Serial.print("LPG: ");
    Serial.print(lpgPPM);
    Serial.println(F(" PPM"))
;

    Serial.print("CH4: ");
    Serial.print(ch4PPM);
    Serial.println(F(" PPM"))
;

    // 发送数据到主机
    esp_err_t result = esp_now_send(masterMACAddress, (uint8_t *) &mq5Data, sizeof(mq5Data));
    if (result == ESP_OK) {
        Serial.println(F("Sent MQ5 data successfully"));
        Serial.println(F("----------------------------"));
    } else {
        Serial.println(F("Error sending the MQ5 data"));
        Serial.println(F("----------------------------"));
    }
}

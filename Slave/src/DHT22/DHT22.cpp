//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "DHT22.h"

DHT dht(DHT22_PIN, DHTTYPE);

void initDHT22() {
    pinMode(DHT22_PIN, INPUT);
    dht.begin();
}

void loopDHT22() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println(F("Failed to read data from the DHT sensor"));
    }

    Serial.println("Humidity: " + String(humidity) + " %");
    Serial.println(("Temperature: " + String(temperature) + " *C"));

    dht22Data.humidity = humidity;
    dht22Data.temperature = temperature;

    // 发送数据到主机
    esp_err_t result = esp_now_send(masterMACAddress, (uint8_t *) &dht22Data, sizeof(dht22Data));
    if (result == ESP_OK) {
        Serial.println(F("Sent DHT22 data successfully"));
        Serial.println(F("----------------------------"));
    } else {
        Serial.println(F("Error sending the DHT22 data"));
        Serial.println(F("----------------------------"));
    }
}

//
// Created by Deralive (10235101526) on 2024/9/1.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#include "MQTT.h"
#include "Ticker.h"

int postMessageID = 0;
Ticker ticker;
extern DHT22Message dht22data;
extern MQ135Message mq135Data;

void connectOneNet() {
    client.setServer(MQTT_Server.c_str(), MQTT_Port);
    client.connect(MQTT_Device_ID.c_str(), MQTT_Product_ID.c_str(), MQTT_Token.c_str());
    client.setCallback(mqttCallback);

    if (client.connected()) {
        Serial.println(F("Connected to OneNET!"));
    } else {
        Serial.println(F("Failed to connect OneNeT!"));
    }

    bool isSubscribeProperty = client.subscribe(ONENET_TOPIC_PROP_SET); //订阅设备属性设置请求
    if (isSubscribeProperty) {
        Serial.println(F("Subscribe Device Property Set Successfully!"));
    } else {
        Serial.println(F("Subscribe Device Property Set Failed!"));
    }

    bool isSubscribeUpdata = client.subscribe(ONENET_TOPIC_PROP_POST_REPLY); //订阅设备属性上报响应
    if (isSubscribeUpdata) {
        Serial.println(F("Subscribe Device Data Sending Successfully!"));
    } else {
        Serial.println(F("Subscribe Device Data Sending Failed!"));
    }
    ticker.attach(3,OneNET_Prop_Post);
}

void keepOneNETConnected() {
    client.loop();
}

void OneNET_Prop_Post() {
    if (client.connected()) {
        char parameters[256];
        char jsonBuff[256];
        // 发送湿温度数据
        sprintf(parameters, "{\"temperature\":{\"value\":%.2f},\"humidity\":{\"value\":%.2f}}",dht22Data.temperature,dht22Data.humidity);
        Serial.println(parameters);
        sprintf(jsonBuff,ONENET_TOPIC_PROP_FORMAT,postMessageID++,parameters);
        Serial.println(jsonBuff);
        bool isUpData = client.publish(ONENET_TOPIC_PROP_POST, jsonBuff);
        // 发送是否下雨
        if (isRainy) {
            sprintf(parameters, "{\"isRainy\":{\"value\":true}}");
        } else {
            sprintf(parameters, "{\"isRainy\":{\"value\":false}}");
        }
        Serial.println(parameters);
        sprintf(jsonBuff,ONENET_TOPIC_PROP_FORMAT,postMessageID++,parameters);
        Serial.println(jsonBuff);
        client.publish(ONENET_TOPIC_PROP_POST, jsonBuff);

        // 发送是否着火
        if (isAblaze) {
            sprintf(parameters, "{\"isAblaze\":{\"value\":true}}");
        } else {
            sprintf(parameters, "{\"isAblaze\":{\"value\":false}}");
        }
        Serial.println(parameters);
        sprintf(jsonBuff,ONENET_TOPIC_PROP_FORMAT,postMessageID++,parameters);
        Serial.println(jsonBuff);
        isUpData = client.publish(ONENET_TOPIC_PROP_POST, jsonBuff);
        if (isUpData) {
            Serial.println(F("Send Data To MQTT Server Successfully!"));
        } else {
            Serial.println(F("Send Data To MQTT Server Failed!"));
        }

        sprintf(parameters, "{\"Brightness\":{\"value\":%d}}",otherData.brightness);
        Serial.println(parameters);
        sprintf(jsonBuff,ONENET_TOPIC_PROP_FORMAT,postMessageID++,parameters);
        Serial.println(jsonBuff);
        isUpData = client.publish(ONENET_TOPIC_PROP_POST, jsonBuff);
        if (isUpData) {
            Serial.println(F("Send Data To MQTT Server Successfully!"));
        } else {
            Serial.println(F("Send Data To MQTT Server Failed!"));
        }

        sprintf(parameters, "{\"Brightness\":{\"value\":%d}}",otherData.brightness);
        Serial.println(parameters);
        sprintf(jsonBuff,ONENET_TOPIC_PROP_FORMAT,postMessageID++,parameters);
        Serial.println(jsonBuff);
        isUpData = client.publish(ONENET_TOPIC_PROP_POST, jsonBuff);
        if (isUpData) {
            Serial.println(F("Send Data To MQTT Server Successfully!"));
        } else {
            Serial.println(F("Send Data To MQTT Server Failed!"));
        }

        sprintf(parameters, "{\"smoke\":{\"value\":%.2f}}",mq135Data.alcoholPPM);
        Serial.println(parameters);
        sprintf(jsonBuff,ONENET_TOPIC_PROP_FORMAT,postMessageID++,parameters);
        Serial.println(jsonBuff);
        isUpData = client.publish(ONENET_TOPIC_PROP_POST, jsonBuff);
        if (isUpData) {
            Serial.println(F("Send Data To MQTT Server Successfully!"));
        } else {
            Serial.println(F("Send Data To MQTT Server Failed!"));
        }

    }
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    // 将接收到的消息转换为字符串
    char message[length + 1];
    strncpy(message, (char*)payload, length);
    message[length] = '\0';

    // 打印主题和消息内容
    Serial.print("Received message from topic: ");
    Serial.println(topic);
    Serial.print("Message: ");
    Serial.println(message);
}
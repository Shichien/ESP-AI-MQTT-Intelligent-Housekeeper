//
// Created by Deralive (10235101526) on 2024/9/1.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#ifndef MQTT_H
#define MQTT_H

#include "configuration.h"

#define ONENET_TOPIC_PROP_POST "$sys/W9TI0JaXlu/DHT22/thing/property/post" // 设备属性上报请求
#define ONENET_TOPIC_PROP_POST_REPLY "$sys/W9TI0JaXlu/DHT22/thing/property/post/reply" // 设备属性上报响应
#define ONENET_TOPIC_PROP_SET "$sys/W9TI0JaXlu/DHT22/thing/property/set" // 设备属性设置请求
#define ONENET_TOPIC_PROP_SET_REPLY "$sys/W9TI0JaXlu/DHT22/thing/property/set_reply" // 设备属性设置响应
#define ONENET_TOPIC_PROP_FORMAT "{\"id\":\"%u\",\"version\":\"1.0\",\"params\":%s}"

extern int postMessageID;

void connectOneNet();
void keepOneNETConnected();
void OneNET_Prop_Post();
void mqttCallback(char* topic, byte* payload, unsigned int length);

#endif //MQTT_H

# Maker-practice
School of Software Engineering, East China Normal University, Maker Practice Course Design

# ESP AI Intelligent Housekeeper
本项目以 ESP32 为主体，使用 Master（主机）与 Slave（从机）通过 ESP-NOW 无线传输协议进行通信
将 Slave 传感器（置于封闭空间中）数据读入 Master（便携手持主机），通过接入星火大模型，实时进行语音识别，通过语音获取当前室内相关信息，调用天气 API 获取天气信息等。

# Slave 从机
从机中成功驱动了许多传感器，分别如下，可以查看相关的实现，当作 Examples：
- DHT22 湿温度传感器
- MQ5、MQ135、MQ4 等气体传感器    
- RainDrop 雨滴传感器
- 基于 LM393 的光照传感器
- 火焰传感器  
- 使用 Servo.h 库驱动 MG90 电机                 
- 将传感器数据连接到 OneNET 官方网站（基于MQTT协议）
- 将传感器数据实时通过 ESP-NOW 协议传输至 Master 主机

## 硬件信息
- ESP-Wroom-32开发板
- DHT22 湿温度传感器
- MPU6050 六轴加速度传感器
- MQ135 有毒气体检测传感器
- 光照传感器、火焰传感器
## 配置信息：
- MAC地址：1C:69:20:2B:9D:58

# Master 主机

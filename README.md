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
主机中成功驱动了讯飞语音大模型，包括：TSS、IAT、LLM 等。

## 项目环境及工具列表
本项目设计的环境为 Windows 11，开发板编程使用 Clion Platform，
选择 Upesy_Wroom 开发环境，Arduino 框架，模拟仿真平台使用 Wokwi Simulator，
串口监视器选用 VOFA+ 1.3.10，波特率为115200（8N1），代码使用 Vim 编写，
课程报告使用 LaTeX 撰写，并使用 Git 进行版本管理。

#### 注意：所有工程文件已一并附上。
#### 包括项目代码、课程报告LateX源代码、视频剪辑及海报设计工程文件一并已上传。

## Notice 1

0. 参考项目置于 \bib 文件夹之中
1. 海报文件使用 Adobe Illustrator 制作，部分工程素材由大模型 DALL·E 生成 
2. 展示视频使用 Adobe Premiere Pro 制作，所有工程素材来自个人创作，3D 基准面使用 Adobe After Effects 制作
3. PPT 使用 LateX + Beamer 制作，结合 WPS PPT 进行展示，使用 OBS Studio 进行录制

## Notice 2

1. 该项目分为主机（Master）、从机（Slave）、以及可添加的多个侧机（Side）
2. 主机承担的职责是主控中心，负责运行语音识别与语音播报、大模型对话；
3. 从机承担的职责是获取传感器数据，并连接至 MQTT 服务器，通过 ESP-NOW 协议无线传输给主机。
4. 为方便调试，主机、从机置于同一块大型面包板上，由于主机和从机之间本身实现的是无线通信，实际可将其分开，最大距离约为10米左右。
5. 侧机（Side）可以添加约 20 个，这是基于 ESP-NOW 协议的最大同机数量。

//
// Created by Deralive (10235101526) on 2024/8/29.
// Academic Contact: 10235101526 @ stu.ecnu.edu.cn
// Business Contact: Deralive @ 163.com / 2642136260 @ qq.com
//

#ifndef MPU6050_H
#define MPU6050_H

#include "configuration.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

extern float i;                                     // 计算偏移量时的循环次数
extern float ax_offset, ay_offset;                  // x, y轴的加速度偏移量
extern float gx_offset, gy_offset;                  // x, y轴的角速度偏移量

extern float rad2deg;                               // 弧度到角度的换算系数
extern float roll_v, pitch_v;                       // 换算到x, y轴上的角速度

extern float now, lasttime, dt;                     // 定义微分时间

extern float gyro_roll, gyro_pitch;                 // 陀螺仪积分计算出的角度，先验状态
extern float acc_roll, acc_pitch;                   // 加速度计观测出的角度，观测状态
extern float k_roll, k_pitch;                       // 卡尔曼滤波后估计出的最优角度，最优估计状态

extern float e_P[2][2];                             // 误差协方差矩阵P
extern float k_k[2][2];                             // 卡尔曼增益矩阵K

extern void onDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);
void initMPU6050();
void loopMPU6050();

#endif //MPU6050_H

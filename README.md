<!--
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-30 15:57:13
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-07 15:06:12
 * @FilePath: \20220902\README.md
 * @Description: 
 * 
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved. 
-->
# ESP32+SD卡+触摸显示屏+MPU6050

## 创建时间
20220902

## 目的
1. 创建两个的按钮界面，用于执行不同功能。
2. 按钮界面添加重力圈的功能。
3. 按钮界面添加图片库。图片库来源是本地存储和sd卡存储，sd卡存储png和bin两种格式。
   
## 硬件
1. 开发板：esp32(devkitv1)
2. 电容触摸lcd显示屏
   
   1. lcd显示屏驱动ic： st7789， 像素240*320， spi接口
   2. 触摸屏驱动ic：CST816S, 像素240*320， iic接口(SDA:21  SCL:22 addr: 0X15)
3. mpu6050 (iic接口 SDA:21 SCL:22 addr：0x68)
4. sd卡转接板(spi接口 MISO:26 MOSI:13 CS:15 CLK:14)
5. sd卡（SanDisk Ultra）

## 软件
platformIO IDE库：
1. GFX Library for Arduino
2. Adafruit MPU6050
3. lvgl
4. CST816S(非官方)
## 接线
| esp32 | 触摸显示屏 | mpu6050 | SD转接板 |
| :---: | :--------: | :-----: | :------: |
|  GND  |    GND     |   GND   |   GND    |
|  3v3  |    3.3V    |   VCC   |   VCC    |
|  D15  |            |         |    CS    |
|  D14  |            |         |   CLK    |
|  D26  |            |         |   MISO   |
|  D13  |            |         |   MOSI   |
|  D4   |    INTR    |
|  D5   |    TRS     |         |
|  D21  |    TDA     |   SDA   |
|  D22  |    TCK     |   SCL   |
|  RX2  |    RES     |
|  D23  |    SDA     |
|  D18  |    SCL     |
|  D33  |     CS     |
|  D32  |     DC     |
|  D25  |    BLK     |


 ![](image/01.png)

 ## 编写流程
我不想写了，写注释吧。。。。。

## 结果
![image](https://github.com/BlueBoxChamil/LVGL-clock/tree/master/image/../../../../../../../image/gif-1.gif)
/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-30 15:15:59
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-07 10:53:06
 * @FilePath: \20220902\lib\hhh\my_gravity_line.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef _MY_GRID_LINE_H_
#define _MY_GRID_LINE_H_

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include "lvgl.h"
#include <Arduino.h>
#include "my_lvgl.h"

void mpu6050_init();
float Rad2Deg(float r);
float GetDeg(float n, int direct);
void set_angle(void *obj, int32_t v);
void mpu6050_start(lv_obj_t *parent);
static void back_button_func(lv_event_t *event);

#endif
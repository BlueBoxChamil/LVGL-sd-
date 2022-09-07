/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-02 13:47:42
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-07 10:54:30
 * @FilePath: \20220902\lib\hhh\my_lvgl.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef _MY_lVGL_H_
#define _MY_lVGL_H_

#include <Arduino.h>
#include "lvgl.h"
#include "my_sd.h"
#include "my_gravity_line.h"
#include "my_img.h"

void test_for_demo();

void main_demo(lv_obj_t *parent);
static void b1_button_func(lv_event_t *event);
static void b2_button_func(lv_event_t *event);

#endif

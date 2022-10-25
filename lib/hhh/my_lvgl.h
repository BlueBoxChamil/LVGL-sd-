/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-07 13:08:28
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-16 10:59:38
 * @FilePath: \20220902-1\lib\hhh\my_lvgl.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
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
#include "my_lv_style.h"
#include "my_clock.h"

extern bool main_demo_open;

void test_for_demo();
void main_demo(lv_obj_t *parent);
void start_demo();

static void start_btn_call_back(lv_event_t *event);

void my_lvgl_func_init();
void my_lvgl_func_button_init(lv_obj_t *btn, lv_obj_t *label, char *name, lv_event_cb_t call_back);

void my_lvgl_func_0_callback(lv_event_t *event);
void my_lvgl_func_1_callback(lv_event_t *event);
void my_lvgl_func_2_callback(lv_event_t *event);

bool is_object_null(lv_obj_t *temp);
lv_obj_t *switch_button(uint8_t i, lv_obj_t *temp);
lv_obj_t *switch_lable(lv_obj_t *btn_temp, lv_obj_t *label_temp);

static void scroll_event_cb(lv_event_t *e);
static void release_button_func(lv_event_t *e);
static void drag_event_handler(lv_event_t *e);

void back_button_start_func();

#endif

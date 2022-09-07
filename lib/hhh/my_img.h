/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-30 17:08:13
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-07 10:51:15
 * @FilePath: \20220902\lib\hhh\my_img.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef _MY_IMG_H_
#define _MY_IMG_H_

#include "lvgl.h"
#include <Arduino.h>
#include "my_lvgl.h"

void my_img_init(lv_obj_t *parent);
void my_img_init_0(lv_obj_t *parent);
void my_img_init_1(lv_obj_t *parent);
void my_img_init_2(lv_obj_t *parent);

static void back_button_func(lv_event_t *event);

#endif
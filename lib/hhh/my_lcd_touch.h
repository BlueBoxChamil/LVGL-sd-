/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-02 13:15:35
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-02 13:32:55
 * @FilePath: \20220902\src\my_lcd_touch.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef _MY_LCD_TOUCH_H_
#define _MY_LCD_TOUCH_H_

#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <CST816S.h>
#include "lvgl.h"

void my_touch_init();
void my_lcd_init();
void lvgl_creat_init();

void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p);
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data);

#endif
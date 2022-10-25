/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-02 09:53:11
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-13 13:47:09
 * @FilePath: \20220902-1\src\main.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include <Arduino.h>
#include "my_lcd_touch.h"
#include "my_sd.h"
#include "my_lvgl.h"
#include "my_gravity_line.h"
#include "my_hardware_button.h"

void setup(void)
{
  Serial.begin(115200);
  // pinMode(27, OUTPUT);
  // digitalWrite(27, HIGH);
  my_button_init();

  //触摸屏初始化
  my_touch_init();

  //显示屏初始化
  my_lcd_init();

  //获取网络时间
  wifi_time_get();

  // mpu6050初始化
  mpu6050_init();

  // lvgl初始化配置
  lvgl_creat_init();

  // sd卡初始化
  my_sd_init();

  //文件系统初始化
  lv_fs_fatfs_init();

  lv_png_init();

  //控件配置
  test_for_demo();

  // write_file();
  // read_file();
  // check_dir();

  Serial.print("end\r\n");
}

void loop()
{
  lv_timer_handler(); /* let the GUI do its work */
  delay(5);
  button.tick();

  // delay(10);
}
/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-08 14:22:51
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-13 13:20:25
 * @FilePath: \20220902-1\lib\hhh\my_hardware_button.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef _MY_HARDWARE_BUTTON_H_
#define _MY_HARDWARE_BUTTON_H_

#include <Arduino.h>
#include "OneButton.h"

#include "my_img.h"
#include "my_gravity_line.h"
#include "my_clock.h"

extern OneButton button;

void doubleclick();
void click();
void longPressStart();
void duringLongPress();
void longPressStop();
void attachPressStart();
void my_button_init();

#endif

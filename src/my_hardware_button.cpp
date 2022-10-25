/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-08 14:21:49
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-16 10:59:51
 * @FilePath: \20220902-1\src\my_hardware_button.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_hardware_button.h"

//按钮引脚
#define PIN_INPUT 19

OneButton button(PIN_INPUT, true);

void doubleclick()
{
    Serial.println("doubleclick");
}
void click()
{
    // Serial.println("click");
    if (my_img_open == true)
    {
        back_button_img_func();
    }
    else if (my_gravity_line == true)
    {
        back_button_gravity_line_func();
    }
    else if (my_clock_open == true)
    {
        back_button_clock_func();
    }
    else if (main_demo_open == true)
    {
        back_button_start_func();
    }
}
void longPressStart()
{
    Serial.println("longPressStart");
}
void duringLongPress()
{
    if (button.isLongPressed())
    {
        // Serial.print("duringLongPress:");
        Serial.println(button.getPressedTicks());
        delay(50);
    }
}
void longPressStop()
{
    Serial.println("longPressStop");
}
void attachPressStart()
{
    Serial.println("attachPressStart");
    Serial.println(digitalRead(PIN_INPUT));
}

void my_button_init()
{
    button.reset(); //清除一下按钮状态机的状态
    button.attachClick(click);
    // button.attachDoubleClick(doubleclick);
    // button.attachLongPressStart(longPressStart);
    // button.attachDuringLongPress(duringLongPress);
    // button.attachLongPressStop(longPressStop);
    // button.attachPressStart(attachPressStart); //按下键就会持续触发
}
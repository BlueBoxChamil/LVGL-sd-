/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-26 16:07:31
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-07 10:53:39
 * @FilePath: \20220902\src\my_gravity_line.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_gravity_line.h"

Adafruit_MPU6050 mpu;
float base_val[] = {10, 10, 10.5};
static lv_obj_t *label;
static lv_obj_t *back_btn;
static lv_obj_t *arc;

enum Direction
{
    X = 0,
    Y = 1,
    Z = 2
};

/**
 * @brief mpu6050陀螺仪初始化
 *
 */
void mpu6050_init()
{
    if (!mpu.begin())
    {
        Serial.println("Failed to find MPU6050 chip");
        while (1)
        {
            delay(10);
        }
    }
    Serial.printf("MPU6050 Found!\r\n");
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
}

float Rad2Deg(float r)
{
    return (180 / 3.1415) * r;
}

/**
 * @brief 获取与XYZ轴的角度
 *
 * @param n
 * @param direct
 * @return float
 */
float GetDeg(float n, int direct)
{
    float prop = n / base_val[direct];
    prop = prop > 1 ? 1 : prop;
    prop = prop < -1 ? -1 : prop;
    return Rad2Deg(acos(prop));
}

/*
                ^(x)
                |
                |
          2     |      3
                |
    <---------------------------
     (y)        |
                |
          1     |      4
                |
*/

/**
 * @brief 设置与水平面的角度
 *
 * @param obj
 * @param v
 */
void set_angle(void *obj, int32_t v)
{
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    float AccX = a.acceleration.x;
    float AccY = a.acceleration.y;
    float AglX = GetDeg(AccX, X);
    float AglY = GetDeg(AccY, Y);

    float deg_360;

    //第一象限
    if ((AccX <= 0) && (AglY <= 90))
    {
        deg_360 = ((90 - AglY) / 360 * 100);
    }
    //第二象限
    else if ((AccX > 0) && (AglY <= 90))
    {
        deg_360 = ((AglY + 90) / 360 * 100);
    }
    //第三象限
    else if ((AccX > 0) && (AglY > 90))
    {
        deg_360 = ((AglY + 90) / 360 * 100);
    }
    //第四象限
    else if ((AccX <= 0) && (AglY > 90))
    {
        deg_360 = ((180 - AglY + 270) / 360 * 100);
    }

    // printf("deg_360 = %f\r\n\r\n", deg_360);
    //设置角度
    lv_arc_set_value((lv_obj_t *)obj, deg_360);
    // lv_arc_set_value((lv_obj_t *)obj, v);
    //设置角度数值
    lv_label_set_text_fmt(label, "%d", (int)deg_360);
}

/**
 * @brief 启动陀螺仪
 *
 * @param parent
 */
void mpu6050_start(lv_obj_t *parent)
{
    /*Create an Arc*/
    arc = lv_arc_create(parent);

    //设置弧度旋转90度，弧度默认0°在右边，90°在下边，180°在左边， 270°在上边，360°在右边和0°重合
    lv_arc_set_rotation(arc, 90);
    //设置背景的弧度范围为0°~360°
    lv_arc_set_bg_angles(arc, 0, 360);
    //删除旋钮
    lv_obj_remove_style(arc, NULL, LV_PART_KNOB); /*Be sure the knob is not displayed*/
    //清楚通过点击调整数值
    lv_obj_clear_flag(arc, LV_OBJ_FLAG_CLICKABLE); /*To not allow adjusting by click*/
    //设置为中心
    lv_obj_center(arc);

    label = lv_label_create(parent);
    lv_label_set_text(label, "Hello Arduino! (V8.0.X)");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 60);

    back_btn = lv_btn_create(parent);
    lv_obj_set_size(back_btn, 100, 50);
    // lv_obj_set_pos(back_btn, 100, 80);
    lv_obj_align(back_btn, LV_ALIGN_CENTER, 0, 100);
    lv_obj_add_event_cb(back_btn, back_button_func, LV_EVENT_ALL, NULL);

    lv_obj_t *label1 = lv_label_create(back_btn);
    lv_label_set_text(label1, "back");
    lv_obj_center(label1);
    lv_obj_add_flag(label1, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);

    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, arc);
    lv_anim_set_exec_cb(&a, set_angle);
    lv_anim_set_time(&a, 50);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE); /*Just for the demo*/
    lv_anim_set_values(&a, 0, 100);
    lv_anim_start(&a);
}

/**
 * @brief 返回按钮回调函数
 *
 * @param event
 */
static void back_button_func(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    if (code == LV_EVENT_CLICKED)
    {
        //删除动画
        lv_anim_del(arc, set_angle);
        lv_obj_del(label);
        lv_obj_del(arc);
        lv_obj_del(back_btn);
        main_demo(lv_scr_act());
    }
}
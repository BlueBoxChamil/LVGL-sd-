/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-02 13:47:34
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-07 10:55:35
 * @FilePath: \20220902\src\my_lvgl.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_lvgl.h"

static lv_obj_t *tv;

void test_for_demo()
{
    //主题界面
    lv_theme_default_init(NULL, lv_palette_main(LV_PALETTE_GREEN), lv_palette_main(LV_PALETTE_RED), LV_THEME_DEFAULT_DARK,
                          LV_FONT_DEFAULT);

    //主界面
    main_demo(lv_scr_act());
}

static lv_obj_t *b1_btn;
static lv_obj_t *b2_btn;

void main_demo(lv_obj_t *parent)
{
    b1_btn = lv_btn_create(parent);
    lv_obj_set_size(b1_btn, 50, 40);
    lv_obj_center(b1_btn);
    lv_obj_add_event_cb(b1_btn, b1_button_func, LV_EVENT_ALL, NULL);
    lv_obj_t *label1 = lv_label_create(b1_btn);
    lv_label_set_text(label1, "img");
    lv_obj_center(label1);
    lv_obj_add_flag(label1, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);

    b2_btn = lv_btn_create(parent);
    lv_obj_set_size(b2_btn, 100, 40);
    lv_obj_align(b2_btn, LV_ALIGN_CENTER, 0, 100);
    lv_obj_add_event_cb(b2_btn, b2_button_func, LV_EVENT_ALL, NULL);
    lv_obj_t *label2 = lv_label_create(b2_btn);
    lv_label_set_text(label2, "mpu6050");
    lv_obj_center(label2);
    lv_obj_add_flag(label2, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
}

static void b1_button_func(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    if (code == LV_EVENT_CLICKED)
    {
        //删除按钮
        lv_obj_del(b1_btn);
        lv_obj_del(b2_btn);
        //创建一个新的窗口
        my_img_init(lv_scr_act());
    }
}

static void b2_button_func(lv_event_t *event)
{
    lv_event_code_t code = lv_event_get_code(event);
    if (code == LV_EVENT_CLICKED)
    {
        //删除按钮
        lv_obj_del(b1_btn);
        lv_obj_del(b2_btn);
        //创建一个新的窗口
        mpu6050_start(lv_scr_act());
    }
}

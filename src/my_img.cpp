/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-30 17:08:07
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-07 15:04:25
 * @FilePath: \20220902\src\my_img.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_img.h"

static lv_obj_t *tv;
static lv_obj_t *back_btn;

/**
 * @brief 图片库初始化
 *
 * @param parent
 */
void my_img_init(lv_obj_t *parent)
{
    tv = lv_tabview_create(lv_scr_act(), LV_DIR_TOP, 0);
    lv_obj_set_style_text_font(lv_scr_act(), LV_FONT_DEFAULT, 0);
    lv_obj_t *t0 = lv_tabview_add_tab(tv, "");
    lv_obj_t *t1 = lv_tabview_add_tab(tv, "");
    lv_obj_t *t2 = lv_tabview_add_tab(tv, "");

    my_img_init_0(t0);
    my_img_init_1(t1);
    my_img_init_2(t2);

    back_btn = lv_btn_create(parent);
    lv_obj_set_size(back_btn, 50, 40);
    // lv_obj_set_pos(back_btn, 20, 20);
    // lv_obj_center(back_btn);
    lv_obj_align(back_btn, LV_ALIGN_CENTER, 0, 100);
    lv_obj_t *label = lv_label_create(back_btn);
    lv_label_set_text(label, "back");
    lv_obj_center(label);
    lv_obj_add_flag(label, LV_OBJ_FLAG_EVENT_BUBBLE | LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(back_btn, back_button_func, LV_EVENT_ALL, NULL);
}

/**
 * @brief 图片0初始化
 *
 * @param parent
 */
void my_img_init_0(lv_obj_t *parent)
{
    // //秒针 使用官方图像
    // LV_IMG_DECLARE(img_hand)

    // lv_obj_t *img = lv_img_create(parent);
    // lv_img_set_src(img, &img_hand);
    // lv_obj_center(img);
    // sd卡图片
    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, "F:/1.png");
    lv_obj_center(img);
}

/**
 * @brief 图片1初始化
 *
 * @param parent
 */
void my_img_init_1(lv_obj_t *parent)
{
    //分针 使用官方图像
    LV_IMG_DECLARE(fenzhen)

    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, &fenzhen);
    lv_obj_center(img);
}

/**
 * @brief 图片2初始化
 *
 * @param parent
 */
void my_img_init_2(lv_obj_t *parent)
{
    // //时针 使用官方图像
    // LV_IMG_DECLARE(shizhen)

    // lv_obj_t *img = lv_img_create(parent);
    // lv_img_set_src(img, &shizhen);
    // lv_obj_center(img);

    // sd卡图片
    lv_obj_t *bg_img;
    bg_img = lv_img_create(parent);
    lv_img_set_src(bg_img, "F:touxiang.bin");
    lv_obj_center(bg_img);
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
        //删除表盘
        lv_obj_del(tv);
        //删除返回按钮
        lv_obj_del(back_btn);
        //创建一个新的窗口
        main_demo(lv_scr_act());
    }
}
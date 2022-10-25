/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-30 17:08:07
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-13 13:28:27
 * @FilePath: \20220902-1\src\my_img.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_img.h"

bool my_img_open = false;

static lv_obj_t *tv;
// static lv_obj_t *back_btn;

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
}

/**
 * @brief 图片0初始化
 *
 * @param parent
 */
void my_img_init_0(lv_obj_t *parent)
{
    //秒针 使用官方图像
    LV_IMG_DECLARE(fenzhen)

    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, &fenzhen);
    lv_obj_center(img);
}

/**
 * @brief 图片1初始化
 *
 * @param parent
 */
void my_img_init_1(lv_obj_t *parent)
{
    lv_obj_t *img = lv_img_create(parent);
    lv_img_set_src(img, "F:/1.png");
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

void back_button_img_func()
{
    // lv_event_code_t code = lv_event_get_code(event);
    // if (code == LV_EVENT_CLICKED)
    {
        //删除动画
        lv_obj_del(tv);
        my_img_open = false;
        // lv_obj_del(back_btn);
        main_demo(lv_scr_act());
    }
}
/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-09 15:28:02
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-14 14:35:21
 * @FilePath: \20220902-1\src\my_lv_style.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#include "my_lv_style.h"

static lv_style_transition_dsc_t trans;
static const lv_style_prop_t trans_props[] = {
    LV_STYLE_WIDTH,
    LV_STYLE_HEIGHT,
    LV_STYLE_BG_COLOR,
    LV_STYLE_PROP_INV,
};

void my_lv_trans_init()
{
    lv_style_transition_dsc_init(&trans, trans_props,
                                 lv_anim_path_ease_in_out, 500, 0, NULL);
}

static lv_style_t style_trans_0;
static lv_style_t style_trans_1;

void my_lv_trans(lv_obj_t *object, int num, lv_style_selector_t selector, lv_color_t color, lv_coord_t width, lv_coord_t height)
{
    lv_style_t *trans_num;
    if (num == 0)
    {
        trans_num = &style_trans_0;
    }
    else if (num == 1)
    {
        trans_num = &style_trans_1;
    }
    
    lv_style_init(trans_num);
    lv_style_set_transition(trans_num, &trans);

    
    lv_style_set_bg_color(trans_num, color);
    lv_style_set_width(trans_num, width);
    lv_style_set_height(trans_num, height);
    lv_obj_add_style(object, trans_num, selector);
}

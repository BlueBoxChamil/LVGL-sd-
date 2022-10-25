#ifndef _MY_lV_STYLE_H_
#define _MY_lV_STYLE_H_

#include <Arduino.h>
#include "lvgl.h"

void my_lv_trans_init();
void my_lv_trans(lv_obj_t *object,int num,  lv_style_selector_t selector, lv_color_t color, lv_coord_t width, lv_coord_t height);

#endif
/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-08-11 13:56:41
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-13 13:36:05
 * @FilePath: \20220902-1\src\my_clock.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */

#include "my_clock.h"
bool my_clock_open = false;

static lv_obj_t *meter_clock;

static lv_meter_indicator_t *indic_sec;
static lv_meter_indicator_t *indic_min;
static lv_meter_indicator_t *indic_hour;

static bool is_set_time = false;
static int local_sec = 0;
static int local_min = 0;
static int local_hour = 0;

// time
static WiFiUDP ntpUDP;
static NTPClient timeClient(ntpUDP);

static const char *ssid = "Texin-SH-Model";
static const char *password = "yachuang2020";

/**
 * @brief lvgl clock回调函数
 *
 * @param indic
 * @param v
 */
static void set_value_sec(void *indic, int32_t v)
{
    //当前时间是否有效
    if (is_set_time == false)
    {
        //获取当前时间
        GetCurrentTime clock_time = now_time();
        // Serial.printf("time_hour: %d\r\n", clock_time.time_hour);
        // Serial.printf("time_mintues: %d\r\n", clock_time.time_mintues);
        // Serial.printf("time_seconds: %d\r\n", clock_time.time_seconds);

        //将当前时间赋值给表盘时间
        local_sec = clock_time.time_seconds;
        local_min = clock_time.time_mintues;
        //获取时间若超过12小时，减去12小时
        if (clock_time.time_hour >= 12)
        {
            local_hour = clock_time.time_hour - 12;
        }
        else
        {
            local_hour = clock_time.time_hour;
        }
        //为了精确显示，时针也指向60个刻度，因此对hour的时间进行处理
        local_hour = local_hour * 5 + local_min / 12;
        //将指针指向当前位置
        lv_meter_set_indicator_end_value(meter_clock, indic_sec, local_sec);
        lv_meter_set_indicator_end_value(meter_clock, indic_min, local_min);
        lv_meter_set_indicator_end_value(meter_clock, indic_hour, local_hour);

        //当前设置时间有效
        is_set_time = true;
    }

    //  如果对象是秒针
    if ((lv_meter_indicator_t *)indic == indic_sec)
    {
        //秒数 < 59 时，秒数加一
        if (local_sec < 59)
        {
            local_sec++;
            lv_meter_set_indicator_end_value(meter_clock, indic_sec, local_sec);
        }
        //秒数 = 59 时，秒数置为零
        else if (local_sec == 59)
        {
            local_sec = 0;
            lv_meter_set_indicator_end_value(meter_clock, indic_sec, local_sec);

            //分数 < 59 时，分数加一
            if (local_min < 59)
            {
                local_min++;
                lv_meter_set_indicator_end_value(meter_clock, indic_min, local_min);
            }
            //分数 = 59 时，分数置为零
            else if (local_min == 59)
            {
                local_min = 0;
                lv_meter_set_indicator_end_value(meter_clock, indic_min, local_min);

                //小时数 < 59 时，小时的刻度加一
                if (local_hour < 59)
                {
                    local_hour++;
                    lv_meter_set_indicator_end_value(meter_clock, indic_hour, local_hour);
                }
                //小时数 = 59 时，小时的刻度分数置为零
                else if (local_hour == 59)
                {
                    local_hour = 0;
                    lv_meter_set_indicator_end_value(meter_clock, indic_hour, local_hour);
                }
            }
        }
    }
}

/**
 * @brief lvgl时钟显示
 *
 */
void lvgl_clock(lv_obj_t *parent)
{
    //创建一个圆形对象
    meter_clock = lv_meter_create(parent);
    //设置圆形大小220*220
    lv_obj_set_size(meter_clock, 220, 220);
    //将圆形设置到中心
    lv_obj_center(meter_clock);

    //添加60个小刻度用于读取分数和秒数
    lv_meter_scale_t *scale_small = lv_meter_add_scale(meter_clock);
    lv_meter_set_scale_ticks(meter_clock, scale_small, 61, 1, 10, lv_palette_main(LV_PALETTE_RED));
    lv_meter_set_scale_range(meter_clock, scale_small, 0, 60, 360, 270);

    //添加12个大刻度不是用于读取小时数，但是用于添加显示
    lv_meter_scale_t *scale_large = lv_meter_add_scale(meter_clock);
    lv_meter_set_scale_ticks(meter_clock, scale_large, 12, 0, 0, lv_palette_main(LV_PALETTE_RED)); /*12 ticks*/
    lv_meter_set_scale_major_ticks(meter_clock, scale_large, 1, 2, 20, lv_color_black(), 10);      /*Every tick is major*/
    lv_meter_set_scale_range(meter_clock, scale_large, 1, 12, 330, 300);                           /*[1..12] values in an almost full circle*/

    //秒针 使用官方图像
    LV_IMG_DECLARE(img_hand)
    //分针 自定义图像
    LV_IMG_DECLARE(fenzhen)
    //时针 自定义图像
    LV_IMG_DECLARE(shizhen)

    /*Add a the hands from images*/
    //给图片添加句柄
    indic_sec = lv_meter_add_needle_img(meter_clock, scale_small, &img_hand, 5, 5);
    indic_min = lv_meter_add_needle_img(meter_clock, scale_small, &fenzhen, 5, 5);
    indic_hour = lv_meter_add_needle_img(meter_clock, scale_small, &shizhen, 5, 5);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    //给动画添加回调函数
    lv_anim_set_exec_cb(&a, set_value_sec);
    //给动画添加起始值和结束值
    lv_anim_set_values(&a, 0, 60);
    //添加动画重复
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    //添加动画持续时间  以毫秒为单位
    lv_anim_set_time(&a, 1000 * 60);
    //添加变量指针
    lv_anim_set_var(&a, indic_sec);
    //开始动画
    lv_anim_start(&a);
}

/**
 * @brief 配置网络获取时间
 *
 */
void wifi_time_get()
{
    //以秒为单位调整时区的时间,与格林尼治标准时间相差八个时区，因此8*60min = 8* 60 * 60
    timeClient.setTimeOffset(8 * 60 * 60);
    //连接wifi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    //初始化NTPClient
    timeClient.begin();
}

/**
 * @brief 获取当前时间
 *
 * @return GetCurrentTime
 */
GetCurrentTime now_time()
{
    GetCurrentTime t_time;
    //从NTP服务器获取当前日期和时间
    timeClient.update();
    //得到字符串形式的时间数据
    // String get_time = timeClient.getFormattedTime();
    // Serial.printf("time is %s\r\n",get_time);
    //获取时间数据
    t_time.time_hour = timeClient.getHours();
    t_time.time_mintues = timeClient.getMinutes();
    t_time.time_seconds = timeClient.getSeconds();

    return t_time;
}

/**
 * @brief 返回按钮回调函数
 *
 * @param event
 */
void back_button_clock_func()
{
    // lv_event_code_t code = lv_event_get_code(event);
    // if (code == LV_EVENT_CLICKED)
    {
        //删除动画
        lv_anim_del(indic_sec, set_value_sec);
        // lv_anim_del_all();
        //当前设置时间失效
        is_set_time = false;
        //删除表盘
        lv_obj_del(meter_clock);
        my_clock_open = false;
        //创建一个新的窗口
        main_demo(lv_scr_act());
    }
}

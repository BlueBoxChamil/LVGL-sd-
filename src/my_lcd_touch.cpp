#include "my_lcd_touch.h"

#define GFX_BL 25
Arduino_DataBus *bus = new Arduino_ESP32SPI(32 /* DC */, 33 /* CS */, 18 /* SCK */, 23 /* MOSI */, -1 /* MISO */, HSPI /* spi_num */);
Arduino_GFX *gfx = new Arduino_ST7789(bus, 16 /* RST */, 0, true, 240, 320);

#define I2C_SDA 21
#define I2C_SCL 22
#define RST_N_PIN 5
#define INT_N_PIN 4

CST816S touch(I2C_SDA, I2C_SCL, RST_N_PIN, INT_N_PIN);

/**
 * @brief 初始化屏幕
 *
 */
void my_lcd_init()
{
    gfx->begin();
    gfx->fillScreen(BLUE);
    pinMode(GFX_BL, OUTPUT);
    digitalWrite(GFX_BL, HIGH);
}

/**
 * @brief 初始化触摸屏
 *
 */
void my_touch_init()
{
    touch.begin();
}

/**
 * @brief 初始化lvgl
 *
 */
void lvgl_creat_init()
{
    static lv_color_t *disp_draw_buf;
    static lv_disp_draw_buf_t draw_buf;
    static lv_disp_drv_t disp_drv;

    lv_init();
    uint32_t screenWidth = gfx->width();
    uint32_t screenHeight = gfx->height();

#ifdef ESP32
    disp_draw_buf = (lv_color_t *)heap_caps_malloc(sizeof(lv_color_t) * screenWidth * 10, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);
#else
    disp_draw_buf = (lv_color_t *)malloc(sizeof(lv_color_t) * screenWidth * 10);
#endif

    if (!disp_draw_buf)
    {
        Serial.println("LVGL disp_draw_buf allocate failed!");
    }
    else
    {
        //初始化显示缓冲区
        lv_disp_draw_buf_init(&draw_buf, disp_draw_buf, NULL, screenWidth * 10);

        /* Initialize the display */
        lv_disp_drv_init(&disp_drv);
        /* Change the following line to your display resolution */
        disp_drv.hor_res = screenWidth;
        disp_drv.ver_res = screenHeight;
        disp_drv.flush_cb = my_disp_flush;
        disp_drv.draw_buf = &draw_buf;
        lv_disp_drv_register(&disp_drv);

        /* Initialize the (dummy) input device driver */
        static lv_indev_drv_t indev_drv;
        lv_indev_drv_init(&indev_drv);
        indev_drv.type = LV_INDEV_TYPE_POINTER;
        indev_drv.read_cb = my_touchpad_read;
        lv_indev_drv_register(&indev_drv);

        //   /* Create simple label */
        //       *label = lv_label_create(lv_scr_act());
        //   lv_label_set_text(label, "Hello Arduino! (V8.0.X)");
        //   lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 20);
    }
}


/**
 * @brief 显示屏刷新回调函数
 *
 * @param disp
 * @param area
 * @param color_p
 */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

#if (LV_COLOR_16_SWAP != 0)
    gfx->draw16bitBeRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#else
    gfx->draw16bitRGBBitmap(area->x1, area->y1, (uint16_t *)&color_p->full, w, h);
#endif

    lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
/**
 * @brief 触摸屏回调函数
 *
 * @param indev_driver
 * @param data
 */
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{
    uint16_t touchX, touchY;

    bool touched = touch.available();

    if (!touched)
    {
        data->state = LV_INDEV_STATE_REL;
    }
    else
    {
        // if(touch.gesture() == "SINGLE CLICK")
        {
            data->state = LV_INDEV_STATE_PR;

            /*Set the coordinates*/
            data->point.x = touch.data.x;
            data->point.y = touch.data.y;
            // Serial.print("Data x ");
            // Serial.println(touch.data.x);

            // Serial.print("Data y ");
            // Serial.println(touch.data.y);
        }
    }
}

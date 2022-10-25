/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-02 13:34:20
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-08 15:20:35
 * @FilePath: \20220902-1\src\my_sd.cpp
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */

#include "my_sd.h"
#include "lvgl.h"

#define PINN_NUM_MISO 26
#define PINN_NUM_MOSI 13
#define PINN_NUM_CLK 14
#define PINN_NUM_CS 15
// #define PIN_NUM_CD 17

#define MOUNT_POINT "/sdcard"

static const char *TAG = "TF_card";
static const char mount_point[] = MOUNT_POINT; //挂载点 根目录

esp_err_t my_sd_init()
{
    esp_err_t ret;

    // sd mmc卡信息结构
    sdmmc_card_t *card;

    //文件系统挂载配置
    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false, //如果挂载失败， false不是重新分区和格式化
        .max_files = 5,                  //打开文件最大数量
        .allocation_unit_size = 16 * 1024,
    };

    // ESP_LOGI(TAG, "Initializing sd Card");
    printf("Initializing sd Card\r\n");

    // sd spi 主机默认属性配置
    sdmmc_host_t host = SDSPI_HOST_DEFAULT();
    //默认配置为HSPI_HOST， 需更改为VSPI_HOST
    host.slot = VSPI_HOST;

    // spi总线配置
    spi_bus_config_t bus_config = {
        .mosi_io_num = PINN_NUM_MOSI,                 // mosi信号先端口
        .miso_io_num = PINN_NUM_MISO,                 // miso信号线端口
        .sclk_io_num = PINN_NUM_CLK,                  // clk信号线端口
        .quadwp_io_num = -1,                          //不使用
        .quadhd_io_num = -1,                          //不使用
        .max_transfer_sz = 4 * 1024 * sizeof(uint8_t) //最大传输数据大小（字节）
    };

    // spi总线初始化
    ret = spi_bus_initialize((spi_host_device_t)host.slot, &bus_config, host.slot);
    if (ret != ESP_OK)
    {
        ESP_LOGI(TAG, "failed to initialize bus");
        return ret;
    }
    ESP_LOGI(TAG, "host slot (SPI%d)", host.slot);

    /*sd spi设备配置*/
    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = (gpio_num_t)PINN_NUM_CS; // cs片选信号线端口
    // slot_config.gpio_cd = ; //sd卡插拔检测信号线线端口
    slot_config.host_id = (spi_host_device_t)host.slot; //主机id

    /*挂载文件系统*/
    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            ESP_LOGI(TAG, "failed to mount filesystem."
                          "if you want to card to be formatted,"
                          "set the examole_format_if_mount_failerd menuconfig option");
        }
        else
        {
            ESP_LOGI(TAG, "failed to initialize the card (%s)"
                          "make sure sd card line have pull-up resistors in place",
                     esp_ - esp_err_to_name(ret));
        }
        return ESP_FAIL;
    }

    /*sd卡已经初始化，打印sd卡属性*/
    sdmmc_card_print_info(stdout, card);

    return ESP_OK;
}

char write_buf[] = "1234567890ABCDEFGHIJ";
lv_fs_file_t f;
void write_file()
{
    lv_fs_res_t res;
    printf("******6666666********\r\n");
    res = lv_fs_open(&f, "F:/dir/file.txt", LV_FS_MODE_WR);
    if (res != LV_FS_RES_OK)
    {
        ESP_LOGI(TAG, "OPEN DDD failed");
        printf("open file failed = %d\r\n", res);
        return;
    }
    printf("open file \r\n");
    /*写入内容*/
    res = lv_fs_write(&f, write_buf, sizeof(write_buf), NULL);
    if (res != LV_FS_RES_OK)
    {
        printf("write file failed\r\n");
        return;
    }
    printf("write file \r\n");
    lv_fs_close(&f);
}

void read_file()
{
    printf("******************\r\n");
    lv_fs_res_t res;

    char read_buf[32];

    res = lv_fs_open(&f, "F:/dir/file.txt", LV_FS_MODE_RD);
    if (res != LV_FS_RES_OK)
    {
        printf("open file failed = %d\r\n", res);
        return;
    }
    printf("open file\r\n");

    res = lv_fs_seek(&f, 0, LV_FS_SEEK_SET);
    if (res != LV_FS_RES_OK)
    {
        printf("SEEK file failed\r\n");
        return;
    }

    /*读入内容*/
    res = lv_fs_read(&f, read_buf, 3, NULL);
    if (res != LV_FS_RES_OK)
    {
        printf("write file failed\r\n");
        return;
    }
    else
    {
        printf("read buf %s", read_buf);
    }

    printf("read file %c\r\n", read_buf[0]);
    printf("read file %c\r\n", read_buf[1]);
    printf("read file %c\r\n", read_buf[2]);

    lv_fs_close(&f);
}
lv_fs_dir_t d;
void check_dir()
{
    // printf("*********3333*********\r\n");
    lv_fs_res_t res;

    char dir_buf[32];

    res = lv_fs_dir_open(&d, "F:");
    if (res != LV_FS_RES_OK)
    {
        printf("open dir failed = %d\r\n", res);
        return;
    }
    // printf("open dir\r\n");

    while (1)
    {
        printf("88\r\n");
        res = lv_fs_dir_read(&d, dir_buf);
        if (res != LV_FS_RES_OK)
        {
            printf("open dir failed = %d\r\n", res);
            return;
        }
        else
        {
            if (dir_buf[0] == '\0')
            {
                break;
            }
            printf("read dir %s", dir_buf);
        }
    }
    lv_fs_dir_close(&d);
}

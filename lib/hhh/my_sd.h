/*
 * @Author: BlueBoxChamil 283040422@qq.com
 * @Date: 2022-09-02 13:34:27
 * @LastEditors: BlueBoxChamil 283040422@qq.com
 * @LastEditTime: 2022-09-05 16:06:43
 * @FilePath: \20220902\lib\hhh\my_sd.h
 * @Description:
 *
 * Copyright (c) 2022 by BlueBoxChamil 283040422@qq.com, All Rights Reserved.
 */
#ifndef _MY_SD_H_
#define _MY_SD_H_

#include <Arduino.h>
// #include <SD.h>
#include "driver/sdspi_host.h"
#include "driver/spi_common.h"
#include "sdmmc_cmd.h"
#include "esp_vfs_fat.h"
#include "esp_log.h"

esp_err_t my_sd_init();
void write_file();
void read_file();
void check_dir();

#endif
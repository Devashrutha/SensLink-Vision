#ifndef __BMP280__
#define __BMP280__

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BMP280_I2C_ADDRESS     0X77
#define BMP280_DEVICE_ID       0X58

#define BMP280_REG_TEMP_XLSB   0xFC 
#define BMP280_REG_TEMP_LSB    0xFB
#define BMP280_REG_TEMP_MSB    0xFA
#define BMP280_REG_TEMP        0xFA
#define BMP280_REG_PRESS_XLSB  0xF9
#define BMP280_REG_PRESS_LSB   0xF8
#define BMP280_REG_PRESS_MSB   0xF7
#define BMP280_REG_PRESSURE    0xF7
#define BMP280_REG_CONFIG      0xF5 
#define BMP280_REG_CTRL        0xF4 
#define BMP280_REG_STATUS      0xF3 
#define BMP280_REG_CTRL_HUM    0xF2
#define BMP280_REG_RESET       0xE0
#define BMP280_REG_ID          0xD0
#define BMP280_REG_CALIB       0x88
#define BMP280_REG_HUM_CAL     0x88
#define BMP280_RESET_VALUE     0xB6

typedef enum{
	BMP280_SLEEP=0,
    BMP280_FORCED=1,
	BMP280_NORMAL=3
} BMP280_Modes;

typedef enum{
	BMP280_SKIP=0,
    BMP280_ULTRA_LOW_POWER,
    BMP280_LOW_POWER,
    BMP280_STANDARD_RES,
    BMP280_HIGH_RES,
    BMP280_ULTRA_HIGH_RES
} BMP280_Upsampling;

typedef enum{
    BMP280_IIR_OFF=0,
    BMP280_IIR_2,
    BMP280_IIR_4,
    BMP280_IIR_8,
    BMP280_IIR_16
} BMP280_IIR_Filter;

typedef enum{
    BMP280_0_5ms = 0,
    BMP280_62_5ms,
    BMP280_125ms,
    BMP280_250ms,
    BMP280_500ms,
    BMP280_1000ms,
    BMP280_2000ms,
    BMP280_4000ms
} BMP280_Standby_ms;

typedef struct{
    BMP280_Modes mode;
    BMP280_Upsampling ups_pressure;
    BMP280_Upsampling ups_temperature;
    BMP280_Upsampling ups_humidity;
    BMP280_IIR_Filter filter;
    BMP280_Standby_ms standby;
} BMP280_Params;

typedef struct {
    uint16_t dig_T1;
    int16_t  dig_T2;
    int16_t  dig_T3;
    uint16_t dig_P1;
    int16_t  dig_P2;
    int16_t  dig_P3;
    int16_t  dig_P4;
    int16_t  dig_P5;
    int16_t  dig_P6;
    int16_t  dig_P7;
    int16_t  dig_P8;
    int16_t  dig_P9;
    uint8_t  id;
    uint16_t address;
    I2C_HandleTypeDef* i2c;
    BMP280_Params parameters;

} BMP280_HandleTypedef;

void bmp280_default_init(BMP280_Params *parameters);
void bmp280_uhr_all_init(BMP280_Params *parameters);
void bmp280_uhr_press_init(BMP280_Params *parameters);
void bmp280_uhr_temp_init(BMP280_Params *parameters);
void bmp280_sleep_init(BMP280_Params *parameters);
bool bmp280_init(BMP280_HandleTypedef *dev, BMP280_Params *parameters);
bool bmp280_busy(BMP280_HandleTypedef *dev);
bool bmp280_read(BMP280_HandleTypedef *dev, float *temperature, float *pressure);

#endif


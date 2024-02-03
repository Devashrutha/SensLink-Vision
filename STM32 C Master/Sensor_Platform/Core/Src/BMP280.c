#include "BMP280.h"

void bmp280_default_init(BMP280_Params *parameters) {
	parameters->mode = BMP280_NORMAL;
	parameters->ups_pressure = BMP280_STANDARD_RES;
	parameters->ups_temperature = BMP280_STANDARD_RES;
	parameters->filter = BMP280_IIR_4;
	parameters->standby = BMP280_250ms;
}

void bmp280_uhr_all_init(BMP280_Params *parameters) {
	parameters->mode = BMP280_NORMAL;
	parameters->ups_pressure = BMP280_ULTRA_HIGH_RES;
	parameters->ups_temperature = BMP280_ULTRA_HIGH_RES;
	parameters->filter = BMP280_IIR_4;
	parameters->standby = BMP280_250ms;
}

void bmp280_uhr_press_init(BMP280_Params *parameters) {
	parameters->mode = BMP280_NORMAL;
	parameters->ups_pressure = BMP280_ULTRA_HIGH_RES;
	parameters->ups_temperature = BMP280_STANDARD_RES;
	parameters->filter = BMP280_IIR_16;
	parameters->standby = BMP280_250ms;
}

void bmp280_uhr_temp_init(BMP280_Params *parameters) {
	parameters->mode = BMP280_NORMAL;
	parameters->ups_pressure = BMP280_STANDARD_RES;
	parameters->ups_temperature = BMP280_ULTRA_HIGH_RES;
	parameters->filter = BMP280_IIR_OFF;
	parameters->standby = BMP280_250ms;
}

void bmp280_sleep_init(BMP280_Params *parameters) {
	parameters->mode = BMP280_SLEEP;
	parameters->ups_pressure = BMP280_SKIP;
	parameters->ups_temperature = BMP280_SKIP;
	parameters->filter = BMP280_IIR_OFF;
	parameters->standby = BMP280_250ms;
}

static bool read_reg16(BMP280_HandleTypedef *dev, uint8_t address, uint16_t *value) {
	uint16_t tx_buff;
	uint8_t rx_buff[2];
	tx_buff = (dev->address << 1);

	if (HAL_I2C_Mem_Read(dev->i2c, tx_buff, address, 1, rx_buff, 2, 5000)
			== HAL_OK) {
		*value = (uint16_t) ((rx_buff[1] << 8) | rx_buff[0]);
		return true;
	} else
		return false;

}

static inline int read_data(BMP280_HandleTypedef *dev, uint8_t address, uint8_t *value,
		uint8_t len) {
	uint16_t tx_buff;
	tx_buff = (dev->address << 1);
	if (HAL_I2C_Mem_Read(dev->i2c, tx_buff, address, 1, value, len, 5000) == HAL_OK)
		return 0;
	else
		return 1;

}

static int write_reg8(BMP280_HandleTypedef *dev, uint8_t address, uint8_t value) {
	uint16_t tx_buff;

	tx_buff = (dev->address << 1);

	if (HAL_I2C_Mem_Write(dev->i2c, tx_buff, address, 1, &value, 1, 10000) == HAL_OK)
		return false;
	else
		return true;
}

static bool read_calibration_data(BMP280_HandleTypedef *dev) {

	if (read_reg16(dev, 0x88, &dev->dig_T1)
			&& read_reg16(dev, 0x8a, (uint16_t *) &dev->dig_T2)
			&& read_reg16(dev, 0x8c, (uint16_t *) &dev->dig_T3)
			&& read_reg16(dev, 0x8e, &dev->dig_P1)
			&& read_reg16(dev, 0x90, (uint16_t *) &dev->dig_P2)
			&& read_reg16(dev, 0x92, (uint16_t *) &dev->dig_P3)
			&& read_reg16(dev, 0x94, (uint16_t *) &dev->dig_P4)
			&& read_reg16(dev, 0x96, (uint16_t *) &dev->dig_P5)
			&& read_reg16(dev, 0x98, (uint16_t *) &dev->dig_P6)
			&& read_reg16(dev, 0x9a, (uint16_t *) &dev->dig_P7)
			&& read_reg16(dev, 0x9c, (uint16_t *) &dev->dig_P8)
			&& read_reg16(dev, 0x9e,
					(uint16_t *) &dev->dig_P9)) {

		return true;
	}

	return false;
}





bool bmp280_init(BMP280_HandleTypedef *dev, BMP280_Params *parameters) {

	if (dev->address != BMP280_I2C_ADDRESS) {

		return false;
	}

	if (read_data(dev, BMP280_REG_ID, &dev->id, 1)) {
		return false;
	}

	if (dev->id != BMP280_DEVICE_ID) {

		return false;
	}


	if (write_reg8(dev, BMP280_REG_RESET, BMP280_RESET_VALUE)) {
		return false;
	}

	// Wait until finished copying over the NVP data.
	while (1) {
		uint8_t status;
		if (!read_data(dev, BMP280_REG_STATUS, &status, 1)
				&& (status & 1) == 0)
			break;
	}

	if (!read_calibration_data(dev)) {
		return false;
	}



	uint8_t config = (parameters->standby << 5) | (parameters->filter << 2);
	if (write_reg8(dev, BMP280_REG_CONFIG, config)) {
		return false;
	}

	uint8_t ctrl = (parameters->ups_temperature << 5)
			| (parameters->ups_pressure << 2) | (parameters->mode);


	if (write_reg8(dev, BMP280_REG_CTRL, ctrl)) {
		return false;
	}

	return true;
}

bool bmp280_busy(BMP280_HandleTypedef *dev) {
	uint8_t status;
	if (read_data(dev, BMP280_REG_STATUS, &status, 1))
		return false;
	if (status & (1 << 3)) {
		return true;
	}
	return false;
}

static inline int32_t compensate_temperature(BMP280_HandleTypedef *dev, int32_t adc_temp,
		int32_t *fine_temp) {
	int32_t var1, var2;

	var1 = ((((adc_temp >> 3) - ((int32_t) dev->dig_T1 << 1)))
			* (int32_t) dev->dig_T2) >> 11;
	var2 = (((((adc_temp >> 4) - (int32_t) dev->dig_T1)
			* ((adc_temp >> 4) - (int32_t) dev->dig_T1)) >> 12)
			* (int32_t) dev->dig_T3) >> 14;

	*fine_temp = var1 + var2;
	return (*fine_temp * 5 + 128) >> 8;
}


static inline uint32_t compensate_pressure(BMP280_HandleTypedef *dev, int32_t adc_press,
		int32_t fine_temp) {
	int64_t var1, var2, p;

	var1 = (int64_t) fine_temp - 128000;
	var2 = var1 * var1 * (int64_t) dev->dig_P6;
	var2 = var2 + ((var1 * (int64_t) dev->dig_P5) << 17);
	var2 = var2 + (((int64_t) dev->dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t) dev->dig_P3) >> 8)
			+ ((var1 * (int64_t) dev->dig_P2) << 12);
	var1 = (((int64_t) 1 << 47) + var1) * ((int64_t) dev->dig_P1) >> 33;

	if (var1 == 0) {
		return 0; 
	}

	p = 1048576 - adc_press;
	p = (((p << 31) - var2) * 3125) / var1;
	var1 = ((int64_t) dev->dig_P9 * (p >> 13) * (p >> 13)) >> 25;
	var2 = ((int64_t) dev->dig_P8 * p) >> 19;

	p = ((p + var1 + var2) >> 8) + ((int64_t) dev->dig_P7 << 4);
	return p;
}


bool bmp280_read_fixed(BMP280_HandleTypedef *dev, int32_t *temperature, uint32_t *pressure) {
	int32_t adc_pressure;
	int32_t adc_temp;
	uint8_t data[8];

	if (read_data(dev, 0xf7, data, 8)) {
		return false;
	}

	adc_pressure = data[0] << 12 | data[1] << 4 | data[2] >> 4;
	adc_temp = data[3] << 12 | data[4] << 4 | data[5] >> 4;

	int32_t fine_temp;
	*temperature = compensate_temperature(dev, adc_temp, &fine_temp);
	*pressure = compensate_pressure(dev, adc_pressure, fine_temp);


	return true;
}


bool bmp280_read(BMP280_HandleTypedef *dev, float *temperature, float *pressure) {
	int32_t fixed_temperature;
	uint32_t fixed_pressure;
	if (bmp280_read_fixed(dev, &fixed_temperature, &fixed_pressure)) {
		*temperature = (float) fixed_temperature / 100;
		*pressure = (float) fixed_pressure / 256;
		return true;
	}

	return false;
}

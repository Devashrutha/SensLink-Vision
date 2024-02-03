/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usb_device.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

#include "BMP280.h"
#include "MPU6050.h"
#include "LoRa.h"


/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DENSITY_AIR_KGPM3      1.293f
#define G_MPS2                 9.807f
#define MOLAR_MASS_AIR_KG_MOL  0.029
#define UNI_GAS_CONST_NMP_MOLK 8.314
#define PRESSURE_SEA_PA        101325.0f
#define SAMP_TIM_ACC_MS        10
#define SAMP_TIM_GYRO_MS       100
#define SAMP_TIM_COM_MS        250

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;
I2C_HandleTypeDef hi2c2;

SPI_HandleTypeDef hspi1;

TIM_HandleTypeDef htim11;

UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;

/* USER CODE BEGIN PV */
LoRa Ra02;
uint16_t LoRa_status = 0;
uint8_t send_data[] = "Hello";
uint16_t status = 0;

BMP280_HandleTypedef bmp280;
float pressure, temperature, altitude;

uint8_t Baro_Data[64];
uint8_t Baro_STR_Size;
uint8_t BARO_ERROR_LED;

char UART_Data[64];
uint8_t UART_STR_Size;

char COM_Port_Data[64];
uint8_t COM_STR_Size;

//FATFS myFATFS;
//FIL myfile;
//UINT sd_error;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_I2C1_Init(void);
static void MX_I2C2_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
static void MX_TIM11_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {

}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_I2C2_Init();
  MX_USART2_UART_Init();
  MX_USB_DEVICE_Init();
  MX_SPI1_Init();
  MX_TIM11_Init();
  /* USER CODE BEGIN 2 */

	Ra02 = newLoRa();
	Ra02.CS_port = LORA_NSS_GPIO_Port;
	Ra02.CS_pin = LORA_NSS_Pin;
	Ra02.DIO0_port = LORA_DIO0_GPIO_Port;
	Ra02.DIO0_pin = LORA_DIO0_Pin;
	Ra02.hSPIx = &hspi1;
	Ra02.bandWidth = BW_500KHz;
	Ra02.overCurrentProtection = 130;
	status = LoRa_init(&Ra02);
	if (status == LORA_OK) {
		LoRa_status = 1;

	}

	bmp280_uhr_all_init(&bmp280.parameters);
	bmp280.address = BMP280_I2C_ADDRESS;
	bmp280.i2c = &hi2c2;

	while (!bmp280_init(&bmp280, &bmp280.parameters)) {
		Baro_STR_Size = sprintf((char*) Baro_Data,
				"BMP280 initialization failed\n");
		CDC_Transmit_FS((uint8_t*) Baro_Data, Baro_STR_Size);
		for (BARO_ERROR_LED = 0; BARO_ERROR_LED <= 3; BARO_ERROR_LED++) {
			HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin, GPIO_PIN_SET);
			HAL_Delay(500);
		}
		HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(2000);
	}

	DWT->CYCCNT = 0;
	MPU6050_t MPU6050;
	MPU6050_peripheral_config();
	uint8_t check = MPU6050_Init(MPU6050_Accelerometer_2G,
			MPU6050_Gyroscope_250_deg, MPU6050_DataRate_4KHz);
	if (check == MPU6050_SUCCESS) {
		printf("MPU6050 Initilalization Success\n");
	}
	MPU6050_set_power_mode(MPU6050_POWER_ON, MPU6050_rate_dont_care);
	MPU6050_enable_irq(LATCH_IRQ_EN | IRQ_RD_CLEAR);

	uint32_t timerACC = 0;
	uint32_t timerGYR = 0;
	uint32_t timerCOM = 0;

//SD CARD
//	if(f_mount(&myFATFS,SDPath,1) == FR_OK){
//		HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin, GPIO_PIN_SET);
//		HAL_Delay(500);
//		char myfilename[]="data2.txt";
//		if(f_open(&myfile,myfilename, FA_WRITE | FA_CREATE_ALWAYS) == FR_OK){
//			char myData[]="WoW_DMA";
//			if(f_write(&myfile, myData,sizeof(myData), &sd_error)==FR_OK){
//				HAL_GPIO_WritePin(MCU_LED_GPIO_Port,MCU_LED_Pin, GPIO_PIN_RESET);
//			}
//			f_close(&myfile);
//		}
//	}
//	else{
//		HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin, GPIO_PIN_SET);
//	}

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

	while (1) {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		MPU6050_Read_All(&MPU6050);
		while (!bmp280_read(&bmp280, &temperature, &pressure)) {
			Baro_STR_Size = sprintf((char*) Baro_Data,
					"Temperature/pressure reading failed\n");
			CDC_Transmit_FS((uint8_t*) Baro_Data, Baro_STR_Size);
			HAL_Delay(2000);
		}
		altitude = -log(pressure / PRESSURE_SEA_PA)
				* (((UNI_GAS_CONST_NMP_MOLK * (273.15 + temperature))
						/ (G_MPS2 * MOLAR_MASS_AIR_KG_MOL)));

		UART_STR_Size = sprintf(UART_Data,
				"ALT(m):%d,TMP(C):%d,PTH:%.2f,ROL:%.2f\r\n",
				(int) altitude, (int) temperature, MPU6050.KalmanAngleY,
				MPU6050.KalmanAngleX);
		HAL_UART_Transmit_DMA(&huart2, (uint8_t*) UART_Data, UART_STR_Size);

		LoRa_transmit(&Ra02, (uint8_t*) UART_Data, sizeof(UART_Data),0);


	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 96;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief I2C2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C2_Init(void)
{

  /* USER CODE BEGIN I2C2_Init 0 */

  /* USER CODE END I2C2_Init 0 */

  /* USER CODE BEGIN I2C2_Init 1 */

  /* USER CODE END I2C2_Init 1 */
  hi2c2.Instance = I2C2;
  hi2c2.Init.ClockSpeed = 100000;
  hi2c2.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c2.Init.OwnAddress1 = 0;
  hi2c2.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c2.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c2.Init.OwnAddress2 = 0;
  hi2c2.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c2.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C2_Init 2 */

  /* USER CODE END I2C2_Init 2 */

}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_16;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief TIM11 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM11_Init(void)
{

  /* USER CODE BEGIN TIM11_Init 0 */

  /* USER CODE END TIM11_Init 0 */

  /* USER CODE BEGIN TIM11_Init 1 */

  /* USER CODE END TIM11_Init 1 */
  htim11.Instance = TIM11;
  htim11.Init.Prescaler = 95;
  htim11.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim11.Init.Period = 65535;
  htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim11) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM11_Init 2 */

  /* USER CODE END TIM11_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_HalfDuplex_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Stream6_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LORA_NSS_GPIO_Port, LORA_NSS_Pin, GPIO_PIN_SET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(MCU_LED_GPIO_Port, MCU_LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : LORA_NSS_Pin */
  GPIO_InitStruct.Pin = LORA_NSS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LORA_NSS_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CARD_BUTTON_Pin */
  GPIO_InitStruct.Pin = SD_CARD_BUTTON_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(SD_CARD_BUTTON_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LORA_DIO0_Pin */
  GPIO_InitStruct.Pin = LORA_DIO0_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LORA_DIO0_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : BARO_INT_Pin IMU_INT_Pin */
  GPIO_InitStruct.Pin = BARO_INT_Pin|IMU_INT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : MCU_LED_Pin */
  GPIO_InitStruct.Pin = MCU_LED_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(MCU_LED_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : SD_CARD_DETECT_Pin */
  GPIO_InitStruct.Pin = SD_CARD_DETECT_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(SD_CARD_DETECT_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI1_IRQn);

  HAL_NVIC_SetPriority(EXTI3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI3_IRQn);

  HAL_NVIC_SetPriority(EXTI4_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_IRQn);

  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

}

/* USER CODE BEGIN 4 */



/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

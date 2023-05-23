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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi3;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

uint8_t SPIRx[10];
uint8_t SPITx[10];

uint8_t switch_read;
uint8_t check = 0;

uint8_t cmd = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI3_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_USART2_UART_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */

  SPITxRx_Setup();
  setOutputGPIOB();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  static uint32_t timestamp = 0;
	  if(HAL_GetTick() > timestamp)
	  {
		  timestamp = HAL_GetTick() + 10;
		  cmd++;
		  cmd = cmd % 2;
		  switch (cmd)
		  {
		  case 0:
			  SPITxRx_readIO();
			  break;
		  case 1:
			  SPITxRx_writeIO();
			  break;
//		  case 2:
//			  setOutputGPIOB();
//			  break;
		  }
	  }
//	  SPITxRx_writeIO();

//	  if(check == 0)
//	  {
//		  check == 1;
//		  SPITxRx_readIO();
//	  }
//	  else if(check == 0)
//	  {
//		  check == 0;
//		  SPITxRx_writeIO();
//	  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
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

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI3_Init(void)
{

  /* USER CODE BEGIN SPI3_Init 0 */

  /* USER CODE END SPI3_Init 0 */

  /* USER CODE BEGIN SPI3_Init 1 */

  /* USER CODE END SPI3_Init 1 */
  /* SPI3 parameter configuration*/
  hspi3.Instance = SPI3;
  hspi3.Init.Mode = SPI_MODE_MASTER;
  hspi3.Init.Direction = SPI_DIRECTION_2LINES;
  hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi3.Init.CLKPolarity = SPI_POLARITY_HIGH;
  hspi3.Init.CLKPhase = SPI_PHASE_2EDGE;
  hspi3.Init.NSS = SPI_NSS_SOFT;
  hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi3.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI3_Init 2 */

  /* USER CODE END SPI3_Init 2 */

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
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void SPITxRx_Setup()
{
	//CS pulse
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0); // CS Select
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 1); // CS deSelect
	HAL_Delay(1);
}

void SPITxRx_readIO()
{
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000001;
		SPITx[1] = 0x12;
		SPITx[2] = 0;
		SPITx[3] = 0;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 4);
		switch_read = SPIRx[2];
	}
}


void setOutputGPIOB()
{
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2))
	{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x01;
		SPITx[2] = 0b00000000;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
	}
}

void SPITxRx_writeIO()
{
	if (HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_2))
	{
		if(SPIRx[2] == 0b00001110)
		{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b10101010;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(500);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b01010101;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(500);
		}
		else if(SPIRx[2] == 0b00001111)
		{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11111111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		}
		else if(SPIRx[2] == 0b00001101)
		{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b00111111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11001111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11110011;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11111100;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);
		}
		else if(SPIRx[2] == 0b00001011)
		{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11111110;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b01111111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11111101;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b10111111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11111011;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11011111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11110111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11101111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);
		}
		else if(SPIRx[2] == 0b00000111)
		{
		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b00001111;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);

		HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 0);
		SPITx[0] = 0b01000000;
		SPITx[1] = 0x13;
		SPITx[2] = 0b11110000;
		HAL_SPI_TransmitReceive_IT(&hspi3, SPITx, SPIRx, 3);
		HAL_Delay(100);
		}
	}
}


void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 1); //CS dnSelect
}

//void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
//{
//	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, 1); //CS dnSelect
//}

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
  while (1)
  {
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

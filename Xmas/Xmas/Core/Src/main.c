/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim3;
DMA_HandleTypeDef hdma_tim3_ch1;

/* USER CODE BEGIN PV */
uint16_t TC_event = 0;
uint16_t HC_event = 0;

uint32_t *ledBuffer = NULL;

uint32_t *ledbuffer = NULL;

uint8_t dmaTimerTransfetCompleteFlag = 0;
uint32_t databuffer;
uint32_t color;
uint32_t grb[24];
uint8_t buffer[24];




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
/* USER CODE BEGIN PFP */
//void begin(TIM_HandleTypeDef *_htim, DMA_HandleTypeDef *_hdmaPtr, uint32_t channel, uint32_t num_of_leds, uint32_t pause_Pulse, uint32_t work_Pulse, uint32_t prescaler);
void led(uint8_t r, uint8_t g, uint8_t b);
void led_PWM();
void led_show();
void timerDmaTransferComplete();
void begin(TIM_HandleTypeDef *_htim,DMA_HandleTypeDef *_hdmaPtr, uint32_t channel, uint32_t *num_of_leds, uint32_t pause_Pulse, uint32_t work_Pulse, uint32_t prescaler);
void setLed();

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
 // uint32_t melody_tone[] = {800, 956, 758};
 // uint32_t melody_dur[] = {1000, 1300, 1600};
  HAL_TIM_PWM_DeInit(&htim1);
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */

  //melody1 is notes of jingle_bells melody  {E4, E4, E4, E4, E4, E4, E4, G4, C4 , D4 , E4, F4, F4, F4, F4, F4, E4, E4, E4, D4, D4, E4, D4, G4}
  uint16_t melody1[] = {329, 329, 329, 329, 329, 329, 329, 392, 261, 293, 329, 349, 349, 349, 349, 349, 329, 329, 329, 293, 293, 329, 293, 392};

  //duration of melodies
  uint16_t duration_melody[] = {250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250, 250};

  uint16_t brmelody = sizeof(melody1)/sizeof(uint16_t);




/*
  __HAL_TIM_SET_PRESCALER(&htim3, 12);
  __HAL_TIM_SET_AUTORELOAD(&htim3, 50);

  HAL_DMA_RegisterCallback(&hdma_tim3_ch1, HAL_DMA_XFER_CPLT_CB_ID,timerDmaTransferComplete);
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
  __HAL_TIM_ENABLE_DMA(&htim3, TIM_CHANNEL_1);

	__HAL_TIM_SET_COUNTER(&htim3, 0);
	__HAL_TIM_ENABLE_DMA(&htim3, TIM_CHANNEL_1);
	HAL_DMA_Start_IT(&hdma_tim3_ch1, 28, TIM_CHANNEL_1, sizeof(28) / sizeof(uint16_t));
	while (dmaTimerTransfetCompleteFlag == 0);
	dmaTimerTransfetCompleteFlag = 0;

	  resetLEDS(leds, 1);

	  HAL_TIM_PWM_Start_DMA(&htim3,TIM_CHANNEL_1 , (uint32_t*)leds, );
	  setLEDS(leds, 1);
	  */



  begin(&htim3, &hdma_tim3_ch1, TIM_CHANNEL_1, 1, 1, 1, 5);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {



    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 479;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 50;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterOutputTrigger2 = TIM_TRGO2_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.BreakFilter = 0;
  sBreakDeadTimeConfig.BreakAFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.Break2State = TIM_BREAK2_DISABLE;
  sBreakDeadTimeConfig.Break2Polarity = TIM_BREAK2POLARITY_HIGH;
  sBreakDeadTimeConfig.Break2Filter = 0;
  sBreakDeadTimeConfig.Break2AFMode = TIM_BREAK_AFMODE_INPUT;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 12;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 49;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(PERIPH_SUPLLY_GPIO_Port, PERIPH_SUPLLY_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PERIPH_SUPLLY_Pin */
  GPIO_InitStruct.Pin = PERIPH_SUPLLY_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(PERIPH_SUPLLY_GPIO_Port, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */





void begin(TIM_HandleTypeDef *_htim, DMA_HandleTypeDef *_hdmaPtr,  uint32_t channel, uint32_t *num_of_leds, uint32_t pause_Pulse, uint32_t work_Pulse, uint32_t prescaler)
{


	uint32_t buffer[25];
	__HAL_TIM_SET_PRESCALER(_htim, 5);
	__HAL_TIM_SET_AUTORELOAD(_htim, 9);
	//__HAL_TIM_ENABLE_DMA(_htim, _hdmaPtr);
	__HAL_TIM_ENABLE_DMA(_htim, channel);

	for(int i = 0; i < 25 ; i++)
	{

	        buffer[i] = 6;
	}



	//HAL_TIM_PWM_Start_DMA(_htim, channel, buffer, 25);
	HAL_DMA_Start(_hdmaPtr, channel, (uint32_t)buffer, 25);
	HAL_Delay(100);
	HAL_DMA_PollForTransfer(_hdmaPtr, HAL_DMA_XFER_CPLT_CB_ID , 100);





	/*

	if (colorRGB == red)
			{
		HAL_TIM_PWM_Start(_htim, channel);
		for(int i = 0; i < 24; i++)
		{
			if(i > 0 && i < 8) buffer[i] = 6;
			if(i > 8 && i < 24) buffer[i] = 6;
			buffer[25] = 0;

			_htim->Instance->CCR1 = buffer[i];
		}

			}



	if(colorRGB == green)
	{
		//color==red;



		HAL_TIM_PWM_Start(_htim, channel);

		for(int i = 0; i < 24; i++)
		{
			if(i > 0 && i < 16) buffer[i] = 6;
			if(i > 16 && i < 24) buffer[i] = 3;

			_htim->Instance->CCR1 = buffer[i];
		}

	}


	HAL_TIM_PWM_Stop_IT(_htim, channel);

	*/

	///prvo moras osigurat memoriju odnosno zauzet dio memorije za ledice tj buffer
	//ledBuffer = (uint32_t*)malloc(num_of_leds * sizeof(uint32_t));
	//u datasheetu pise da je memorija na pocetku konfigurirana sa svim 0 za reset
	//memset((uint32_t*)ledBuffer, 0, sizeof(uint32_t) * num_of_leds);

	//inicializirat timer
//	__HAL_TIM_SET_PRESCALER(_htim, 5);
	//_HAL_TIM_SET_AUTORELOAD(_htim, 9);

	//inicijalizacija za DMA
//	HAL_DMA_RegisterCallback(&hdma_tim3_ch1, HAL_DMA_XFER_CPLT_CB_ID, 1);

	//_htim->Instance->CCR1 = 3;
	//for(int j = 0 ; j < 12; j++)
	//{
	//HAL_TIM_PWM_Start(_htim, channel);
	//for(int i = 0 ; i < 25; i++)
	//{
		//_htim->Instance->CCR1 = buffer[i];
		//while(__HAL_TIM_GET_COUNTER(_htim) < 6);
	//}

	//HAL_TIM_PWM_Stop(_htim, channel);

	//}


//	__HAL_TIM_ENABLE_DMA(_htim, channel);

}
void setLed()
{



}














/*void melody(TIM_HandleTypeDef *_htim, uint32_t freq, uint32_t duration_melody)
{
	uint32_t prescaler = ((HAL_RCC_GetSysClockFreq()/ (50*freq)) - 1);

	uint32_t period = ((HAL_RCC_GetSysClockFreq() / prescaler/freq)-1);

	uint32_t duty = period/2;

	__HAL_TIM_SET_PRESCALER(_htim, prescaler);

	__HAL_TIM_SET_AUTORELOAD(_htim, period);

	_htim->Instance->CCR1 = duty;

	//HAL_TIM_PWM_Start(_htim, TIM_CHANNEL_1);

	HAL_Delay(duration_melody);

	//HAL_TIM_PWM_Stop(_htim, TIM_CHANNEL_1);
}
*/
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

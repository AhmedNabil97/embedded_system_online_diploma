/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_it.h"


# define CAN_BTR1		(*(volatile unsigned int *)(CAN1 + 0x1C))

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
CAN_HandleTypeDef hcan;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_CAN_Init(void);

#define   mask_Reg		(*(volatile unsigned int *)(CAN1 + 0x244))

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */


void CAN_TX(uint32_t ID , uint8_t DLC , uint8_t * Pay_Load)
{

	// get no. of Free Tx Mail box
	uint8_t no_of_free_TX_mail_box = HAL_CAN_GetTxMailboxesFreeLevel(& hcan);
	uint32_t pTxMailbox ;
	CAN_TxHeaderTypeDef pHeader;
	pHeader.DLC = DLC;
	pHeader.IDE = CAN_ID_STD ;
	pHeader.RTR = CAN_RTR_DATA ;
	pHeader.StdId = ID;

	if(no_of_free_TX_mail_box)
	{

		// request transmit of a new msg
		if(HAL_CAN_AddTxMessage(&hcan, &pHeader, Pay_Load, &pTxMailbox) != HAL_OK )
		{
			Error_Handler();
		}

		// wait until TX mail box is transmitted

		while ( HAL_CAN_IsTxMessagePending(&hcan, pTxMailbox) );
	}



}

void CAN_RX_FILTER(uint16_t STD_FILTER_ID,uint16_t STD_FILTER_MASK){
	/* Configure the reception filters using the following configuration
       (++) HAL_CAN_ConfigFilter()*/

	CAN_FilterTypeDef sFilterConfig;
	sFilterConfig.FilterActivation=CAN_FILTER_ENABLE;
	sFilterConfig.FilterBank=0;
	sFilterConfig.FilterFIFOAssignment=CAN_FILTER_FIFO0;
	sFilterConfig.FilterIdHigh=  STD_FILTER_ID << 5;
	sFilterConfig.FilterIdLow=0x0000;
	sFilterConfig.FilterMaskIdHigh= STD_FILTER_MASK << 5;
	sFilterConfig.FilterMaskIdLow=0x0000;
	sFilterConfig.FilterMode= CAN_FILTERMODE_IDMASK ;
	sFilterConfig.FilterScale=CAN_FILTERSCALE_32BIT;


	if(HAL_CAN_ConfigFilter(&hcan, &sFilterConfig) != HAL_OK){
		Error_Handler();
	}
}



void CAN_RX(uint16_t * ID , uint8_t * DLC , unsigned char * rx_data_Payload)
{


	/*  (++) Monitor reception of message using HAL_CAN_GetRxFifoFillLevel()
         until at least one message is received.
    (++) Then get the message using HAL_CAN_GetRxMessage().
	 */


	CAN_RxHeaderTypeDef pHeader;

	// this funtion return number of msgs available in the sepecified FIFO

	// wait until receiving a msg
	while (HAL_CAN_GetRxFifoFillLevel(&hcan, CAN_FILTER_FIFO0) == 0 );

	if ( HAL_CAN_GetRxMessage(&hcan, CAN_FILTER_FIFO0, &pHeader, rx_data_Payload) != HAL_OK )
	{
		Error_Handler();
	}

	*ID = pHeader.StdId;
	*DLC = pHeader.DLC;

}






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
	MX_CAN_Init();
	CAN_RX_FILTER(0x3FF, 0x7FF);
	if( HAL_CAN_Start(& hcan) != HAL_OK )
	{
		Error_Handler();
	}

	/* USER CODE BEGIN 2 */

	volatile uint8_t Frame_no = 0 ;
	volatile static unsigned char RX_Data[16];
	volatile uint16_t RX_ID;
	volatile uint8_t RX_DLC;
	volatile uint8_t Tx_Pay_load[8] = {'C','A','N',' ','N','O',':',};
	volatile uint16_t Tx_ID = 0x3FF;

	/* USER CODE END 2 */

	/* Infinite loop */
	/* USER CODE BEGIN WHILE */
	int k = 0;
	while (1)
	{
		/* USER CODE END WHILE */
		Tx_Pay_load[7] = Frame_no ++ ;
		CAN_TX(Tx_ID, 8, Tx_Pay_load);              //wait until TX is done
		CAN_RX(&RX_ID, &RX_DLC, RX_Data);          //wait until RX is done
		k++;
		if(k == 3)
		{
			Tx_ID = 0x1FF;
		}
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
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief CAN Initialization Function
 * @param None
 * @retval None
 */
static void MX_CAN_Init(void)
{

	/* USER CODE BEGIN CAN_Init 0 */

	/* USER CODE END CAN_Init 0 */

	/* USER CODE BEGIN CAN_Init 1 */

	/* USER CODE END CAN_Init 1 */
	hcan.Instance = (uint32_t*)CAN1;
	hcan.Init.Prescaler = 1;
	hcan.Init.Mode = CAN_MODE_LOOPBACK;
	hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
	hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
	hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
	hcan.Init.TimeTriggeredMode = DISABLE;
	hcan.Init.AutoBusOff = DISABLE;
	hcan.Init.AutoWakeUp = DISABLE;
	hcan.Init.AutoRetransmission = ENABLE;
	hcan.Init.ReceiveFifoLocked = DISABLE;
	hcan.Init.TransmitFifoPriority = DISABLE;
	if (HAL_CAN_Init(&hcan) != HAL_OK)
	{
		Error_Handler();
	}
	/* USER CODE BEGIN CAN_Init 2 */

	/* USER CODE END CAN_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void)
{

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOA_CLK_ENABLE();

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
	/* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

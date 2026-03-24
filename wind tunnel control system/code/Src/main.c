/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"
#include "oled.h"
#include "spi.h"
#include "key.h"
#include "delay.h"
#include "vl53l0x_api.h"
#include "filter.h"
#include "ST_I2C.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

__IO uint32_t oled_setpoint = 0;
__IO uint32_t key_setpoint = 0;
__IO uint32_t key_push_setpoint = 0;
uint8_t oled_string[20]= {0};
uint8_t key_change_long_short = 0;
uint8_t temp = 0;
uint8_t key_v, key_u, key_d , key_o;
uint8_t state = 1;

uint16_t set_distance = 400;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void OLED_PROC(void);
void KEY_PROC(void);
void LAST_JUDGE_PROC(void);
/* USER CODE BEGIN PFP */
//extern void VL53L0X_Init(void);
//extern uint16_t VL53L0X_GetValue(void);
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
	delay_init(72);
  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();
	OLED_Init();
	OLED_Clear();
	
	
	VL53L0X_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

		OLED_PROC();
		KEY_PROC();
		LAST_JUDGE_PROC();
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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

/* USER CODE BEGIN 4 */
void OLED_PROC(void)
{

	 if((uwTick - oled_setpoint) <20) return;
		oled_setpoint = uwTick;
	
//		sprintf((unsigned char*)oled_string , " %d  " ,++temp);
//		OLED_ShowString(0,6, oled_string);
//		sprintf((unsigned char*)oled_string , "%d " ,(int)key_scan());
//		OLED_ShowString(0,6, oled_string);
		
		sprintf((unsigned char*)oled_string , "%d%d%d%d " ,key_v,key_d,key_u,key_o);
		OLED_ShowString(35,0, oled_string);
	
//		//origin
//		sprintf((unsigned char*)oled_string , "origin:%d  " ,(VL53L0X_GetValue()));
//		OLED_ShowString(16,2, oled_string);
//	
//		//filtering
//	  sprintf((unsigned char*)oled_string , "filter_a:%d  " ,smooth(VL53L0X_GetValue()));
//		OLED_ShowString(16,4, oled_string);

		//filtering
		sprintf((unsigned char*)oled_string , "filter_m:%d  " ,median(VL53L0X_GetValue()));
		OLED_ShowString(16,6, oled_string);
		
		sprintf((unsigned char*)oled_string , "state:%d  " ,state);
		OLED_ShowString(35,2, oled_string);
		sprintf((unsigned char*)oled_string , "dis:%d  " ,set_distance);
		OLED_ShowString(35,4, oled_string);
    OLED_ShowString(0,0, (unsigned char *)"TEST");



//		OLED_Clear();
	  if(temp>=100) temp = 0;




}
void KEY_PROC(void)
{
	 if((uwTick - key_setpoint) <50) return;
		key_setpoint = uwTick;
//  
	  key_v = key_scan();
		key_d = key_v & ( key_o ^ key_v);
		key_u = ~key_v & ( key_o ^ key_v);
		key_o = key_v ;

	
	 if(key_d) key_push_setpoint = uwTick;
	
	 if(key_d == 1)
	{
		 state++;
		 if(state >= 5) state = 1;

	 }
	 
	 if(state == 2)
	{
			 if(key_d == 2)
				 set_distance+=10;
			 if(key_d == 3)
				 set_distance-=10; 
			 
			 
			 if((key_o==2) && (key_change_long_short==1))
			 {
				 set_distance +=10;
			 if(key_u == 2) key_change_long_short = 0;
				 
				}
			 
				if((key_o==3) && (key_change_long_short==1))
			 {
				 set_distance -=10;
			 if(key_u == 3) key_change_long_short = 0;
				 
				}
			 
				
			 if(set_distance<=200) set_distance = 200;
			 if(set_distance>=400) set_distance = 400;
	 
	}
	
	

}


void LAST_JUDGE_PROC(void)
{

		if(( uwTick - key_push_setpoint)<=800)
		{
				if( key_u == 2)  key_change_long_short = 0;
				if( key_u == 3)  key_change_long_short = 0; 
		}
		else 
		{
		
			if( key_o == 2)  key_change_long_short = 1; 
			if( key_o == 3)  key_change_long_short = 1; 
 

		}

}







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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

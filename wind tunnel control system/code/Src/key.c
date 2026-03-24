#include "key.h"

uint8_t key_scan(void)
{

	uint8_t key_val = 0;
	
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET)   key_val = 1;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET)   key_val = 3;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_RESET)  key_val = 2;
	if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET)  key_val = 4;
	
	
	
	return key_val;
}
	
	
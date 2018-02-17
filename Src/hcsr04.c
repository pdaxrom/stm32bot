#include "main.h"
#include "stm32f1xx_hal.h"
#include "hcsr04.h"

extern TIM_HandleTypeDef htim1;

static int sonar_value;
static int sonar_ready;

void sonar_start()
{
	  volatile int i;
	  HAL_GPIO_WritePin(SONAR_TRIGGER_GPIO_Port, SONAR_TRIGGER_Pin, GPIO_PIN_SET);
	  for (i = 0; i < 100; i++) ;
	  HAL_GPIO_WritePin(SONAR_TRIGGER_GPIO_Port, SONAR_TRIGGER_Pin, GPIO_PIN_RESET);
	  sonar_ready = RESET;
}

int sonar_is_ready()
{
	return (sonar_ready == SET);
}

int sonar_distance()
{
	return sonar_value * 165 / 1000;
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
	if (pin == SONAR_ECHO_Pin) {
		if (HAL_GPIO_ReadPin(SONAR_ECHO_GPIO_Port, SONAR_ECHO_Pin) == GPIO_PIN_SET) {
			sonar_ready = RESET;
			__HAL_TIM_SET_COUNTER(&htim1, 0);
		} else {
			sonar_value = __HAL_TIM_GET_COUNTER(&htim1);
			sonar_ready = SET;
		}
	}
}

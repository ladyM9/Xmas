#include "stm32c0xx_hal.h"
#include "buzzer.h"

void melody(TIM_HandleTypeDef *_htim, uint32_t freq, uint32_t duration_melody)
{

	//Calculation for prescaler = fCPU/ (period * freq of counter) - 1
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

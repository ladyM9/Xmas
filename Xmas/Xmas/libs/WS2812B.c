#include "stm32c0xx_hal.h"
#include "WS2812B.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

uint16_t buffer[28]; //pazi sto ti pise u IOC-u za DMA settings u ovom slucaju je Half Word sto je uint16_t

//buffer za LEDICE
uint32_t *pwmBuffer = NULL;


void begin(TIM_HandleTypeDef *_htim, DMA_HandleTypeDef *_dmahtim ,uint32_t channel, uint16_t numofleds)
{
	pwmBuffer = (uint32_t*)malloc(numofleds * sizeof(uint32_t));
	memset((uint32_t*)pwmBuffer, 0, sizeof(uint32_t) * numofleds);

	__HAL_TIM_SET_PRESCALER(_htim, 5);
	__HAL_TIM_SET_AUTORELOAD(_htim, 9);

}
void turnOnLed(TIM_HandleTypeDef *_htim, DMA_HandleTypeDef *_dmahtim  ,uint32_t channel, uint16_t numofleds)
{



	for(int i = 0; i < numofleds; i++)
	{
	convertToPWM(buffer, pwmBuffer[i]);
	__HAL_TIM_ENABLE_DMA(_htim, TIM_DMA_CC1);
	__HAL_TIM_SET_COUNTER(_htim, 0);
	HAL_DMA_Start(_dmahtim, (uint32_t)buffer, (uint32_t)&(_htim->Instance->CCR1), sizeof(buffer)/sizeof(uint16_t));
	HAL_TIM_PWM_Start(_htim, channel);
	HAL_DMA_PollForTransfer(_dmahtim, HAL_DMA_FULL_TRANSFER  , 5);
	HAL_TIM_PWM_Stop(_htim, channel);
	__HAL_TIM_DISABLE_DMA(_htim, TIM_DMA_CC1);
	}
	HAL_Delay(50);



}
void setLed( uint8_t index, uint8_t g, uint8_t r, uint8_t b)
{
	if(index < 12)
	{
	pwmBuffer[index] = ( (uint32_t)g<<16 | (uint32_t)r<<8 | (uint32_t)b );
	}
}

void convertToPWM(uint16_t *bufferLEDs, uint32_t rgbBuffer)
{

	for(int i = 0; i < 24 ; i++)
	{
		uint8_t bit = (rgbBuffer >> (23-i) & 1);
		if(bit == 1)
		{
			bufferLEDs[i + 2] = 6;

		}
		else
		{
			bufferLEDs[i + 2] = 3;
		}

	}




}




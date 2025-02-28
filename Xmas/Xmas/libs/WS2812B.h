#ifndef __WS2812B_H__
#define __WS2812B_H__


void begin(TIM_HandleTypeDef *_htim, DMA_HandleTypeDef *_dmahtim ,uint32_t channel, uint16_t numofleds);
void turnOnLed(TIM_HandleTypeDef *_htim, DMA_HandleTypeDef *_dmahtim ,uint32_t channel, uint16_t numofleds);
void setLed( uint8_t index, uint8_t g, uint8_t r, uint8_t b);
void convertToPWM(uint16_t *bufferLEDs, uint32_t rgbBuffer);
void X0();
void stars();
void stars2();

#endif

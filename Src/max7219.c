#include "main.h"
#include "stm32f1xx_hal.h"
#include "max7219.h"

typedef enum {
	REG_NO_OP 			= 0x00 << 8,
	REG_DIGIT_0 		= 0x01 << 8,
	REG_DIGIT_1 		= 0x02 << 8,
	REG_DIGIT_2 		= 0x03 << 8,
	REG_DIGIT_3 		= 0x04 << 8,
	REG_DIGIT_4 		= 0x05 << 8,
	REG_DIGIT_5 		= 0x06 << 8,
	REG_DIGIT_6 		= 0x07 << 8,
	REG_DIGIT_7 		= 0x08 << 8,
	REG_DECODE_MODE 	= 0x09 << 8,
	REG_INTENSITY 		= 0x0A << 8,
	REG_SCAN_LIMIT 		= 0x0B << 8,
	REG_SHUTDOWN 		= 0x0C << 8,
	REG_DISPLAY_TEST 	= 0x0F << 8,
} MAX7219_REGISTERS;

extern SPI_HandleTypeDef hspi1;

static void max7219_clean(void);
static void sendData(uint16_t data);

static uint8_t framebuffer[] = { 0xFF, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xFF };

void max7219_init(uint8_t intensivity)
{
	HAL_Delay(800);
	max7219_setIntensivity(intensivity);
	max7219_clean();
	max7219_display(framebuffer);
}

void max7219_setIntensivity(uint8_t intensivity)
{
	if (intensivity > 0x0F)
		return;
	sendData(REG_SHUTDOWN | 0x01);
	sendData(REG_DECODE_MODE | 0x00);
	sendData(REG_SCAN_LIMIT | 0x07);
	sendData(REG_INTENSITY | intensivity);
}

static void max7219_clean()
{
	sendData(REG_DIGIT_0 | 0x00);
	sendData(REG_DIGIT_1 | 0x00);
	sendData(REG_DIGIT_2 | 0x00);
	sendData(REG_DIGIT_3 | 0x00);
	sendData(REG_DIGIT_4 | 0x00);
	sendData(REG_DIGIT_5 | 0x00);
	sendData(REG_DIGIT_6 | 0x00);
	sendData(REG_DIGIT_7 | 0x00);
}

static void sendData(uint16_t data)
{
	HAL_GPIO_WritePin(MATRIXLED_CS_GPIO_Port, MATRIXLED_CS_Pin, GPIO_PIN_RESET);

	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);

	HAL_GPIO_WritePin(MATRIXLED_CS_GPIO_Port, MATRIXLED_CS_Pin, GPIO_PIN_SET);
}

void max7219_display(uint8_t* array)
{
	sendData(REG_SHUTDOWN | 0x01);
	sendData(REG_DECODE_MODE | 0x00);
	sendData(REG_SCAN_LIMIT | 0x07);

	sendData(REG_DIGIT_0 | array[0]);
	sendData(REG_DIGIT_1 | array[1]);
	sendData(REG_DIGIT_2 | array[2]);
	sendData(REG_DIGIT_3 | array[3]);
	sendData(REG_DIGIT_4 | array[4]);
	sendData(REG_DIGIT_5 | array[5]);
	sendData(REG_DIGIT_6 | array[6]);
	sendData(REG_DIGIT_7 | array[7]);
}

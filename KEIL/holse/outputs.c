#include "outputs.h"
#include "main.h"
#include "config.h"
#include "spi.h"


//type must  fit all outputs see MAX_OUTPUTS in config.h
uint16_t curStateOutputs = 0; //TODO: Use for this var backup registers



void enableOutputs(void){
	//HAL_GPIO_WritePin(OUT_ENABLE_GPIO_Port, OUT_ENABLE_Pin, GPIO_PIN_RESET);
	setOutputs(curStateOutputs);
	HAL_GPIO_WritePin(LED_ENABLE_GPIO_Port, LED_ENABLE_Pin, GPIO_PIN_RESET);
};
	

void setOutputs(uint16_t outputs){
	curStateOutputs = outputs;
	HAL_SPI_Transmit(&hspi2, (uint8_t *) &curStateOutputs, 2, 50);
	//for led: toggle pin to push data to out registers
	HAL_GPIO_WritePin(LED_PUSH_DATA_GPIO_Port, LED_PUSH_DATA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_PUSH_DATA_GPIO_Port, LED_PUSH_DATA_Pin, GPIO_PIN_SET);
	//for out: toggle pin to push data to out registers
	HAL_GPIO_WritePin(LED_PUSH_DATA_GPIO_Port, OUT_PUSH_DATA_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LED_PUSH_DATA_GPIO_Port, OUT_PUSH_DATA_Pin, GPIO_PIN_SET);
};

void setOutputOn(int num) {
	if (num < 0 || num >= MAX_OUTPUTS) return;
	setOutputs(1 << num | curStateOutputs);
};

void setOutputOff(int num) {
	if (num < 0 || num >= MAX_OUTPUTS) return;
	setOutputs(~(1 << num) & curStateOutputs);
};
void setOutputToggle(int num) {
	if (num < 0 || num >= MAX_OUTPUTS) return;
	setOutputs(1 << num ^ curStateOutputs);
};

int getOutputState(int num) {
	if (num < 0 || num >= MAX_OUTPUTS) return -1;
	if(1 << num & curStateOutputs) return 1;
	else return 0;
};
uint16_t getOutputsState(void) {
	return curStateOutputs;
};
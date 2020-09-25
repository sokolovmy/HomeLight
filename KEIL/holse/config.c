#include "config.h"
#include "STM32_EEPROM_SPI.h"
#include "spi.h"
#include "string.h"


char signature[] = "c4b8249f1fd7ee005a77bdfbdd2c9108";
struct __attribute__((__packed__)) {
	ConfigInput configInputs[16];
	ConfigInput configInputsLPress[16];
	ConfigTimer configTimers[16];
} config;




void setInput(int input, ConfigOp op, BitPorts out) {
	if (input >= MAX_INPUTS) return;
	config.configInputs[input].op = op;
	config.configInputs[input].out = out;
};
void setInputLPress(int input, ConfigOp op, BitPorts out) {
	if (input >= MAX_INPUTS) return;
	config.configInputsLPress[input].op = op;
	config.configInputsLPress[input].out = out;
};

void setTimer(int timer, ConfigOp op, BitPorts out, uint32_t secs) {
	if (timer >= MAX_TIMERS) return;
	config.configTimers[timer].op = op;
	config.configTimers[timer].out = out;
	config.configTimers[timer].secs = secs;
};
ConfigInput * getInput(int input){
	if (input >= MAX_INPUTS) return NULL;
	return &config.configInputs[input];
};

ConfigInput * getInputLPress(int input){
	if (input >= MAX_INPUTS) return NULL;
	return &config.configInputsLPress[input];
};

ConfigTimer * getTimer(int timer){
	if (timer >= MAX_INPUTS) return NULL;
	return &config.configTimers[timer];
};

int loadFromFlash(void) {
	EEPROM_SPI_INIT(&hspi1);
	char buf[sizeof(signature)] = {0};
	EEPROM_SPI_ReadBuffer((uint8_t *)buf, 0, sizeof(signature));
	if (strncmp(signature, buf, sizeof(signature)) == 0) // read from flash config
		EEPROM_SPI_ReadBuffer((uint8_t *)&config, sizeof(signature), sizeof(config));
	else {
		memset(&config, 0, sizeof(config));
		config.configInputsLPress[0].op = off;
		config.configInputsLPress[0].out = 0xFF;
		for(int i = 0; i < MAX_INPUTS; i++) {
			config.configInputs[i].op = toggle;
			config.configInputs[i].out = 1 << i;
		}
	}
	return 0;
};

int saveToFlash(void) {
	EEPROM_SPI_INIT(&hspi1);
	EepromOperations res = EEPROM_SPI_WriteBuffer((uint8_t *)signature, 0, sizeof(signature));
	if (res != EEPROM_STATUS_COMPLETE) return -1;
	EEPROM_SPI_WriteBuffer((uint8_t *)&config, sizeof(signature), sizeof(config));
	if (res != EEPROM_STATUS_COMPLETE) return -2;
	return 0;
};

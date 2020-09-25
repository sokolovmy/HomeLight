
#ifndef __CONFIG_HOME_LIGHT
#define __CONFIG_HOME_LIGHT

#include "stdint.h"
#include "stddef.h"

#define MAX_OUTPUTS 16
#define MAX_INPUTS 16
#define MAX_TIMERS 16
typedef uint16_t BitPorts;
typedef enum {
	nop = 0, //no operation
	toggle = 1,
	on = 2,
	off = 3,
	timerNop = 0x80,
	timerToggle = 0x81,
	timerOn = 0x82,
	timerOff = 0x83
} ConfigOp;

typedef struct __attribute__((__packed__)) {
	ConfigOp op; //operation
	BitPorts out; //output ports | timer (bitwise)
} ConfigInput;
typedef struct __attribute__((__packed__)) {
	ConfigOp op; //operation
	BitPorts out; //output ports | timer (bitwise)
	uint32_t secs;
} ConfigTimer;


void setInput(int input, ConfigOp op, BitPorts out);
void setInputLPress(int input, ConfigOp op, BitPorts out);
void setTimer(int timer, ConfigOp op, BitPorts out,  uint32_t secs);
ConfigInput * getInput(int input);
ConfigInput * getInputLPress(int input);
ConfigTimer * getTimer(int timer);
int loadFromFlash(void);
int saveToFlash(void);


#endif


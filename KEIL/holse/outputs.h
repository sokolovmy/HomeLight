#ifndef __OUTPUTS__H
#define __OUTPUTS__H

#include "stdint.h"
#include "emCli.h"


void enableOutputs(void);
void setOutputs(uint16_t outputs);
void setOutputOn(int num);
void setOutputOff(int num);
void setOutputToggle(int num);
int getOutputState(int num);
uint16_t getOutputsState(void);

#endif

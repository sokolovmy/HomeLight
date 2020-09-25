#ifndef __CONS_H__
#define __CONS_H__


#include "emCLI.h"
#include "usbd_cdc_if.h"
#include "cmsis_os.h"
//#include "stdint.h"

#define TERM_TIMEOUT 120 //Timeout in seconds about :)
#define MAX_WORD_LENGTH 6 + 1

//char * consBuf = 0;
void consInit(void);
void putBufPtr(uint8_t * Buf, uint32_t * Len);


#endif


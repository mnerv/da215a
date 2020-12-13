/*
 * hmi.c
 *
 * Functions for user interaction.
 *
 * Author:  Mathias Beckius
 *
 * Date:    2014-11-28
 */

#ifndef HMI_H_
#define HMI_H_

#include <inttypes.h>

void hmi_init(void);
uint8_t input_int(char*, uint16_t*);
void output_msg(char*, char*, uint8_t);

#endif /* HMI_H_ */
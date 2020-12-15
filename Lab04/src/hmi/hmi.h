/**
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
uint8_t input_int(const char* p_msg, uint16_t* p_int_nr);
void output_msg(const char* p_str1, const char* p_str2,
                uint8_t delay_after_msg);

#endif /* HMI_H_ */
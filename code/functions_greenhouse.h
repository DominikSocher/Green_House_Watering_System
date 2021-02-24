/*
 * function_greenhouse.h
 *
 *  Created on: 18.12.2020
 *      Author: Dominik
 *      function declarations
 */

#ifndef FUNCTIONS_GREENHOUSE_H_
#define FUNCTIONS_GREENHOUSE_H_

#include "sierra_includes.h"

 extern void hmi(alt_u8 welcome_flag,alt_u8 mode, alt_u8 level, alt_u8 level_old, alt_u8 level_new, alt_u32 light, alt_u32 humidity);
 extern alt_u32 analog_map(alt_u32 raw_data, alt_u32 in_min, alt_u32 in_max, alt_u32 out_min, alt_u32 out_max);
 extern alt_u32 analog_value(alt_u8 channel);
 extern alt_u8 full_auto(alt_u32 light, alt_u32 humidity);
 extern void error_handler(alt_u8 reset, alt_u8 *pump, alt_u8 *level, alt_u8 *error_flag1, alt_u8 *mode);

#endif /* FUNCTIONS_GREENHOUSE_H_ */

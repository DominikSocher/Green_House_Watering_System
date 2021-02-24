/*
 * sierra_includes.h
 *
 *  Created on: 18.12.2020
 *      Author: Dominik
 *      includes and definitions for sierra
 */

#ifndef SIERRA_INCLUDES_H_
#define SIERRA_INCLUDES_H_

//include Sierra-Driver
#include "altera_avalon_sierra_ker.h"
#include <altera_avalon_sierra_io.h>
#include <altera_avalon_sierra_regs.h>
#include <altera_avalon_sierra_name.h>
#include <altera_avalon_pio_regs.h>
#include <altera_avalon_timer_regs.h>
#include <DE10_Lite_VGA_Driver.h>
#include <char_map.h>
#include <draw_vga.h>
#include <stdio.h>
#include <DE10_Lite_Arduino_Driver.h>
#include "sys/alt_irq.h"

//logging
#define DEF_LOGGING_PRINT

//Semaphore definitions
#define sem_id_1 1 //global variables
#define sem_id_2 2 // flags
//#define sem_id_3 3
//#define sem_id_4 4
//#define sem_id_5 5
//#define sem_id_6 6
//#define sem_id_7 7
//#define sem_id_8 8

//Task definition
#define idle 0
#define hmi_task 1
#define analog_task 2
#define digital_in_task 3
#define auto_task 4
#define error_task 5
//#define task_f 6
//#define task_g 7

//task stack size definition
#define stack_size 1000
//task size allocation
char idle_stack[stack_size];
char hmi_stack[stack_size];
char analog_stack[stack_size];
char digital_in_stack[stack_size];
char auto_stack[stack_size];
char error_stack[stack_size];
//char task_g_stack[stack_size];

//sierra task
extern void idle_code(void);
extern void hmi_code(void);
extern void analog_code(void);
extern void digital_in_code(void);
extern void auto_code(void);
extern void error_code(void);

//global variables
extern alt_u8 key_flag;
extern alt_u8 key_flag1;
extern alt_u8 key_flag2;
extern alt_u8 reset_flag;
extern alt_u8 manual_flag;
extern alt_u8 pump_flag;
extern alt_u8 welcome_flag;
extern alt_u8 error_flag1;
extern alt_u8 error_flag2;
extern alt_u8 tank_level;
extern alt_u8 level_new;
extern alt_u8 level_old;
extern alt_u32 water_flow;
extern alt_u32 light, humidity; //analog 1 light sensor, analog 2 humidity sensor

#endif /* SIERRA_INCLUDES_H_ */

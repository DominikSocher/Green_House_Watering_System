/*
 * hmi_code.c
 *
 *  Created on: 29.12.2020
 *      Author: Dominik
 */

#include "sierra_includes.h"
#include "functions_greenhouse.h"

//Global variables
alt_u8 key_flag = 0;
alt_u8 key_flag1 = 0;
alt_u8 key_flag2 = 0;
alt_u8 reset_flag = 0;
alt_u8 manual_flag = 0;
alt_u8 pump_flag = 0;
alt_u8 welcome_flag = 0;
alt_u8 error_flag1 = 0;
alt_u8 error_flag2 = 0;
alt_u8 tank_level = 100;
alt_u8 level_new = 100;
alt_u8 level_old = 100;
alt_u32 water_flow = 0;
alt_u32 light, humidity = 0; //analog 1 light sensor, analog 2 humidity sensor

void hmi_code(void)
{
	task_periodic_start_union test;
    //printf("hmi,Prio 1\n ");
    init_period_time(75); // 2 seconds period time

    while(1) // Loop forever
    {
       	test = wait_for_next_period(); //every 1 second
        if((test.periodic_start_integer & 0x1) != 0)
        {
        	printf("deadline miss, plot_acc");
        }
        hmi(welcome_flag,manual_flag, tank_level, level_old, level_new, humidity, light);
    	//printf("HMI\n");
    }
}

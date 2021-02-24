/*
 * error_code.c
 *
 *  Created on: 30.12.2020
 *      Author: Dominik
 *      The error code task
 */

#include "functions_greenhouse.h"
#include "sierra_includes.h"

void error_code(void)
{
	task_periodic_start_union test;
   // printf("digital_in,Prio 1\n ");
    init_period_time(50); // 1 seconds period time

    while(1) // Loop forever
    {
       	test = wait_for_next_period(); //every 1 second
        	if((test.periodic_start_integer & 0x1) != 0)
        	{
        		printf("deadline miss, plot_acc");
        	}
       //call error handler and check
       error_handler(reset_flag, &pump_flag, &tank_level, &error_flag1, &manual_flag);
       //reset
       if(reset_flag == 1)
       {
    	   sem_take(sem_id_1);
    	   level_new = 100;
    	   level_old = 100;
    	   sem_release(sem_id_1);
       }
    	//printf("error_code");
    }
}

/*
 * auto_code.c
 *
 *  Created on: 30.12.2020
 *      Author: Dominik'
 *      The auto code task
 */

#include "functions_greenhouse.h"
#include "sierra_includes.h"

void auto_code(void)
{
	task_periodic_start_union test;
  //  printf("auto ,Prio 1\n ");
    init_period_time(25); // 1 seconds period time
    arduino_pin_mode(6, 1);
    arduino_pin_mode(8,0);

    while(1) // Loop forever
    {
       	test = wait_for_next_period(); //every 1 second
        	if((test.periodic_start_integer & 0x1) != 0)
        	{
        		printf("deadline miss, plot_acc");
        	}
       	if(error_flag1 == 0 && welcome_flag == 1)
        {
        	//auto mode
        	if (manual_flag == 0)
        	{
        		pump_flag = full_auto(humidity,light);
        		sem_take(sem_id_1);
        		level_old = level_new;
        		sem_release(sem_id_1);
        	}
        	//Manual Mode
        	else if (manual_flag == 1 )
        	{
        		//Hand mode pump is a dead-man-switch
        		if(key_flag1 == 1)
        		{
        			sem_take(sem_id_2);
        			pump_flag = 1;
        			sem_release(sem_id_2);
        		}
        		else
        		{
        			sem_take(sem_id_2);
        			pump_flag = 0;
        			sem_release(sem_id_2);
        		}
        	}
        	else pump_flag = 0;
        	//Subtract water level
        	sem_take(sem_id_2);
        	if(pump_flag == 1)
        	{
        		//hall sensor
        		if( arduino_digital_read(8))
        			{
        				//hall sensor increments variable
        				sem_take(sem_id_1);
        				water_flow++;
        				tank_level = tank_level - water_flow;
        				sem_release(sem_id_1);
        			}
        		water_flow = 0;
        		level_new = tank_level;
        	}
        	sem_release(sem_id_2);
       // printf("auto %d ", water_flow);
        }
    }
}

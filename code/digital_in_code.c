/*
 * digital_in_code.c
 *
 *  Created on: 30.12.2020
 *      Author: Dominik
 *
 *      The digital in code task
 */

#include "functions_greenhouse.h"
#include "sierra_includes.h"

void digital_in_code(void)
{
	task_periodic_start_union test;
   // printf("digital_in,Prio 1\n ");
    init_period_time(15); // 1 seconds period time
    arduino_pin_mode(6, 1);

    while(1) // Loop forever
    {
       	test = wait_for_next_period(); //every 1 second
        	if((test.periodic_start_integer & 0x1) != 0)
        	{
        		printf("deadline miss, plot_acc");
        	}
        //switch between manual and auto mode
        sem_take(sem_id_2);
        key_flag = key_down_up(2);
        sem_release(sem_id_2);
		sem_take(sem_id_2);
		key_flag1 = key_down_up(3);
		sem_release(sem_id_2);
        if(key_flag == 1)
        {
        	sem_take(sem_id_2);
        	manual_flag = !manual_flag;
        	sem_release(sem_id_2);
        }
        sem_take(sem_id_2);
        reset_flag = key_down_up(9);
        sem_release(sem_id_2);
		sem_take(sem_id_2);
		arduino_digital_write(6, pump_flag);
		sem_release(sem_id_2);
    	const alt_u8 key_mask = IORD_ALTERA_AVALON_PIO_DATA(PIO_BUTTONS_IN_BASE);
    	const alt_u8 key0_in = key_mask & 0x1;
    	if(key0_in == 0 && key0_in != key_flag2)
    	{
    		//key0 pressed call print_frame
    		clear_screen(Col_Black);
    		sem_take(sem_id_2);
    		welcome_flag = 1;
    		sem_release(sem_id_2);
    	}
    	key_flag2 = key0_in;

    	//printf("digital_in %d ", welcome_flag);
    }
}

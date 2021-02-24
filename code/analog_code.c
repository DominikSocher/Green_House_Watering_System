/*
 * analog_code.c
 *
 *  Created on: 30.12.2020
 *      Author: Dominik
 *
 *      The analog code task
 *
 */
#include "sierra_includes.h"
#include "functions_greenhouse.h"

//define analog channels
#define CH0 0
#define CH1 1

//alt_u32 light = 0;
//alt_u32 humidity = 0; //analog 1 light sensor, analog 2 humidity sensor

void analog_code(void)
{
	task_periodic_start_union test;
    //printf("analog,Prio 1\n ");
    init_period_time(50); // 1 seconds period time

    while(1) // Loop forever
    {
       	test = wait_for_next_period(); //every 1 second
        if((test.periodic_start_integer & 0x1) != 0)
        {
        	printf("deadline miss, plot_acc");
        }
        sem_take(sem_id_1);
        //call analog function
        light = analog_value(CH1);
        sem_release(sem_id_1);
        sem_take(sem_id_1);
        humidity = analog_value(CH0);
        sem_release(sem_id_1);
    	//printf("analog");
    }
}

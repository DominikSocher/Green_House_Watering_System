/*
 * main.c
 *
 *  Created on: 18.12.2020
 *      Author: Dominik
 *      In the main function all tasks are getting created
 */

#include "functions_greenhouse.h"
#include "sierra_includes.h"

int main()
{
	Sierra_Initiation_HW_and_SW();
	// HW Version
	printf("  Sierra HW version = %d\n", sierra_HW_version());
	printf("  Sierra SW driver version = %d\n", sierra_SW_driver_version());
	//analog input init
	arduino_analog_init(MODULAR_ADC_0_SEQUENCER_CSR_BASE,MODULAR_ADC_0_SAMPLE_STORE_CSR_BASE);
	//clear screen at startup
	clear_screen(Col_Black);
	//welcome screen
	vga_init();
	/*********************************************************************
	* Initialize time base register.
	* This example     : 50 MHz system-clock
	* Wanted tick time : 20 ms (50Hz)
	* Formula gives    : 20 ms x 50 MHx / 1000 => 1000(dec)
	* ******************************************************************/
	set_timebase(1000);
    //create task
	task_create(idle, 0, READY_TASK_STATE, idle_code, idle_stack, stack_size);
	task_create(hmi_task, 1, READY_TASK_STATE, hmi_code, hmi_stack, stack_size);
	task_create(analog_task, 4, READY_TASK_STATE, analog_code, analog_stack, stack_size);
	task_create(digital_in_task, 5, READY_TASK_STATE, digital_in_code, digital_in_stack, stack_size);
	task_create(auto_task, 9, READY_TASK_STATE, auto_code, auto_stack, stack_size);
	task_create(error_task, 2, READY_TASK_STATE, error_code, error_stack, stack_size);
	tsw_on();

	while(1)
	{
	    // ERROR!!
	    printf ("* ERROR! SYSTEM FAILED *\n ");
	}
}



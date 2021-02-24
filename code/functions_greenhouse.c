/*
 * main_screen.c
 *
 *  Created on: 18.12.2020
 *      Author: Dominik
 */

#include "functions_greenhouse.h"

#define light_threshold 25
#define humidity_threshold 65
#define error_level 95

/**********************************************
 * function for the HMI prints system relevant
 * Information to a vga screen
 *
 * parameter
 * welcome_flag execute when true
 * mode			flag holds mode
 * level		actual level of tank
 * level_old	old tank level
 * level_new	new tank level
 * light		actual light in percent
 * Humidity		actual moister in percent
 * return type
 * 	void
 **********************************************/
void hmi(alt_u8 welcome_flag,alt_u8 mode, alt_u8 level, alt_u8 level_old, alt_u8 level_new, alt_u32 light, alt_u32 humidity)
{
	if(welcome_flag == 1)
	{
		//frame
		draw_hline(0, 120, 320, Col_White);
		draw_vline(160,0,240, Col_White);
		//tank
		tty_print(100, 80,"Level:", Col_White, Col_Black);
		sem_take(sem_id_1);
		int_print(100, 100, level,3, Col_White, Col_Black);
		sem_release(sem_id_1);
		draw_vline(60,5, 100, Col_White);
		draw_hline(60,105, 26, Col_White);
		draw_vline(85,5, 100, Col_White);
		if(level_new == level_old)
		{
			//fill tank
			for(size_t i = 61; i < 85; i ++)
			{
				for(size_t j = 105-level_new; j < 105; j ++)
				{
					write_pixel(i, j, Col_Blue);
				}
			}
		}
		else
		//empty tank
		for(size_t k = 61; k < 85; k++)
		{
			for(size_t l = 5; l<105-level_new; l++)
			{
				write_pixel(k, l,Col_Black);
			}
		}
		tty_print(170, 10,"Sensor Values", Col_White, Col_Black);
		tty_print(170, 40,"Light:", Col_White, Col_Black);
		tty_print(170, 60,"Soil:", Col_White, Col_Black);
		//tty_print(170, 80,"Last watering:", Col_White, Col_Black);
		sem_take(sem_id_1);
		int_print(250, 40, light,3,Col_White, Col_Black);
		int_print(250, 60, humidity,3,Col_White, Col_Black);
		sem_release(sem_id_1);
		tty_print(20, 130,"Mode", Col_White, Col_Black);
		tty_print(20, 220,"Auto", Col_White, Col_Black);
		tty_print(100, 220, "Hand", Col_White,Col_Black);
		sem_take(sem_id_2);
		if(mode == 1)
		{
			draw_filled_circle(38, 200, 12,Col_White);
			draw_filled_circle(118, 200, 12,Col_Red);
		}
		else if (mode == 0)
		{
			draw_filled_circle(38, 200, 12,Col_Red);
			draw_filled_circle(118, 200, 12,Col_White);

		}
		tty_print(170, 130,"ErrorLog", Col_White, Col_Black);
		sem_release(sem_id_2);
	}
}

/**********************************************
 * function to map the analog raw data
 * This function maps the analog value min/max
 * to a corresponding value.
 *
 * parameter
 * 	raw_data 	raw analog data
 * 	in_min 		raw minimum data
 * 	in_max 		raw maximum data
 * 	out_min 	mapped minimum data
 * 	out_max 	mapped maximum data
 *
 * return type
 * 	alt_u32 mapped analog value
 **********************************************/
alt_u32 analog_map(alt_u32 raw_data, alt_u32 in_min, alt_u32 in_max, alt_u32 out_min, alt_u32 out_max)
{
	return (raw_data - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**********************************************
 * function checks ADC constantly and map value
 * to percent. returns mapped value
 *
 * parameter
 * 	alt_u8 channel variable for analog input channel
 *
 * return type
 * 	alt_u32 mapped_out
 **********************************************/
alt_u32 analog_value(alt_u8 channel)
{
	alt_u32 analog_in;
	alt_u32 mapped_out;
	analog_in = arduino_analog_read(channel);
	//map to percent
	mapped_out = analog_map(analog_in,0,2765,0,100);
	return mapped_out;
}

/**********************************************
 * function checks analog values if they are in predefines
 * range set output high
 *
 * parameter
 * light 		actual light data
 * humidity		actual humidity data
 *
 * return type
 * 	output
 **********************************************/
alt_u8 full_auto(alt_u32 light, alt_u32 humidity)
{
	alt_u8 output = 0;
	sem_take(sem_id_1);
	//check light and soil within range
	if(light < light_threshold && humidity > humidity_threshold )
	{
		output = 1;
	}
	else output = 0;
	sem_release(sem_id_1);
	return output;
}

/**********************************************
 * function handles one error. If tank empty
 * fill it. Halts system and change to hand mode
 *
 * parameter
 *  reset		digital in reset
 *  pump		pump flag
 *  level		tank level
 *  error_flag  error flag
 * 	mode        mode flag
 *
 * return type
 * 	alt_u32 mapped analog value
 **********************************************/
void error_handler(alt_u8 reset, alt_u8 * pump, alt_u8 *level, alt_u8 *error_flag1,alt_u8 *mode)
{
	//Error1 empty tank
	if(*level <= error_level)
	{
		sem_take(sem_id_2);
		*error_flag1 = 1;
		sem_release(sem_id_2);
		tty_print(170, 150,"Fill Tank", Col_Red, Col_Black);
		tty_print(170, 170,"Press PB_4", Col_Red, Col_Black);
		tty_print(170, 190,"to confirm", Col_Red, Col_Black);
		sem_take(sem_id_2);
		//stop pump, set mode to hand
		*mode = 1;
		*pump = 0;
		sem_release(sem_id_2);
		if(reset == 1)
		{
			sem_take(sem_id_1);
			//fill tank
			*level = 100;
			sem_release(sem_id_1);
		}
	}
	else if(*level == 100)
	{
		sem_take(sem_id_2);
		*error_flag1 = 0;
		sem_release(sem_id_2);
		//erase message
		for(size_t i = 170; i <= 300; i++)
		{
			for(size_t j = 150; j <= 200; j++)
			{
				write_pixel(i, j,Col_Black);
			}
		}
	}
}

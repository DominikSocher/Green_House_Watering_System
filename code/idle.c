/*
 * idle.c
 *
 *  Created on: 29.12.2020
 *      Author: Dominik
 */

#include "sierra_includes.h"

void idle_code(void)
{
    /* Never blocked. Idle shall only be in running or ready state, lowest priority and taskid 0 */
	//printf("IDLE,Prio 0\n");

  while(1) // Loop forever!
  {
	  for(size_t i=0; i<10000; i++);
    //  printf(".");
  }
}

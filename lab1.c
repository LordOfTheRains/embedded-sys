
/*****************************************************************************\
* Laboratory Exercises COMP 3510                                              *
* Author: Rain Li, David Harris                                               *
* Date  : February 7, 2018                                                    *
\*****************************************************************************/

/*****************************************************************************\
*                             Global system headers                           *
\*****************************************************************************/


#include "common.h"

/*****************************************************************************\
*                             Global data types                               *
\*****************************************************************************/

#include <stdint.h>


/*****************************************************************************\
*                             Global definitions                              *
\*****************************************************************************/

#define CHECK_BIT(var, pos) ((var) & (1 << (pos)))



/*****************************************************************************\
*                            Global data structures                           *
\*****************************************************************************/




/*****************************************************************************\
*                                  Global data                                *
\*****************************************************************************/




/*****************************************************************************\
*                               Function prototypes                           *
\*****************************************************************************/

void Control(void);



/*****************************************************************************\
* function: main()                                                            *
* usage:    Create an artificial environment for embedded systems. The parent *
*           process is the "control" process while children process will gene-*
*           generate events on devices                                        *
*******************************************************************************
* Inputs: ANSI flat C command line parameters                                 *
* Output: None                                                                *
*                                                                             *
* INITIALIZE PROGRAM ENVIRONMENT                                              *
* WHILE JOBS STILL RUNNING                                                    *
*    CREATE PROCESSES                                                         *
*    RUN LONG TERM SCHEDULER                                                  *
*    RUN SHORT TERM SCHEDULER                                                 *
*    DISPATCH NEXT PROCESS                                                    *
\*****************************************************************************/

int main (int argc, char **argv) {

   if (Initialization(argc,argv)){
     Control();
   } 
} /* end of main function */

/***********************************************************************\
 * Input : none                                                          *
 * Output: None                                                          *
 * Function: Monitor Devices and process events                          *
 \***********************************************************************/
void Control(void){
  int i;
  Status LastStatus=0;
  i = 0;
  while (1) {
    //printf("%10.3f   Flags = %d - \n ", Now(), Flags);
    //sleep(0); // Just to slow down to have time to see Flags
	if (CHECK_BIT(Flags, i)){ //event at device i
		DisplayEvent('d', &BufferLastEvent[i]);
		Server(&BufferLastEvent[i]);
		Flags &= ~(1<<i); // clear the ith bit
	}
	LastStatus = Flags;
  	//printf("\n >>>>>>>>>  >>> When: %10.3f  Flags = %d\n", Now(),
     //Flags); 
	if (i < 32){
		i++;
	}
	else
		i = 0;
	//printf("i = %d\n", i);
	}
}


/***********************************************************************\
* Input : None                                                          *
* Output: None                                                          *
* Function: This must print out the number of Events buffered not yet   *
*           not yet processed (Server() function not yet called)        *
\***********************************************************************/
void BookKeeping(void){
  int bufEvents = 0;
  /*for (int i = 0; i < MAX_NUMBER_DEVICES; i++){
	DisplayEvent('0', &BufferLastEvent[i]);
	if (BufferedLastEvent[i] != null){
	bufEvents++;
	}
  }
  printf("Buffered Events: %d\n", bufEvents);*/
  printf("\n >>>>>> Done\n");
}







/*
void Control(void){
  int i;
  Status LastStatus=0;
  i = 1;
  while (1) {
    //printf("%10.3f   Flags = %d - \n ", Now(), Flags);
    sleep(1); // Just to slow down to have time to see Flags
	if (CHECK_BIT(Flags, i)){ //event at device i
		DisplayEvent('d', &BufferLastEvent[j]);
		Server(&BufferLastEvent[i]);
		Flags &= ~i; // clear the ith bit
	}
	LastStatus = Flags;
  	printf("\n >>>>>>>>>  >>> When: %10.3f  Flags = %d\n", Now(),
     Flags); 
	if (i < 32){
		i++;
	}
	else
		i = 1;
	printf("i = %d\n", i);
}

*/



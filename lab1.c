
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
int processed[MAX_NUMBER_DEVICES] = {0}; // store the last event id that device seen
Timestamp start;
float responseTime[MAX_NUMBER_DEVICES] = {0};
void Control(void){
  int i;
  Status LastStatus=0;
  while (1) {
    if (Flags){
      start = Now();
      Flag temp = Flags;
      Flags = 0;
      int device = 0;
      while (temp){
        if (temp & 1){
          responseTime[device] += Now() - BufferLastEvent[device].When;
          processed[device]++;
          DisplayEvent('d', &BufferLastEvent[device]);
      		Server(&BufferLastEvent[device]);
          //printf("device: %d --- lastEID: %d\n",i, lastEID[i] );

        }
        temp = temp >> 1;
        device++;
      }
    }
  }
    //printf("%10.3f   Flags = %d - \n ", Now(), Flags);
    //sleep(0); // Just to slow down to have time to see Flags

}


/***********************************************************************\
* Input : None                                                          *
* Output: None                                                          *
* Function: This must print out the number of Events buffered not yet   *
*           not yet processed (Server() function not yet called)        *
\***********************************************************************/
void BookKeeping(void){
  Timestamp done = Now();
  int missed = 0;
  int total = 0;
   for (int i = 0; i < MAX_NUMBER_DEVICES ; i++){
      int numEvent = BufferLastEvent[i].EventID;
      if (numEvent > 0){
  	    DisplayEvent('b', &BufferLastEvent[i]);
        missed += numEvent - processed[i] + 1 ;
        printf("device: [%d] --- avg response time: %d\n",i,  responseTime[i]/numEvent );
        printf("device: [%d] --- processed: %d\n",i, processed[i] );
      }
  }
  printf("total turn around time %10.3f\n", done);
  printf("\n >>>>>> Done\n");
}

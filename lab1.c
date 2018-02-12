
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

double turnaround[MAX_NUMBER_DEVICES] = {0};
double responseTime[MAX_NUMBER_DEVICES] = {0};
void Control(void){
  int i;

  while (1) {
    if (Flags){
      unsigned temp = Flags; //temp is negative sometimes even if flag is not
      //printf("Flags = %d - \n ",Flags);
      //printf("temp = %d...... \n ",temp);
      Flags = 0;
      int device = 0;
      while (temp){
        if (temp & 1){
          responseTime[device] += Now() - BufferLastEvent[device].When;
      		Server(&BufferLastEvent[device]);
          turnaround[device] += Now() - BufferLastEvent[device].When;
          DisplayEvent('d', &BufferLastEvent[device]);
          processed[device]++;
        }
        temp = temp >> 1;
        device++;
        //printf("temp = %d - \n ",temp);
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

  int totalEvents = 0;
  printf("\nStart BookKeeping ...\n");
  printf("\nDevice\tmissed\tavg response time\tavg turnaround time\tlast event\n");
  for (int i = 0; i < MAX_NUMBER_DEVICES ; i++){
    int numEvent = BufferLastEvent[i].EventID + 1;
    if (numEvent > 0){
      float missed = numEvent - processed[i];
      printf("%d\t%5.2f",i,missed/numEvent*100.0);
      printf("\t\t%lf\t\t%lf\t%d\n",responseTime[i]/numEvent,turnaround[i]/numEvent,numEvent );
      //printf("device [%d]:missed %d percent events with avg response time: %lf\n",i, missed/numEvent*100 ,responseTime[i]/numEvent );
    }
  }
}


/*****************************************************************************\
* Laboratory Exercises COMP 3510                                              *
* Author: Saad Biaz                                                           *
* Date  : March 5, 2013                                                   *
\*****************************************************************************/

/*****************************************************************************\
*                             Global system headers                           *
\*****************************************************************************/


#include "common.h"

/*****************************************************************************\
*                             Global data types                               *
\*****************************************************************************/



/*****************************************************************************\
*                             Global definitions                              *
\*****************************************************************************/





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
void InterruptRoutineHandlerDevice(void);
void BookKeeping();


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
* START CONTROL ROUTINE                                                       *
\*****************************************************************************/

int main (int argc, char **argv) {

   if (Initialization(argc,argv)){
     Control();
   }
} /* end of main function */

/***********************************************************************\
 * Input : none                                                          *
 * Output: None                                                          *
 * Function: Monitor Devices and process events (written by students)    *
 \***********************************************************************/
void Control(void){

  while (1){
    if (Flags){
      unsigned temp = Flags; //temp is negative sometimes even if flag is not
      //printf("Flags = %d - \n ",Flags);
      //printf("temp = %d...... \n ",temp);
      Flags = 0;
      int device = 0;
      while (temp){
        if (temp & 1){
      		Server(&BufferLastEvent[device]);
          turnaround[device] += Now() - BufferLastEvent[device].When;
          processed[device]++;
        }
        temp = temp >> 1;
        device++;
        //printf("temp = %d - \n ",temp);
      }
    }
  }
  }

}

int MAX_E_POWER = 4;
int MAX_EVENT_PER_DEV = 1 << MAX_E_POWER; //MAXIMUM NUMBER OF EVENTS PER DEVICE TO BUFFER
typedef struct EventQueue{
  Event unservedEvents[MAX_EVENT_PER_DEV];
  int nextToServe = 0;
  int nextToStore = 0;
} EventQueue;

int processed[MAX_NUMBER_DEVICES] = {0}; // store the last event id that device seen
double turnaround[MAX_NUMBER_DEVICES] = {0};
double responseTime[MAX_NUMBER_DEVICES] = {0};
EventQueue unserved[MAX_NUMBER_DEVICES];
/***********************************************************************\
* Input : None                                                          *
* Output: None                                                          *
* Function: This routine is run whenever an event occurs on a device    *
*           The id of the device is encoded in the variable flag        *
\***********************************************************************/
void InterruptRoutineHandlerDevice(void){
  printf("An event occured at %f  Flags = %d \n", Now(), Flags);
	// Put Here the most urgent steps that cannot wait
  unsigned temp = Flags; //temp is negative sometimes even if flag is not
  //printf("Flags = %d - \n ",Flags);
  //printf("temp = %d...... \n ",temp);
  Flags = 0;
  int device = 0;
  while (temp){
    if (temp & 1){
      unserved[device].unservedEvents[unserved[device].nextToStore] = BufferLastEvent[device]; //store the event
      unserved[device].nextToStore = (unserved[device].nextToStore + 1) & (MAX_EVENT_PER_DEV - 1);
      //Flags |= ~1; //clear the device flag
      DisplayEvent('d', &BufferLastEvent[device]);
      responseTime[device] += Now() - BufferLastEvent[device].When;
    }
    temp = temp >> 1;
    device++;
    //printf("temp = %d - \n ",temp);
  }
}


/***********************************************************************\
* Input : None                                                          *
* Output: None                                                          *
* Function: This must print out the number of Events buffered not yet   *
*           not yet processed (Server() function not yet called)        *
\***********************************************************************/
void BookKeeping(void){
  // For EACH device, print out the following metrics :
  // 1) the percentage of missed events, 2) the average response time, and
  // 3) the average turnaround time.
  // Print the overall averages of the three metrics 1-3 above
  int i;
  printf("\nStart BookKeeping ...\n");
  printf("\nDevice\tmissed\tavg response time\tavg turnaround time\tlast event\n");
  for (i = 0; i < MAX_NUMBER_DEVICES ; i++){
    int numEvent = BufferLastEvent[i].EventID + 1;
    if (numEvent > 0){
      float missed = numEvent - processed[i];
      printf("%d\t%5.2f",i,missed/numEvent*100.0);
      printf("\t\t%lf\t\t%lf\t%d\n",responseTime[i]/numEvent,turnaround[i]/numEvent,numEvent );
      //printf("device [%d]:missed %d percent events with avg response time: %lf\n",i, missed/numEvent*100 ,responseTime[i]/numEvent );
    }
  }
}

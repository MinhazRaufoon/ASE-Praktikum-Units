#include "me_init.h"
void can_receive(void);


/********************************************************************
 *                         Application entry point                  *
 ********************************************************************/
int main(void) {

  /* Board and modules initialization */
  ME_Init();
  
  /* Timer configuration */
  // PIT_ConfigureTimerX(X,X);
  // PIT_StartTimer(X);
  /* Application main loop that runs forever*/
  for ( ; ; ) {
/********************************************************************
 *                           Main Loop                              *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                  Write down your logic here.                     *
 ********************************************************************/

   /* Operating System Delay*/
   osalThreadDelayMilliseconds(250UL);
  }
}



/********************************************************************
 *                   Can Reception Function                         *
 ********************************************************************/
void can_receive() {

}



/********************************************************************
 *                      Interrupt Functions                         *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                Interrupts can be handled below.                  *
 ********************************************************************
 *                   Interrupt Handlers for PIT                     *
 ********************************************************************/
/* void Pit_Channel_X(){
*
*   //Logic in here
*
*   //Clear Interrupt Flag
*
*
*/


/********************************************************************
*                   Interrupt Handlers for CAN Message Buffer       *
********************************************************************/
IRQ_HANDLER(SPC5_FLEXCAN0_BUF_08_11_HANDLER) {

// clear flags for all buffers here

}







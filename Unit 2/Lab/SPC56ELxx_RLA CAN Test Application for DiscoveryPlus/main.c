#include "me_init.h"

/********************************************************************
 *             Global variables and function declarations           *
 ********************************************************************/
void toggleU1Led();
void toggleU2Led();
int ID;
int speed = 0;
char direction = 'a';
int nextSpeed(void);
int shouldSend = 0;

void can_send(int bufferIdx, int data);


/********************************************************************
 *                         Application entry point                  *
 ********************************************************************/
int main(void) {

  /* Board and modules initialization */
  ME_Init();





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


void toggleU1Led() {
  if (U1 == 1) U1 = 0;
  else U1 = 1;
}
void toggleU2Led() {
  if (U2 == 1) U2 = 0;
  else U2 = 1;
}

int nextSpeed() {
  int toReturn = speed;
  if (direction == 'a') speed += 5;
  else speed -= 5;
  if (speed == 300) direction = 'd';
  if (speed == 0) direction = 'a';
  return toReturn;
}

void can_send(int bufferIdx, int data) {
  CAN_0.BUF[bufferIdx].CS.B.CODE = 0b1100;

  if (data >= 256) {
	  CAN_0.BUF[bufferIdx].DATA.B[0] = data % 256;
	  CAN_0.BUF[bufferIdx].DATA.B[1] = 1;
  } else {
	  CAN_0.BUF[bufferIdx].DATA.B[0] = data;
	  CAN_0.BUF[bufferIdx].DATA.B[1] = 0;
  }
}
/********************************************************************
 *                   Can Reception Function                         *
 ********************************************************************/

void can_receive() {
	P = ~P;
	if (CAN_0.IFRL.B.BUF5I == 1) {
		if (CAN_0.BUF[0].ID.B.STD_ID == 0xFF)
			U3 = ~U3;
		else if (CAN_0.BUF[0].ID.B.STD_ID == 1) {
			shouldSend = 1;
		}
	}
	CAN_0.IFRL.B.BUF5I = 1;
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

void myTimer(void) {
	toggleU1Led();
	if (shouldSend) can_send(8, nextSpeed());
	PIT.CHANNEL[1].TFLG.B.TIF = 1;
}



/********************************************************************
*                   Interrupt Handlers for CAN Message Buffer       *
********************************************************************/
IRQ_HANDLER(SPC5_FLEXCAN0_BUF_08_11_HANDLER) {
	CAN_0.IFRL.B.BUF8I = 1;


}






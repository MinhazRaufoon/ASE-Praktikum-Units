#include "me_init.h"

void toggleU1Led();
void toggleU2Led();

int shouldSend = 0;
int speed = 0;
char direction = 'a';
int nextSpeed();
void can_send(int bufferIdx, int data);

int isCanReceiveSuccess();
void can_receive(void);
int receiveCanMsgID();
int receiveCanMsgData();

/********************************************************************
 *                         Application entry point                  *
 ********************************************************************/
int main(void) {

  /* Board and modules initialization */
  ME_Init();
  
  /* Timer configuration */
  // PIT_ConfigureTimerX(X,X);
  PIT_ConfigureTimer1(1, 200);
  // PIT_StartTimer(X);
  PIT_StartTimer(1);
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

int nextSpeed() {
  int toReturn = speed;
  if (direction == 'a') speed += 5;
  else speed -= 5;
  if (speed == 300) direction = 'd';
  if (speed == 0) direction = 'a';
  return toReturn;
}

void toggleU1Led() {
  if (U1 == 1) U1 = 0;
  else U1 = 1;
}
void toggleU2Led() {
  if (U2 == 1) U2 = 0;
  else U2 = 1;
}

void vector60() {
  toggleU1Led();
}

void can_send(int bufferIdx, int data) {
  CAN_0.BUF[bufferIdx].CS.B.CODE = 0xC;
  CAN_0.BUF[bufferIdx].DATA.B[0] = data % 256;
  CAN_0.BUF[bufferIdx].DATA.B[1] = 0;
  
  if (data > 256) {
    CAN_0.BUF[bufferIdx].DATA.B[1] = 1;
  }
}

/********************************************************************
 *                   Can Reception Function                         *
 ********************************************************************/
int isCanReceiveSuccess() {
  if (CAN_0.IFRL.B.BUF5I == 1) return 1;
  return 0;
}

int receiveCanMsgID() {
  return CAN_0.BUF[0].ID.B.STD_ID;
}

int receiveCanMsgData() {
  int receivedData = CAN_0.BUF[0].DATA.B[0];
  if (CAN_0.BUF[0].DATA.B[1] == 1) receivedData += 256;
  return receivedData;
}

void can_receive() {
  int receivedCanID;
  int receivedData;

  U3 = 0;
  if (isCanReceiveSuccess()) {
    receivedCanID = receiveCanMsgID();
    
    if (receivedCanID == 0xFF) {
      toggleU2Led();
    } else if (receivedCanID == 1) {
      U3 = 1;
      shouldSend = 1;
    } 

    receivedData = receiveCanMsgData();
  }
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
void Pit_Channel_1(){
  //Logic in here
  vector60();
  if (shouldSend) can_send(8, nextSpeed());

  //Clear Interrupt Flag
  PIT.CHANNEL[1].TFLG.B.TIF = 1;
}


/********************************************************************
*                   Interrupt Handlers for CAN Message Buffer       *
********************************************************************/
IRQ_HANDLER(SPC5_FLEXCAN0_BUF_08_11_HANDLER) {

// clear flags for all buffers here
  CAN_0.IFRL.B.BUF8I = 1;
  CAN_0.IFRL.B.BUF9I = 1;
  CAN_0.IFRL.B.BUF10I = 1;
  CAN_0.IFRL.B.BUF11I = 1;
}







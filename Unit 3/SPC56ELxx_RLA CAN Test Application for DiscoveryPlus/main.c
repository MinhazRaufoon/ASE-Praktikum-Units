#include "me_init.h"

/********************************************************************
 *             Global variables and function declarations           *
 ********************************************************************/
#define AUTO 1
#define MANUAL 2

#define ALIVE = 2
#define ABSENT = 3

#define ID_LIGHT_STATES_MSG 0x201
#define ID_RPM_MSG 0x202
#define ID_ECU1_ALIVE_MSG 0x203
#define ID_ECU1_ERROR_MSG 0x204

#define ID_ECU2_INDICATOR_SWITCH 0x302
#define ID_ECU3_HEADLIGHT_SWITCH 0x403
#define ID_ECU2_ALIVE_MSG 0x304
#define ID_ECU2_ERROR_MSG 0x305

/* ECU STATE MANAGEMENT*/
struct State {
  int mode;

  // light states
  int indicatorStates; // left, right, hazard
  int headlightStates; // high, low,  parking

  int ecu2Status;
};

struct State ecu1State = {
  MANUAL, 0, 0, ABSENT
};

int getPotentiometerValue();
int getLightIntensity();
int getRPM();
int getLightState();
void adjustMode();
int isAutomaticMode();
void turnOnLowbeamAndParkingLight();
void indicateECU2Status();

void can_send(int bufferIdx, int id, int data, int dataLength);
void canSendRPMValue();
void canSendLightStates();
void canOnReceive();


/********************************************************************
 *                         Application entry point                  *
 ********************************************************************/
int main(void) {

  /* Board and modules initialization */
  ME_Init();

  PIT_ConfigureTimer(2, 100);
  PIT_StartTimer(2);

  PIT_ConfigureTimer(3, 400);
  PIT_StartTimer(3);

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
      adjustMode();
     /* Operating System Delay*/
     osalThreadDelayMilliseconds(250UL);
  }
}

/* UTIL */
int getPotentiometerValue() {
  return POT;
}

int getLightIntensity() {
  return LDR;
}

int getRPM() {
  return getPotentiometerValue() * 10;
}

int getLightState() {
  if (isAutomaticMode() && getLightIntensity() < 512) {
    turnOnLowbeamAndParkingLight();
  }

  int lightState = ecu1State.indicatorStates | (ecu1State.headlightStates << 3);
  return lightState;
}

void adjustMode() {
  if (SW1 == 1) ecu1State.mode = AUTO;
  else ecu1State.mode = MANUAL;
}

int isAutomaticMode() {
  if (ecu1State.mode == AUTO) return 1;
  return 0;
}

void turnOnLowbeamAndParkingLight() {
  ecu1State.headlightStates = ecu1State.headlightStates & 0x1;
}

void indicateECU2Status() {
  if (ecu1State.ecu2Status == ABSENT) P = ~P;
}

/********************************************************************
 *                   Can Reception Function                         *
 ********************************************************************/
void can_send(int bufferIdx, int id, int data, int dataLength) {
  CAN_0.BUF[bufferIdx].CS.B.CODE = 0b1100;
  CAN_0.BUF[bufferIdx].CS.B.LENGTH = dataLength;
  CAN_0.BUF[bufferIdx].MSG_ID.B.STD_ID = id;

  if (dataLength == 2) {
    if (data >= 256) {
      CAN_0.BUF[bufferIdx].DATA.B[0] = data & 0xFF;
      CAN_0.BUF[bufferIdx].DATA.B[1] = data >> 8;
    } else {
      CAN_0.BUF[bufferIdx].DATA.B[0] = data;
      CAN_0.BUF[bufferIdx].DATA.B[1] = 0;
    }
  }

  else if (dataLength == 1) {
    CAN_0.BUF[bufferIdx].DATA.B[0] = data;
  }
}

void canSendRPMValue() {
  int rpm = getRPM();
  can_send(8, ID_RPM_MSG, rpm, 2);
}

void canSendLightStates() {
  int lightState = getLightState();
  can_send(9, ID_LIGHT_STATES_MSG, lightState, 1);
}

void canSendECU1Status() {
  int statusID;

  if (ecu1State.ecu2Status == ABSENT) statusID = ID_ECU1_ERROR_MSG;
  else statusID = ID_ECU1_ALIVE_MSG;

  can_send(10, statusID, 0, 0);
}

void canOnReceive() {
  int id = CAN_0.BUF[0].ID.B.STD_ID;
  int data = CAN_0.BUF[0].DATA.B[0];

  if (id == ID_ECU2_INDICATOR_SWITCH) {
    ecu1State.indicatorStates = data & 0x7;
  } 
  else if (id == ID_ECU3_HEADLIGHT_SWITCH) {
    ecu1State.headlightStates = data & 0x7;
  }
  else if (id == ID_ECU2_ALIVE_MSG) {
    ecu1State.ecu2Status = ALIVE;
    P = 0;
  }
  else if (id == ID_ECU2_ERROR_MSG) {
    ecu1State.ecu2Status = ABSENT;
  }
}

void can_receive() {
	if (CAN_0.IFRL.B.BUF5I == 1) {
    canOnReceive();
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

void channel1_ISR(void) {
  /* gets called every 200ms */
  indicateECU2Status();
  canSendECU1Status();
  PIT.CHANNEL[1].TFLG.B.TIF = 1;
}

void channel2_ISR(void) {
  /* gets called every 100ms */
  canSendRPMValue();
  PIT.CHANNEL[2].TFLG.B.TIF = 1; 
}

void channel3_ISR(void) {
  /* gets called every 400ms */
  canSendLightStates();  
  PIT.CHANNEL[3].TFLG.B.TIF = 1;
}


/********************************************************************
*                   Interrupt Handlers for CAN Message Buffer       *
********************************************************************/
IRQ_HANDLER(SPC5_FLEXCAN0_BUF_08_11_HANDLER) {
	CAN_0.IFRL.B.BUF8I = 1;
  CAN_0.IFRL.B.BUF9I = 1;
  CAN_0.IFRL.B.BUF10I = 1;
}

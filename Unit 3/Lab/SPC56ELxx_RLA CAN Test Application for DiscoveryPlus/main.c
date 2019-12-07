#include "me_init.h"

/********************************************************************
 *             Global variables and function declarations           *
 ********************************************************************/
#define AUTO 1
#define MANUAL 2

#define ALIVE 2
#define ABSENT 3

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
  int indicatorStates; // left, right, hazard
  int headlightStates; // high, low,  parking
  int ecu2Status;
};
struct State ecu1State = {
  MANUAL, 7,  7, ABSENT
};

int getPotentiometerValue(void);
int getLightIntensity(void);
int getRPM(void);
int isAutomaticMode(void);
int getLightState(void);
void adjustMode(void);
void turnOnLowbeamAndParkingLight(void);
void indicateECU2Status(void);

void can_send(int bufferIdx, int id, int data, int dataLength);
void canSendRPMValue(void);
void canSendLightStates(void);
void canOnReceive(void);

/* Switches and buttons variable to be used to receive signals from board */
int SW1 = 0;
int SW2 = 0;
int SW3 = 0;
int SW4= 0;
int BT5= 0;
int BT6= 0;




/********************************************************************
 *                         Application entry point                  *
 ********************************************************************/
int main(void) {

  /* Board and modules initialization */
  ME_Init();

  /* Configure and start timmer channels */

  PIT_ConfigureTimer(1, 200);
  PIT_StartTimer(1);

  PIT_ConfigureTimer(2, 100);
    PIT_StartTimer(2);

    PIT_ConfigureTimer(3, 400);
        PIT_StartTimer(3);


  /* Application main loop that runs forever*/
for ( ; ; ) {
	adjustMode();
   /* Operating System Delay*/
   osalThreadDelayMilliseconds(250UL);
 }
}


/* UTIL */
int getPotentiometerValue(void) {
  return POT;
}

int getLightIntensity(void) {
  return LDR;
}

int getRPM(void) {
  return getPotentiometerValue() * 10;
}

int getLightState(void) {
  if (isAutomaticMode() && getLightIntensity() < 512) {
    turnOnLowbeamAndParkingLight();
  }

  int lightState = ecu1State.indicatorStates | (ecu1State.headlightStates << 3);
  return lightState;
}

void adjustMode(void) {
  if (SW1 == 1) ecu1State.mode = AUTO;
  else ecu1State.mode = MANUAL;
}

int isAutomaticMode(void) {
  if (ecu1State.mode == AUTO) return 1;
  return 0;
}

void turnOnLowbeamAndParkingLight(void) {
  ecu1State.headlightStates = ecu1State.headlightStates & 0x1;
}

void indicateECU2Status(void) {
  if (ecu1State.ecu2Status == ABSENT) {
	  //P = ~P;
	  //U1 = ~U1;
	  U1 = ~U1;U2=~U2;U3=~U3;
	  P=~P;
	  Tx = ~Tx;
  }
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
      CAN_0.BUF[bufferIdx].DATA.B[0] = data % 256;
      CAN_0.BUF[bufferIdx].DATA.B[1] = (data >> 8) & 0xFF;
    } else {
      CAN_0.BUF[bufferIdx].DATA.B[0] = data;
      CAN_0.BUF[bufferIdx].DATA.B[1] = 0;
    }
  }

  else if (dataLength == 1) {
    CAN_0.BUF[bufferIdx].DATA.B[0] = data;
  }
}

void canSendRPMValue(void) {
  int rpm = getRPM();
  can_send(8, ID_RPM_MSG, rpm, 2);
}

void canSendLightStates(void) {
  int lightState = getLightState();
  can_send(9, ID_LIGHT_STATES_MSG, lightState, 1);
}

void canSendECU1Status(void) {^
  if (ecu1State.ecu2Status == ABSENT) can_send(10, ID_ECU1_ERROR_MSG, 0, 0);

  can_send(10, ID_ECU1_ALIVE_MSG, 0, 0);
}

void can_receive() {
	if(CAN_0.IFRL.B.BUF5I == 1)
	{
		int data = CAN_0.BUF[0].DATA.B[0];

		switch(CAN_0.BUF[0].ID.B.STD_ID)
		{
			case ID_ECU2_INDICATOR_SWITCH:
				ecu1State.indicatorStates = data & 0x7;
				break;

			case ID_ECU3_HEADLIGHT_SWITCH:
				ecu1State.headlightStates = data & 0x7;
				break;

			case ID_ECU2_ALIVE_MSG:
				ecu1State.ecu2Status = ALIVE;
				P = 0;
				U1=0;
				break;

			case ID_ECU2_ERROR_MSG:
				ecu1State.ecu2Status = ABSENT;
				break;

			case 0x83:
				//ecu1State.indicatorStates = (CAN_0.BUF[0].DATA.B[1] | CAN_0.BUF[0].DATA.B[2]<<1) & 0x7;
				break;

			case 0x84:
				data = CAN_0.BUF[0].DATA.B[2];
				ecu1State.headlightStates = data & 0x7;
				break;

			default :
				break;
		}
	}
	//CAN_0.IFRL.B.BUF5I = 1;
}










/********************************************************************
 *                   Interrupt Handlers for PIT Channel 1-3         *
 ********************************************************************/
void Pit_Channel_1()
{
	indicateECU2Status();
	 canSendECU1Status();
PIT.CHANNEL[1].TFLG.R = 1;
}

void Pit_Channel_2()
{
	canSendRPMValue();
PIT.CHANNEL[2].TFLG.R = 1;
}

void Pit_Channel_3()
{
	canSendLightStates();
PIT.CHANNEL[3].TFLG.R = 1;
}


















/*************************************************************************
*                    	DONT CHANGE ANYTHING BELOW 	!!!                  *
*                                                                        *
**************************************************************************/

/*************************************************************************
*                   Interrupt Handlers for CAN Message Buffer            *
*                 Receive Interrupt for buffer 08-15 flag cleared        *
**************************************************************************/
IRQ_HANDLER(SPC5_FLEXCAN0_BUF_08_11_HANDLER) {
	CAN_0.IFRL.B.BUF8I  = 1;
	CAN_0.IFRL.B.BUF9I  = 1;
	CAN_0.IFRL.B.BUF10I = 1;
	CAN_0.IFRL.B.BUF11I = 1;
}
IRQ_HANDLER(SPC5_FLEXCAN0_BUF_12_15_HANDLER) {
	CAN_0.IFRL.B.BUF12I = 1;
	CAN_0.IFRL.B.BUF13I = 1;
	CAN_0.IFRL.B.BUF14I = 1;
	CAN_0.IFRL.B.BUF15I = 1;
}

/*************************************************************************
*                  Function to receive the data of the display           *
**************************************************************************/
void updateInputs()
{
	SW1 = CAN_0.BUF[0].DATA.B[0];
	SW2 = CAN_0.BUF[0].DATA.B[1];
	SW3 = CAN_0.BUF[0].DATA.B[2];
	SW4 = CAN_0.BUF[0].DATA.B[3];
	BT5 = CAN_0.BUF[0].DATA.B[4];
	BT6 = CAN_0.BUF[0].DATA.B[5];

}







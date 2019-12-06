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

void toggleDoorControlLED() {
	if (ecu1State.ecu2Status == ABSENT) P = ~P;
	// TODO: clear the interrupt
}

/* CAN FUNCTIONS */
void canSendRPMValue() {
	int rpm = getRPM();
	// send rpm
}

void canSendLightStates() {
	int lightState = ecu1State.indicatorStates | (ecu1State.headlightStates << 3);
	if (isAutomaticMode() && getLightIntensity() < 512) {
  		turnOnLowbeamAndParkingLight();
  	}
	// send light state
}

void canOnReceive() {
	int id = 999999; // TODO: find out from received msg
	int data = 99999; // TODO: find out from received msg first byte

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



/* MAIN */
int main(void) {
  for ( ; ; ) {
  	adjustMode();
  	
  }
}


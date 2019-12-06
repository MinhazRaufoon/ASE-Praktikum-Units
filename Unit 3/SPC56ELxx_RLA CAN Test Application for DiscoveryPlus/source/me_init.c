#include "me_init.h"


extern void CANMsgBufInit(void);



void ME_Init(){

	/* Initialization of all the imported components in the order specified in
	 the application wizard. The function is generated automatically.*/
  componentsInit();

  /* Enable Interrupts */
  irqIsrEnable();

  /* Pit Init */
  PIT_Init();
  /*SIu Init*/
  Siu_Init();
  /*Init ADC*/
  ADC0_Init();
  /*  Activates the CAN driver 1. */
  can_lld_start(&CAND1, &can_config_cfg0);
  CANMsgBufInit();


}

#include "adc.h"

/* ADC_0  module initialization for the potentiometer */
void ADC0_Init()
{
 /* ADC Peripheral Activation  */
 SPCSetPeripheralClockMode(32, SPC5_ME_PCTL_RUN(1) | SPC5_ME_PCTL_LP(2));
 /*Disable power down mode */
 ADC0.MCR.B.PWDN = 0;
 /* Scan Mode */
 ADC0.MCR.B.MODE = 1;
 /* Overwrite Enable */
 ADC0.MCR.B.OWREN = 1;
 /* Channel 5 used for input from potentiometer */
 ADC0.NCMR[0].B.CH5 = 1;
 /* Start conversion */
 ADC0.MCR.B.NSTART = 1;
}


/* ADC_1  module initialization for the light sensor  */


void ADC1_Init()
{
/* ADC Peripheral Activation  */
 SPCSetPeripheralClockMode(33, SPC5_ME_PCTL_RUN(1) | SPC5_ME_PCTL_LP(2));
 /*Disable power down mode */
 ADC1.MCR.B.PWDN = 0;
 /* Scan Mode */
 ADC1.MCR.B.MODE = 1;
 /* Overwrite Enable */
 ADC1.MCR.B.OWREN = 1;
 /* Channel 3 used for input from light sensor */
 ADC1.NCMR[0].B.CH3 = 1;
 /* Start conversion */
 ADC1.MCR.B.NSTART = 1;

}




/* TESTING PURPOUSE FUNCTION */
void showData(int value)
{
  //Catch the value of the light sensor that is saved on the right side register
  if(value <= 256)
  {
    /* LED0 - on, LED1 - off, LED2 - off, LED3 - off */

    SIU.GPDO[37].R = 1;
    SIU.GPDO[6].R = 0;
    SIU.GPDO[39].R = 0;
    SIU.GPDO[9].R = 0;

  }
  else if(value > 256 && value <= 512)
  {
    /* LED0 - on, LED1 - on, LED2 - off, LED3 - off */

	    SIU.GPDO[37].R = 1;
	    SIU.GPDO[6].R = 1;
	    SIU.GPDO[39].R = 0;
	    SIU.GPDO[9].R = 0;

  }
  else if(value > 512 && value <= 768)
    {
      /* LED0 - on, LED1 - on, LED2 - off, LED3 - off */

	    SIU.GPDO[37].R = 1;
	    SIU.GPDO[6].R = 1;
	    SIU.GPDO[39].R = 1;
	    SIU.GPDO[9].R = 0;

    }
  else
  {
    /* LED0 - on, LED1 - on, LED2 - on, LED3 - on */

	    SIU.GPDO[37].R = 1;
	    SIU.GPDO[6].R = 1;
	    SIU.GPDO[39].R = 1;
	    SIU.GPDO[9].R = 1;

  }
}






//void updateInputs(void);
//void testing(void);
//
//int SW1 = 0;
//int SW2 = 0;
//int SW3 = 0;
//int SW4= 0;
//int BT5= 0;
//int BT6= 0;



//void updateInputs()
//{
//	SW1 = CAN_0.BUF[0].DATA.B[0];
//	SW2 = CAN_0.BUF[0].DATA.B[1];
//	SW3 = CAN_0.BUF[0].DATA.B[2];
//	SW4 = CAN_0.BUF[0].DATA.B[3];
//	BT5 = CAN_0.BUF[0].DATA.B[4];
//	BT6 = CAN_0.BUF[0].DATA.B[5];
//
//}
//
//
//
//
//void testing (void)
//{
//	U1 = SW1;
//	U2 = SW2;
//	U3 = SW3;
//	P = SW4;
//	Tx = BT5;
//	Rx = BT6;
//
//	}




















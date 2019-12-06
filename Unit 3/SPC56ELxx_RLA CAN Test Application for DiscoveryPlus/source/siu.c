#include "siu.h"



void Siu_Init() {
/***************************************************************************
*                           LED Configuration 		                       *
***************************************************************************/

	SIU.PCR[45].R = 0x0200;      /* LED 0 */ 
	SIU.PCR[46].R = 0x0200;     /*  LED 1 */ 
	SIU.PCR[47].R = 0x0200;     /*  LED 2 */ 

    /* Plate configuration LED */
	SIU.PCR[6].R  = 0x0200; 
	SIU.PCR[7].R = 0x0200;  
	SIU.PCR[8].R = 0x0200;  
	SIU.PCR[37].R = 0x0200;  
	SIU.PCR[9].R = 0x0200; 
	SIU.PCR[36].R = 0x0200;


	

/***************************************************************************
*                       Analog inputs configuration                        *
***************************************************************************/

	/* Analog inputs */
	SIU.PCR[32].R = 0x2500;       /* LDR */
	SIU.PCR[66].R = 0x2500;       /* Potentiometer */
	
	
/********************************************************************
*                     CAN pin configuration                         *
********************************************************************/
	   /* Setup FlexCAN 1 pins */
	   /* TX */
//SIU.PCR[].B.PA  = ;
//SIU.PCR[].B.OBE = ;
//SIU.PCR[].B.IBE = ;

		/* RX */
//SIU.PCR[].B.PA = ;
//SIU.PCR[].B.OBE = ;
//SIU.PCR[].B.IBE = ;

	SIU.PCR[16].B.PA = 1;
	SIU.PCR[16].B.OBE = 1;
	SIU.PCR[16].B.IBE = 0;

	SIU.PCR[17].B.PA = 1;
	SIU.PCR[17].B.OBE = 0;
	SIU.PCR[17].B.IBE = 1;

    SIU.PSMI[0].B.PADSEL = 0x1;
    SIU.PSMI[33].B.PADSEL = 0x1;
}




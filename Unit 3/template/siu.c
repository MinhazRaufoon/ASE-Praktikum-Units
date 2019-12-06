#include "siu.h"

void peripheral_Init()
{
	SIU.PCR[45].R = 0x0200;      /* LED 0 */ 
	SIU.PCR[46].R = 0x0200;     /*  LED 1 */ 
	SIU.PCR[47].R = 0x0200;     /*  LED 2 */ 

    /* Plate configuration LED */
	SIU.PCR[37].R  = 0x0200; /* LED U1 */ 
	SIU.PCR[39].R = 0x0200;  /* LED U2 */ 
	SIU.PCR[36].R = 0x0200;  /* LED U3 */ 
	SIU.PCR[38].R = 0x0200;  /* LED P */ 
	SIU.PCR[9].R = 0x0200;   /* LED Tx */ 
	SIU.PCR[42].R = 0x0200;  /* LED Rx */ 

	/* Analog inputs */
	SIU.PCR[32].R = 0x2500;       /* LDR */
	SIU.PCR[66].R = 0x2500;       /* Potentiometer */


    SIU.PSMI[0].B.PADSEL = 0x1;    /* Can0 Padselect */ 
    SIU.PSMI[33].B.PADSEL = 0x1;   /* Can0 Padselect */ 
}

void Siu_Init() {
peripheral_Init();
/***************************************************************************
*                                  Task 2                                 *
*                            Can PIn Configuration                        *
***************************************************************************/
/*************************************************************************
*                     CAN pin configuration                              *
*                    _____  ___  ___   ___                               *
*                   |_   _|/ _ \|   \ / _ \                              *
*                     | | | (_) | |) | (_) |                             *
*                     |_|  \___/|___/ \___/                              *
*                                                                        *
**************************************************************************/
/*
SIU.PCR[].B.PA = ;
SIU.PCR[].B.IBE = ;
SIU.PCR[].B.OBE = ;

SIU.PCR[].B.PA = ;
SIU.PCR[].B.IBE = ;
SIU.PCR[].B.OBE = ;
 */


}

#include "components.h"
#include "can_lld_cfg.h"
#include "me_init.h"
#include "can.h"





void CANMsgBufInit(void)
{

/********************************************************************
*               CAN message buffer configuration                   *
*                    _____  ___  ___   ___                         *
*                   |_   _|/ _ \|   \ / _ \                        *
*                     | | | (_) | |) | (_) |                       *
*                     |_|  \___/|___/ \___/                        *
*                                                                  *
********************************************************************/
/* MB Code */
//CAN_0.BUF[].CS.B.CODE = ;
/* Standard format */
//CAN_0.BUF[].MSG_CS.B.IDE = ;
/* SRR */
//	CAN_0.BUF[].MSG_CS.B.SRR = ;
/* Data Frame */
//CAN_0.BUF[].MSG_CS.B.RTR = ;
/* Data Length */
//CAN_0.BUF[].CS.B.LENGTH = ;
/* STD_ID */
//CAN_0.BUF[].MSG_ID.B.STD_ID = ;

//CAN_0.RXFIFO.IDTABLE[0].R = 0; //0x08000000
//CAN_0.RXIMR[0].R = 0; //0x1fcfffff

	// using buffer 8
	CAN_0.BUF[8].CS.B.CODE = 0b1000;
	CAN_0.BUF[8].MSG_CS.B.IDE = 0;
	CAN_0.BUF[8].MSG_CS.B.SRR = 0;
	CAN_0.BUF[8].CS.B.LENGTH = 2;
	CAN_0.BUF[8].MSG_ID.B.STD_ID = 75;
	CAN_0.BUF[8].MSG_CS.B.RTR = 0;


}



/********************************************************************
 *                   Don't touch anything below!                    *
 ********************************************************************/

void cfg0_errorcb(CANDriver *canp, uint32_t esr,uint8_t rx_err_counter, uint8_t tx_err_counter){
  /* Put error management code Here */
  (void)canp;
  (void)esr;
  (void)rx_err_counter;
  (void)tx_err_counter;
}

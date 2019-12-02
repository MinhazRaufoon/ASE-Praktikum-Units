#include "components.h"
#include "can_lld_cfg.h"
#include "me_init.h"
#include "can.h"




/********************************************************************
 *                           TASK 2                                 *
 ********************************************************************/
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
int i;
for (i = 8; i < 12; i++) {
	CAN_0.BUF[i].CS.B.CODE = 0x8;
	CAN_0.BUF[i].MSG_CS.B.IDE = 0;
	CAN_0.BUF[i].MSG_CS.B.SRR = 0;
	CAN_0.BUF[i].CS.B.LENGTH = 0x2;
	CAN_0.BUF[i].MSG_ID.B.STD_ID = 103; // check the current PC's IP address
	CAN_0.BUF[i].MSG_CS.B.RTR = 0;
}
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
}




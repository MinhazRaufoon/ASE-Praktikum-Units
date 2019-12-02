#include "pit.h"

/* Configure the timer channels with a specific frequency */
void PIT_ConfigureTimer(uint8_t channel,uint32_t frequency)
{
uint32_t reg;
/* PIT frequency (PIT uses the Peripheral set 0 clock = SYS_CLK / SYSCLK_DIVIDER. */
//reg = SPCGetSystemClock() / (frequency) - 1U;
reg = 60000 * frequency;
/* Define the timer load value */
PIT.CHANNEL[channel].LDVAL.R = reg;
/* Define the timer current value  */
PIT.CHANNEL[channel].CVAL.R = reg;
/* Interrupt timer flag cleared */
PIT.CHANNEL[channel].TFLG.R = 1U;
}


/* Enable timer */
void PIT_StartTimer(uint8_t channel)
{
 PIT.CHANNEL[channel].TCTRL.R = 3U;
}

/* Disable timer */
void PIT_StopTimer(uint8_t channel)
{
 PIT.CHANNEL[channel].TCTRL.R = 0U;
}


/* Initialize the timer module */
void PIT_Init(void)
{
  /* Switch on PIT module */
//  PIT.PITMCR.B.MDIS = 0;
	PIT.PITMCR.B.MDIS = 0;
  /* PIT clock enabled. */

  /* Pit Clock enabled */
//   PIT.PITMCR.R = 1;
	PIT.PITMCR.R = 1;
  /* Run timer for debug mode */
 // PIT.PITMCR.B.FRZ = 0;
	PIT.PITMCR.B.FRZ = 0;
  /* Initialize Timmers */
	PIT_ConfigureTimer(1, 200);
	PIT_StartTimer(1);
}

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





























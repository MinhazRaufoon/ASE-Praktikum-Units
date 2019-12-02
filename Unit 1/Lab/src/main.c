#include "init.h"


int LED0_PCR = 9;
int LED1_PCR = 42;
int LED2_PCR = 13;
int LED3_PCR = 12;
int LED4_PCR = 62;
int LED5_PCR = 61;
int LED6_PCR = 59;
int LED7_PCR = 11;

int BT5_PCR = 1;
int BT6_PCR = 0;
int SW1_PCR = 44;
    

void showData(int value);
void showData_2_1(int value);
void showData_2_3(int value);
int get_light_sensor_value();
int get_potentiometer_value();
void led_on(int pcr);
void led_off(int pcr);
void turn_off_all_leds();

void task_2_1();
void task_2_2();
void task_2_3();
void task_3_1();
void task_3_2();
void task_4();

/********************************************************************
 *                              main                                *
 ********************************************************************/

void main(void)
{
    /* board initialization */
    Init();


    /* forever */
    for(;;)
    {
        task_2_2();
        //task_2_3();
        task_3_1();
        task_3_2();
/********************************************************************
 *                           Main Loop                              *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                  Write down your logic here.                     *
 ********************************************************************/  
    }
}

int get_light_sensor_value() {
    return (int) ADC_0.CDR[2].B.CDATA;
}

int get_potentiometer_value() {
    return (int) ADC_0.CDR[4].B.CDATA;
}

void task_2_1() {
    int light = get_light_sensor_value();
    showData_2_1(light);
}

void task_2_2() {
    int pot = get_potentiometer_value();
    showData_2_1(pot);
}

void task_2_3() {
    int light = get_light_sensor_value();
    showData_2_3(light);
}

void led_on(int pcr) {
    SIU.GPDO[pcr].R = 0;
}
void led_off(int pcr) {
    SIU.GPDO[pcr].R = 1;
}


void showData(int value)
{
/********************************************************************
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 ********************************************************************/  
void showData_2_1(int value) {
    if(value <= 256)
      {   
        /* LED0 - on, LED1 - off, LED2 - off, LED3 - off */
          led_on(LED0_PCR);
          led_off(LED1_PCR);
          led_off(LED2_PCR);
          led_off(LED3_PCR);
      }
      else if(value > 256 && value <= 512)
      {  
        /* LED0 - on, LED1 - on, LED2 - off, LED3 - off */
            led_on(LED0_PCR);
          led_on(LED1_PCR);
          led_off(LED2_PCR);
          led_off(LED3_PCR);
      }
      else if(value > 512 && value <= 768)
      {  
        /* LED0 - on, LED1 - on, LED2 - on, LED3 - off */
      led_on(LED0_PCR);
          led_on(LED1_PCR);
          led_on(LED2_PCR);
          led_off(LED3_PCR);
      }    
      else
      {  
        /* LED0 - on, LED1 - on, LED2 - on, LED3 - on */
        led_on(LED0_PCR);
          led_on(LED1_PCR);
          led_on(LED2_PCR);
          led_on(LED3_PCR);
      } 
}

void showData_2_3(int value) {
    if(value <= 205)
      {   
        /* LED0 - on, LED1 - on, LED2 - on, LED3 - on */
        led_on(LED0_PCR);
          led_on(LED1_PCR);
          led_on(LED2_PCR);
          led_on(LED3_PCR);
      led_on(LED4_PCR);
      }
    else if(value > 205 && value <= 410)
      {   
        /* LED0 - on, LED1 - on, LED2 - on, LED3 - on */
        led_on(LED0_PCR);
          led_on(LED1_PCR);
          led_on(LED2_PCR);
          led_on(LED3_PCR);
      led_off(LED4_PCR);
      }
      else if(value > 410 && value <= 615)
      {  
        /* LED0 - on, LED1 - on, LED2 - on, LED3 - off */
      led_on(LED0_PCR);
          led_on(LED1_PCR);
          led_on(LED2_PCR);
          led_off(LED3_PCR);
      led_off(LED4_PCR);
      }
      else if(value > 615 && value <= 820)
      {  
        
      /* LED0 - on, LED1 - on, LED2 - off, LED3 - off */
            led_on(LED0_PCR);
          led_on(LED1_PCR);
          led_off(LED2_PCR);
          led_off(LED3_PCR);
      led_off(LED4_PCR);
      }    
      else
      {  
        
      /* LED0 - on, LED1 - off, LED2 - off, LED3 - off */
          led_on(LED0_PCR);
          led_off(LED1_PCR);
          led_off(LED2_PCR);
          led_off(LED3_PCR);
      led_off(LED4_PCR);
      } 
}

void task_3_1() {
    int b5 = SIU.GPDI[BT5_PCR].R;
    int b6 = SIU.GPDI[BT6_PCR].R;
    if (b5 == 0) {
        led_on(LED5_PCR);
    }
    else {
        led_off(LED5_PCR);
    }

    if (b6 != 0) {
        led_on(LED6_PCR);
    }
    else {
        led_off(LED6_PCR);
    }
}



/********************************************************************
 *                      Interrupt Functions                         *
 *                    _____  ___  ___   ___                         *
 *                   |_   _|/ _ \|   \ / _ \                        *
 *                     | | | (_) | |) | (_) |                       *
 *                     |_|  \___/|___/ \___/                        *
 *                                                                  *
 *                Interrupts can be handled below.                  *
 ********************************************************************/  

void toggle_led(int pcr) {
    int v = SIU.GPDO[pcr].R;
    if (!v) SIU.GPDO[pcr].R = 1;
    else SIU.GPDO[pcr].R = 0;
}

void PITCHANNEL0() {
    /* clear flag */
    PIT.CH[0].TFLG.B.TIF = 1;
    
    toggle_led(LED7_PCR);
}

void PITCHANNEL1() {
    /* clear flag */
    PIT.CH[1].TFLG.B.TIF = 1;
    // task_4();
}

void task_3_2() {
    int swt = SIU.GPDI[SW1_PCR].R;

    if (!swt) {
        PIT_ConfigureTimer(0, 1000);
        PIT_StartTimer(0);
    }
    else {
        led_off(LED7_PCR);
        PIT_StopTimer(0);
    }
}

int light = 0;
void task_4(){
    if (light == 0) {
        led_on(LED0_PCR);
    } else if (light == 1) {
        led_off(LED0_PCR);
        led_on(LED1_PCR);
    } else if (light == 2) {
        led_off(LED1_PCR);
        led_on(LED2_PCR);
    } else if (light == 3) {
        led_off(LED2_PCR);
        led_on(LED3_PCR);
    } else if (light == 4) {
        led_off(LED3_PCR);
        led_on(LED4_PCR);
    } else if (light == 5) {
        led_off(LED4_PCR);
        led_on(LED5_PCR);
    } else if (light == 6) {
        led_off(LED5_PCR);
        led_on(LED6_PCR);
    } else if (light == 7) {
        led_off(LED6_PCR);
        led_on(LED7_PCR);
    } else if (light == 8) turn_off_all_leds();
    light++;
}
void turn_off_all_leds() {
    led_off(LED0_PCR);
    led_off(LED1_PCR);
    led_off(LED2_PCR);
    led_off(LED3_PCR);
    led_off(LED4_PCR);
    led_off(LED5_PCR);
    led_off(LED6_PCR);
    led_off(LED7_PCR);
}
/********************************************************************
 *                   Interrupt Vector Table                         *
 *                                                                  *
 *                 Don't touch anything below!                      *
 ********************************************************************/
#pragma interrupt Ext_Isr
#pragma section IrqSect RX address=0x040
#pragma use_section IrqSect Ext_Isr

void Ext_Isr() {
    switch(INTC.IACKR.B.INTVEC)
    {
        case 59:
            /* Timer Interrupt */
            PITCHANNEL0();
            break;
        case 60:
            /* Timer Interrupt */
            PITCHANNEL1();
            break;            
        default:
            break;
    }
    /* End of Interrupt Request */
    INTC.EOIR.R = 0x00000000;
}

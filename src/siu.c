#include "jdp.h"

int LED0_PCR = 9;
int LED1_PCR = 42;
int LED2_PCR = 13;
int LED3_PCR = 12;
int LED4_PCR = 62;
int LED5_PCR = 61;
int LED6_PCR = 59;
int LED7_PCR = 11;

void led_off(int pcr);
void init_task1();
void init_task_2_1();
void init_task_2_2();
void init_task_2_3();
void init_task_3_1();
void init_task_3_2();
void init_task_4();
void turn_off_all_leds();

void SIU_Init(void) {
  /***************************************************************************
   *                                  Task 1                                 *
   *    Please enter the PCR register numbers and initialitation code here   *
   ***************************************************************************/
  /* LEDs */
  /* SIU.PCR[].R = ; */   /* LED0 */
  /* SIU.PCR[].R = ; */   /* LED1 */
  /* ... */
   init_task1();
  /***************************************************************************
   *                                  Task 2                                 *
   *                       Analog inputs configuration                       *
   ***************************************************************************/  
  /* SIU.PCR[].R = ; */
  /* ... */

    init_task_2_1();
    init_task_2_2();
    init_task_2_3();

  /***************************************************************************
   *                                  Task 3                                 *
   *                            Buttons & switches                           *
   ***************************************************************************/    
  /* SIU.PCR[].R = ; */   /* BT5 */
  /* ... */
    init_task_3_1();
    init_task_3_2();
    // init_task_4();
}

void led_off(int pcr) {
    SIU.GPDO[pcr].R = 1;
}

void init_task1() {
    int i = 0;
    int pcr_idx[8] = {11, 59, 61, 62, 12, 13, 42, 9};
    for (i=0; i<8; i++) {
        SIU.PCR[pcr_idx[i]].R = 0x0200;
        // SIU.GPDO[i].R = 0;
    }
 
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

void init_task_2_1() {
    SIU.PCR[33].R = 0x2500;
    turn_off_all_leds();
}

void init_task_2_2() {
    SIU.PCR[65].R = 0x2500;
    turn_off_all_leds();
}

void init_task_2_3() {
    SIU.PCR[33].R = 0x2500;
    turn_off_all_leds();
}

void init_task_3_1() {
    int BT5_PCR = 1;
    int BT6_PCR = 0;
    
    SIU.PCR[BT5_PCR].R = 0x0100; 
    SIU.PCR[BT6_PCR].R = 0x0100; 
}
void init_task_3_2() {
    int SW1_PCR = 44;
    SIU.PCR[SW1_PCR].R = 0x0100;
    turn_off_all_leds();
}

void init_task_4(){
    turn_off_all_leds();
PIT_ConfigureTimer(1, 1000);
        PIT_StartTimer(1);
}
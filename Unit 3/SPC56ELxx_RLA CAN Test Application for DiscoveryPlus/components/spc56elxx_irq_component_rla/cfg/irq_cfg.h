#ifndef _IRQ_CFG_H_
#define _IRQ_CFG_H_


#if !defined(FALSE) || defined(__DOXYGEN__)
#define FALSE                       0U
#endif

#if !defined(TRUE) || defined(__DOXYGEN__)
#define TRUE                        1U
#endif


/********************************************************************
 *                           TASK 1                                 *
 *                                                                  *
 ********************************************************************/


// #define <vectorxx>	<function_Name>
#define vector60 channel1_ISR
#define vector61 channel2_ISR
#define vector127 channel3_ISR



#if !defined(_FROM_ASM_)
#ifdef __cplusplus
extern "C" {
#endif
/************************************************************************************
 *                                         TASK 1                                   *
 *                 Define the PIT interrupt processing function prototype           *
 ***********************************************************************************/

// void <function_Name>(void);   this function is now an external function and can defined in main
void channel1_ISR(void);
void channel2_ISR(void);
void channel3_ISR(void);


  void irq_cfg_init(void);


#ifdef __cplusplus
}
#endif
#endif /* !defined(_FROM_ASM_) */

#endif /* _IRQ_CFG_H_ */

/** @} */

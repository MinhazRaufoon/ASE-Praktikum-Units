/*
    SPC5 RLA - Copyright (C) 2019 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License").
    You may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Copyright (C) 2008 Freescale & STMicroelectronics - The driver registers
    structure (lines 51-472) is derived by the core header file defining the
    whole core register set.
*/

/**
 * @file    spc5_fccu.h
 * @brief   FCCU helper driver header.
 *
 * @addtogroup FCCU
 * @{
 */

#ifndef _SPC5_FCCU_H_
#define _SPC5_FCCU_H_

/*===========================================================================*/
/* Driver constants.                                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Driver pre-compile time settings.                                         */
/*===========================================================================*/

/*===========================================================================*/
/* Derived constants and error checks.                                       */
/*===========================================================================*/

/*===========================================================================*/
/* Driver data structures and types.                                         */
/*===========================================================================*/

/* PPC register definitions not compatible with MISRA rules on bit-fields 
 (Rules 6.1). */
/*lint -e46 */
struct spc5_fccu {

  union {   /* FCCU Control Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_1:23;
      vuint32_t  NVML:1;            /* NVM configuration loaded */
      vuint32_t  OPS:2;             /* Operation status */
      vuint32_t  unused_0:1;
      vuint32_t  OPR:5;             /* Operation run */
    } B;
  } CTRL;

  union {   /* FCCU CTRL Key Register */
    vuint32_t R;
    struct {
      vuint32_t CTRLK:32;
    } B;
  } CTRLK;

  union {   /* FCCU Configuration Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_1:10;
      vuint32_t  RCCE1:1;           /* RCC1 enable */
      vuint32_t  RCCE0:1;           /* RCC0 enable */
      vuint32_t  SMRT:4;            /* Safe Mode Request Timer */
      vuint32_t  unused_0:4;
      vuint32_t  CM:1;              /* Config mode */
      vuint32_t  SM:1;              /* Switching mode */
      vuint32_t  PS:1;              /* Polarity Selection */
      vuint32_t  FOM:3;             /* Fault Output Mode Selection */
      vuint32_t  FOP:6;             /* Fault Output Prescaler */
    } B;
  } CFG;

  union {   /* FCCU CF Configuration Register 0-3 */
    vuint32_t R;
    struct {
      vuint32_t CFC31:1;
      vuint32_t CFC30:1;
      vuint32_t CFC29:1;
      vuint32_t CFC28:1;
      vuint32_t CFC27:1;
      vuint32_t CFC26:1;
      vuint32_t CFC25:1;
      vuint32_t CFC24:1;
      vuint32_t CFC23:1;
      vuint32_t CFC22:1;
      vuint32_t CFC21:1;
      vuint32_t CFC20:1;
      vuint32_t CFC19:1;
      vuint32_t CFC18:1;
      vuint32_t CFC17:1;
      vuint32_t CFC16:1;
      vuint32_t CFC15:1;
      vuint32_t CFC14:1;
      vuint32_t CFC13:1;
      vuint32_t CFC12:1;
      vuint32_t CFC11:1;
      vuint32_t CFC10:1;
      vuint32_t CFC9:1;
      vuint32_t CFC8:1;
      vuint32_t CFC7:1;
      vuint32_t CFC6:1;
      vuint32_t CFC5:1;
      vuint32_t CFC4:1;
      vuint32_t CFC3:1;
      vuint32_t CFC2:1;
      vuint32_t CFC1:1;
      vuint32_t CFC0:1;
    } B;
  } CF_CFG[4];

  union {   /* FCCU NCF Configuration Register 0-3 */
    vuint32_t R;
    struct {
      vuint32_t NCFC31:1;
      vuint32_t NCFC30:1;
      vuint32_t NCFC29:1;
      vuint32_t NCFC28:1;
      vuint32_t NCFC27:1;
      vuint32_t NCFC26:1;
      vuint32_t NCFC25:1;
      vuint32_t NCFC24:1;
      vuint32_t NCFC23:1;
      vuint32_t NCFC22:1;
      vuint32_t NCFC21:1;
      vuint32_t NCFC20:1;
      vuint32_t NCFC19:1;
      vuint32_t NCFC18:1;
      vuint32_t NCFC17:1;
      vuint32_t NCFC16:1;
      vuint32_t NCFC15:1;
      vuint32_t NCFC14:1;
      vuint32_t NCFC13:1;
      vuint32_t NCFC12:1;
      vuint32_t NCFC11:1;
      vuint32_t NCFC10:1;
      vuint32_t NCFC9:1;
      vuint32_t NCFC8:1;
      vuint32_t NCFC7:1;
      vuint32_t NCFC6:1;
      vuint32_t NCFC5:1;
      vuint32_t NCFC4:1;
      vuint32_t NCFC3:1;
      vuint32_t NCFC2:1;
      vuint32_t NCFC1:1;
      vuint32_t NCFC0:1;
    } B;
  } NCF_CFG[4];

  union {   /* FCCU CFS Configuration Register 0-7 */
    vuint32_t R;
    struct {
      vuint32_t CFSC15:2;
      vuint32_t CFSC14:2;
      vuint32_t CFSC13:2;
      vuint32_t CFSC12:2;
      vuint32_t CFSC11:2;
      vuint32_t CFSC10:2;
      vuint32_t CFSC9:2;
      vuint32_t CFSC8:2;
      vuint32_t CFSC7:2;
      vuint32_t CFSC6:2;
      vuint32_t CFSC5:2;
      vuint32_t CFSC4:2;
      vuint32_t CFSC3:2;
      vuint32_t CFSC2:2;
      vuint32_t CFSC1:2;
      vuint32_t CFSC0:2;
    } B;
  } CFS_CFG[8];

  union {   /* FCCU NCFS Configuration Register 0-7 */
    vuint32_t R;
    struct {
      vuint32_t NCFSC15:2;
      vuint32_t NCFSC14:2;
      vuint32_t NCFSC13:2;
      vuint32_t NCFSC12:2;
      vuint32_t NCFSC11:2;
      vuint32_t NCFSC10:2;
      vuint32_t NCFSC9:2;
      vuint32_t NCFSC8:2;
      vuint32_t NCFSC7:2;
      vuint32_t NCFSC6:2;
      vuint32_t NCFSC5:2;
      vuint32_t NCFSC4:2;
      vuint32_t NCFSC3:2;
      vuint32_t NCFSC2:2;
      vuint32_t NCFSC1:2;
      vuint32_t NCFSC0:2;
    } B;
  } NCFS_CFG[8];

  union {   /* FCCU CF Status Register 0-3 */
    vuint32_t R;
    struct {
      vuint32_t CFS31:1;
      vuint32_t CFS30:1;
      vuint32_t CFS29:1;
      vuint32_t CFS28:1;
      vuint32_t CFS27:1;
      vuint32_t CFS26:1;
      vuint32_t CFS25:1;
      vuint32_t CFS24:1;
      vuint32_t CFS23:1;
      vuint32_t CFS22:1;
      vuint32_t CFS21:1;
      vuint32_t CFS20:1;
      vuint32_t CFS19:1;
      vuint32_t CFS18:1;
      vuint32_t CFS17:1;
      vuint32_t CFS16:1;
      vuint32_t CFS15:1;
      vuint32_t CFS14:1;
      vuint32_t CFS13:1;
      vuint32_t CFS12:1;
      vuint32_t CFS11:1;
      vuint32_t CFS10:1;
      vuint32_t CFS9:1;
      vuint32_t CFS8:1;
      vuint32_t CFS7:1;
      vuint32_t CFS6:1;
      vuint32_t CFS5:1;
      vuint32_t CFS4:1;
      vuint32_t CFS3:1;
      vuint32_t CFS2:1;
      vuint32_t CFS1:1;
      vuint32_t CFS0:1;
    } B;
  } CFS[4];

  union {   /* FCCU CF Key Register */
    vuint32_t R;
  } CFK;

  union {   /* FCCU NCF Status Register 0-3 */
    vuint32_t R;
    struct {
      vuint32_t NCFS31:1;
      vuint32_t NCFS30:1;
      vuint32_t NCFS29:1;
      vuint32_t NCFS28:1;
      vuint32_t NCFS27:1;
      vuint32_t NCFS26:1;
      vuint32_t NCFS25:1;
      vuint32_t NCFS24:1;
      vuint32_t NCFS23:1;
      vuint32_t NCFS22:1;
      vuint32_t NCFS21:1;
      vuint32_t NCFS20:1;
      vuint32_t NCFS19:1;
      vuint32_t NCFS18:1;
      vuint32_t NCFS17:1;
      vuint32_t NCFS16:1;
      vuint32_t NCFS15:1;
      vuint32_t NCFS14:1;
      vuint32_t NCFS13:1;
      vuint32_t NCFS12:1;
      vuint32_t NCFS11:1;
      vuint32_t NCFS10:1;
      vuint32_t NCFS9:1;
      vuint32_t NCFS8:1;
      vuint32_t NCFS7:1;
      vuint32_t NCFS6:1;
      vuint32_t NCFS5:1;
      vuint32_t NCFS4:1;
      vuint32_t NCFS3:1;
      vuint32_t NCFS2:1;
      vuint32_t NCFS1:1;
      vuint32_t NCFS0:1;
    } B;
  } NCFS[4];

  union {   /* FCCU NCF Key Register */
    vuint32_t R;
  } NCFK;

  union {   /* FCCU NCF Enable Register 0-3 */
    vuint32_t R;
    struct {
      vuint32_t NCFE31:1;
      vuint32_t NCFE30:1;
      vuint32_t NCFE29:1;
      vuint32_t NCFE28:1;
      vuint32_t NCFE27:1;
      vuint32_t NCFE26:1;
      vuint32_t NCFE25:1;
      vuint32_t NCFE24:1;
      vuint32_t NCFE23:1;
      vuint32_t NCFE22:1;
      vuint32_t NCFE21:1;
      vuint32_t NCFE20:1;
      vuint32_t NCFE19:1;
      vuint32_t NCFE18:1;
      vuint32_t NCFE17:1;
      vuint32_t NCFE16:1;
      vuint32_t NCFE15:1;
      vuint32_t NCFE14:1;
      vuint32_t NCFE13:1;
      vuint32_t NCFE12:1;
      vuint32_t NCFE11:1;
      vuint32_t NCFE10:1;
      vuint32_t NCFE9:1;
      vuint32_t NCFE8:1;
      vuint32_t NCFE7:1;
      vuint32_t NCFE6:1;
      vuint32_t NCFE5:1;
      vuint32_t NCFE4:1;
      vuint32_t NCFE3:1;
      vuint32_t NCFE2:1;
      vuint32_t NCFE1:1;
      vuint32_t NCFE0:1;
    } B;
  } NCFE[4];

  union {   /* FCCU NCF Time-out Enable Register 0-3 */
    vuint32_t R;
    struct {
      vuint32_t NCFTOE31:1;
      vuint32_t NCFTOE30:1;
      vuint32_t NCFTOE29:1;
      vuint32_t NCFTOE28:1;
      vuint32_t NCFTOE27:1;
      vuint32_t NCFTOE26:1;
      vuint32_t NCFTOE25:1;
      vuint32_t NCFTOE24:1;
      vuint32_t NCFTOE23:1;
      vuint32_t NCFTOE22:1;
      vuint32_t NCFTOE21:1;
      vuint32_t NCFTOE20:1;
      vuint32_t NCFTOE19:1;
      vuint32_t NCFTOE18:1;
      vuint32_t NCFTOE17:1;
      vuint32_t NCFTOE16:1;
      vuint32_t NCFTOE15:1;
      vuint32_t NCFTOE14:1;
      vuint32_t NCFTOE13:1;
      vuint32_t NCFTOE12:1;
      vuint32_t NCFTOE11:1;
      vuint32_t NCFTOE10:1;
      vuint32_t NCFTOE9:1;
      vuint32_t NCFTOE8:1;
      vuint32_t NCFTOE7:1;
      vuint32_t NCFTOE6:1;
      vuint32_t NCFTOE5:1;
      vuint32_t NCFTOE4:1;
      vuint32_t NCFTOE3:1;
      vuint32_t NCFTOE2:1;
      vuint32_t NCFTOE1:1;
      vuint32_t NCFTOE0:1;
    } B;
  } NCF_TOE[4];

  union {   /* FCCU NCF Time-out Register */
    vuint32_t R;
  } NCF_TO;

  union {   /* FCCU CFG Timeout Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_0:29;
      vuint32_t  TO:3;              /* Configuration time-out */
    } B;
  } CFG_TO;

  union {   /* FCCU IO Control Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_1:26;
      vuint32_t  EIN1:1;            /* Error input 1 */
      vuint32_t  EIN0:1;            /* Error input 0 */
      vuint32_t  unused_0:2;
      vuint32_t  EOUT1:1;           /* Error out 1 */
      vuint32_t  EOUT0:1;           /* Error out 0 */
    } B;
  } EINOUT;

  union {   /* FCCU Status Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_0:29;
      vuint32_t  STATUS:3;          /* FCCU status */
    } B;
  } STAT;

  vuint32_t ADR_reserved1[4];

  union {   /* FCCU SC Freeze Status Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_0:30;
      vuint32_t  RCCS1:1;           /* RCC1 Status */
      vuint32_t  RCCS0:1;           /* RCC0 Status */
    } B;
  } SCFS;

  union {   /* FCCU CF Fake Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_0:25;
      vuint32_t  FCFC:7;            /* Fake critical fault code */
    } B;
  } CFF;
  
  union {   /* FCCU NCF Fake Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_0:25;
      vuint32_t  FNCFC:7;           /* Fake non-critical fault code */
    } B;
  } NCFF;

  union {   /* FCCU IRQ Status Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_0:29;
      vuint32_t  NMI_STAT:1;        /* NMI Interrupt Status */
      vuint32_t  ALRM_STAT:1;       /* Alarm Interrupt Status */
      vuint32_t  CFG_TO_STAT:1;     /* Configuration Time-out Status */
    } B;
  } IRQ_STAT;

  union {   /* FCCU IRQ Enable Register */
    vuint32_t R;
    struct {
      vuint32_t  unused_0:31;
      vuint32_t  CFG_TO_IEN:1;      /* Configuration Time-out Interrupt Enable */
    } B;
  } IRQ_EN;

  union {   /* FCCU XTMR Register */
    vuint32_t R;
    struct {
      vuint32_t  XTMR_XTMR:32;      /* Alarm/Watchdog/safe request timer */
    } B;
  } XTMR;

  union {   /* FCCU MCS Register */
    vuint32_t R;
    struct {
      vuint32_t  VL3:1;             /* Valid */
      vuint32_t  FS3:1;             /* Fault Status */
      vuint32_t  unused_3:2;
      vuint32_t  MCS3:4;            /* Magic Carpet oldest state */
      vuint32_t  VL2:1;             /* Valid */
      vuint32_t  FS2:1;             /* Fault Status */
      vuint32_t  unused_2:2;
      vuint32_t  MCS2:4;            /* Magic Carpet previous-previous state */
      vuint32_t  VL1:1;             /* Valid */
      vuint32_t  FS1:1;             /* Fault Status */
      vuint32_t  unused_1:2;
      vuint32_t  MCS1:4;            /* Magic Carpet previous state */
      vuint32_t  VL0:1;             /* Valid */
      vuint32_t  FS0:1;             /* Fault Status */
      vuint32_t  unused_0:2;
      vuint32_t  MCS0:4;            /* Magic Carpet latest state */
    } B;
  } MCS;
};
/*lint +e46 */

/*===========================================================================*/
/* Driver macros.                                                            */
/*===========================================================================*/

/*===========================================================================*/
/* External declarations.                                                    */
/*===========================================================================*/

/**
 * @name    FCCU unit reference
 * @{
 */
#define SPC5_FCCU       (*(struct spc5_fccu *)SPC5_FCCU_BASE)

/** @} */

#endif /* _SPC5_FCCU_H_ */

/** @} */

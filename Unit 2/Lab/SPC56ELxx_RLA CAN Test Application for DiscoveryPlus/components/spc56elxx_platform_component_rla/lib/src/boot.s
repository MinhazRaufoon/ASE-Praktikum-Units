/*
    SPC5 RLA - Copyright (C) 2015 STMicroelectronics

    Licensed under the Apache License, Version 2.0 (the "License").
    You may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    boot.s
 * @brief   SPC56ELxx boot-related code.
 *
 * @addtogroup PPC_BOOT
 * @{
 */

#include "boot.h"
#include "toolchain.h"

#if !defined(__DOXYGEN__)
       /* BAM record.*/
        .section    .boot, "axv"

        .long       0x015A0000
        .long       _reset_address

        /*
         * Reset entry point for core0.
         */
        .align      2
        .globl      _reset_address
        .type       _reset_address, @function
_VLE
_reset_address:
#if BOOT_PERFORM_CORE_INIT
        e_bl        _tlballoc
        e_bl        _ramclear
        e_bl        _regclear
        e_bl        _tlb0alloc
#endif /* BOOT_PERFORM_CORE_INIT */
        e_bl        _iv0init

#if BOOT_RELOCATE_IN_RAM
        /*
         * Image relocation in RAM.
         */
        e_lis       %r4, HI(__ram_reloc_start__)
        e_or2i      %r4, LO(__ram_reloc_start__)
        e_lis       %r5, HI(__ram_reloc_dest__)
        e_or2i      %r5, LO(__ram_reloc_dest__)
        e_lis       %r6, HI(__ram_reloc_end__)
        e_or2i      %r6, LO(__ram_reloc_end__)
.relloop:
        cmpl        cr0, %r4, %r6
        se_bge      .relend
        se_lwz      %r7, 0(%r4)
        se_addi     %r4, 4
        se_stw      %r7, 0(%r5)
        se_addi     %r5, 4
        se_b        .relloop
.relend:
        e_lis       %r3, HI(_boot_address)
        e_or2i      %r3, LO(_boot_address)
        mtctr       %r3
        se_bctrl
#else
        e_b         _boot_address
#endif /* BOOT_RELOCATE_IN_RAM */

#if (BOOT_CORE1 == 1)
        /*
         * Reset entry point for core1.
         */
        .align      2
        .globl      _reset_address1
        .type       _reset_address1, @function
_VLE
_reset_address1:
        e_bl        _tlballoc
        e_bl        _tlb0alloc
        e_bl        _iv1init

        e_lis       %r3, HI(_boot_address1)
        e_or2i      %r3, LO(_boot_address1)
        mtctr       %r3
        se_bctrl
#endif /* BOOT_CORE1 */

        .align      2
_ramcode:
        tlbwe
        se_isync
        se_blr

        /*
         * TLBs (except TLB0) invalidation and allocation.
         */
        .align      2
_tlballoc:
        /*
         * Invalidating all TLBs except TLB0.
         */
        e_lis       %r3, 0
        mtspr       625, %r3        /* MAS1 */
        mtspr       626, %r3        /* MAS2 */
        mtspr       627, %r3        /* MAS3 */
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(1))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(2))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(3))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(4))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(5))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(6))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(7))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(8))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(9))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(10))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(11))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(12))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(13))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(14))
        mtspr       624, %r3        /* MAS0 */
        tlbwe
        e_lis       %r3, HI(MAS0_TBLMAS_TBL | MAS0_ESEL(15))
        mtspr       624, %r3        /* MAS0 */
        tlbwe

        /*
         * TLB1 allocated to internal RAM (0x40000000).
         */
        e_lis       %r3, HI(TLB1_MAS0)
        mtspr       624, %r3        /* MAS0 */
        e_lis       %r3, HI(TLB1_MAS1)
        e_or2i      %r3, LO(TLB1_MAS1)
        mtspr       625, %r3        /* MAS1 */
        e_lis       %r3, HI(TLB1_MAS2)
        e_or2i      %r3, LO(TLB1_MAS2)
        mtspr       626, %r3        /* MAS2 */
        e_lis       %r3, HI(TLB1_MAS3)
        e_or2i      %r3, LO(TLB1_MAS3)
        mtspr       627, %r3        /* MAS3 */
        tlbwe

        /*
         * TLB2 allocated to internal Peripherals Bridge A.
         */
        e_lis       %r3, HI(TLB2_MAS0)
        mtspr       624, %r3        /* MAS0 */
        e_lis       %r3, HI(TLB2_MAS1)
        e_or2i      %r3, LO(TLB2_MAS1)
        mtspr       625, %r3        /* MAS1 */
        e_lis       %r3, HI(TLB2_MAS2)
        e_or2i      %r3, LO(TLB2_MAS2)
        mtspr       626, %r3        /* MAS2 */
        e_lis       %r3, HI(TLB2_MAS3)
        e_or2i      %r3, LO(TLB2_MAS3)
        mtspr       627, %r3        /* MAS3 */
        tlbwe

        /*
         * TLB3 allocated to internal Peripherals Bridge B.
         */
        e_lis       %r3, HI(TLB3_MAS0)
        mtspr       624, %r3        /* MAS0 */
        e_lis       %r3, HI(TLB3_MAS1)
        e_or2i      %r3, LO(TLB3_MAS1)
        mtspr       625, %r3        /* MAS1 */
        e_lis       %r3, HI(TLB3_MAS2)
        e_or2i      %r3, LO(TLB3_MAS2)
        mtspr       626, %r3        /* MAS2 */
        e_lis       %r3, HI(TLB3_MAS3)
        e_or2i      %r3, LO(TLB3_MAS3)
        mtspr       627, %r3        /* MAS3 */
        tlbwe

        /*
         * TLB4 allocated to on-platform peripherals.
         */
        e_lis       %r3, HI(TLB4_MAS0)
        mtspr       624, %r3        /* MAS0 */
        e_lis       %r3, HI(TLB4_MAS1)
        e_or2i      %r3, LO(TLB4_MAS1)
        mtspr       625, %r3        /* MAS1 */
        e_lis       %r3, HI(TLB4_MAS2)
        e_or2i      %r3, LO(TLB4_MAS2)
        mtspr       626, %r3        /* MAS2 */
        e_lis       %r3, HI(TLB4_MAS3)
        e_or2i      %r3, LO(TLB4_MAS3)
        mtspr       627, %r3        /* MAS3 */
        tlbwe

        /*
         * TLB5 allocated to on-platform peripherals.
         */
        e_lis       %r3, HI(TLB5_MAS0)
        mtspr       624, %r3        /* MAS0 */
        e_lis       %r3, HI(TLB5_MAS1)
        e_or2i      %r3, LO(TLB5_MAS1)
        mtspr       625, %r3        /* MAS1 */
        e_lis       %r3, HI(TLB5_MAS2)
        e_or2i      %r3, LO(TLB5_MAS2)
        mtspr       626, %r3        /* MAS2 */
        e_lis       %r3, HI(TLB5_MAS3)
        e_or2i      %r3, LO(TLB5_MAS3)
        mtspr       627, %r3        /* MAS3 */
        tlbwe

#if (BOOT_CORE1 == 1)
        /*
         * TLB6 allocated to internal RAM (0x50000000).
         */
        e_lis       %r3, HI(TLB6_MAS0)
        mtspr       624, %r3        /* MAS0 */
        e_lis       %r3, HI(TLB6_MAS1)
        e_or2i      %r3, LO(TLB6_MAS1)
        mtspr       625, %r3        /* MAS1 */
        e_lis       %r3, HI(TLB6_MAS2)
        e_or2i      %r3, LO(TLB6_MAS2)
        mtspr       626, %r3        /* MAS2 */
        e_lis       %r3, HI(TLB6_MAS3)
        e_or2i      %r3, LO(TLB6_MAS3)
        mtspr       627, %r3        /* MAS3 */
        tlbwe
#endif /* BOOT_CORE1 */

        se_blr

        /*
         * RAM clearing.
         */
        .align      2
_ramclear:
        /*
         * This device requires a write to all RAM location in order to
         * initialize the ECC detection hardware, this is going to slow
         * down the startup but there is no way around.
         */
        xor         %r0, %r0, %r0
        xor         %r1, %r1, %r1
        xor         %r2, %r2, %r2
        xor         %r3, %r3, %r3
        xor         %r4, %r4, %r4
        xor         %r5, %r5, %r5
        xor         %r6, %r6, %r6
        xor         %r7, %r7, %r7
        xor         %r8, %r8, %r8
        xor         %r9, %r9, %r9
        xor         %r10, %r10, %r10
        xor         %r11, %r11, %r11
        xor         %r12, %r12, %r12
        xor         %r13, %r13, %r13
        xor         %r14, %r14, %r14
        xor         %r15, %r15, %r15
        xor         %r16, %r16, %r16
        xor         %r17, %r17, %r17
        xor         %r18, %r18, %r18
        xor         %r19, %r19, %r19
        xor         %r20, %r20, %r20
        xor         %r21, %r21, %r21
        xor         %r22, %r22, %r22
        xor         %r23, %r23, %r23
        xor         %r24, %r24, %r24
        xor         %r25, %r25, %r25
        xor         %r26, %r26, %r26
        xor         %r27, %r27, %r27
        xor         %r28, %r28, %r28
        xor         %r29, %r29, %r29
        xor         %r30, %r30, %r30
        xor         %r31, %r31, %r31
        e_lis       %r4, HI(__ram_start__)
        e_or2i      %r4, LO(__ram_start__)
        e_lis       %r5, HI(__ram_end__)
        e_or2i      %r5, LO(__ram_end__)
.cleareccloop:
        cmplw       %r4, %r5
        se_bge      .cleareccend
        e_stmw      %r16, 0(%r4)
        e_addi      %r4, %r4, 64
        se_b        .cleareccloop
.cleareccend:

        se_blr

        /*
         * Special function registers clearing, required in order to avoid
         * possible problems with lockstep mode.
         */
        .align      2
_regclear:
        mtcrf       0xFF, %r31
        mtspr       9, %r31         /* CTR     */
        mtspr       22, %r31        /* DEC     */
        mtspr       26, %r31        /* SRR0-1  */
        mtspr       27, %r31
        mtspr       54, %r31        /* DECAR   */
        mtspr       58, %r31        /* CSRR0-1 */
        mtspr       59, %r31
        mtspr       61, %r31        /* DEAR    */
        mtspr       256, %r31       /* USPRG0  */
        mtspr       272, %r31       /* SPRG1-7 */
        mtspr       273, %r31
        mtspr       274, %r31
        mtspr       275, %r31
        mtspr       276, %r31
        mtspr       277, %r31
        mtspr       278, %r31
        mtspr       279, %r31
        mtspr       285, %r31       /* TBU     */
        mtspr       284, %r31       /* TBL     */
#if 0
        mtspr       318, %r31       /* DVC1-2  */
        mtspr       319, %r31
#endif
        mtspr       562, %r31       /* DBCNT */
        mtspr       570, %r31       /* MCSRR0  */
        mtspr       571, %r31       /* MCSRR1  */
        mtspr       604, %r31       /* SPRG8-9 */
        mtspr       605, %r31

        se_blr

        /*
         * TLB0 re-allocation to flash.
         */
        .align      2
_tlb0alloc:
        /*
         * Finally the TLB0 is re-allocated to flash, note, the final phase
         * is executed from RAM.
         */
        e_lis       %r3, HI(TLB0_MAS0)
        mtspr       624, %r3        /* MAS0 */
        e_lis       %r3, HI(TLB0_MAS1)
        e_or2i      %r3, LO(TLB0_MAS1)
        mtspr       625, %r3        /* MAS1 */
        e_lis       %r3, HI(TLB0_MAS2)
        e_or2i      %r3, LO(TLB0_MAS2)
        mtspr       626, %r3        /* MAS2 */
        e_lis       %r3, HI(TLB0_MAS3)
        e_or2i      %r3, LO(TLB0_MAS3)
        mtspr       627, %r3        /* MAS3 */
        se_mflr     %r4
        e_lis       %r6, HI(_ramcode)
        e_or2i      %r6, LO(_ramcode)
        e_lis       %r7, HI(0x40010000)
        se_mtctr    %r7
        se_lwz      %r3, 0(%r6)
        se_stw      %r3, 0(%r7)
        se_lwz      %r3, 4(%r6)
        se_stw      %r3, 4(%r7)
        se_lwz      %r3, 8(%r6)
        se_stw      %r3, 8(%r7)
        se_bctrl
        se_mtlr     %r4

        /*
         * Branch prediction enabled.
         */
        e_li        %r3, BUCSR_DEFAULT
        mtspr       1013, %r3       /* BUCSR */

        /*
         * Cache invalidated and then enabled.
         */
        se_li       %r3, LICSR1_ICINV
        mtspr       1011, %r3       /* LICSR1 */
.inv:   mfspr       %r3, 1011       /* LICSR1 */
        e_and2i.    %r3, LICSR1_ICINV
        se_bne      .inv
        e_lis       %r3, HI(LICSR1_DEFAULT)
        e_or2i      %r3, LO(LICSR1_DEFAULT)
        mtspr       1011, %r3       /* LICSR1 */

        se_blr

        /*
         * Core 0 exception vectors initialization.
         */
        .align      2
_iv0init:
        /* MSR initialization.*/
        e_lis       %r3, HI(MSR_DEFAULT)
        e_or2i      %r3, LO(MSR_DEFAULT)
        mtMSR       %r3

        /* IVPR initialization.*/
        e_lis       %r3, HI(__ivpr0_base__)
        e_or2i      %r3, LO(__ivpr0_base__)
        mtIVPR      %r3

        se_blr

#if (BOOT_CORE1 == 1)
        /*
         * Core 1 exception vectors initialization.
         */
        .align      2
_iv1init:
        /* MSR initialization.*/
        e_lis       %r3, HI(MSR_DEFAULT)
        e_or2i      %r3, LO(MSR_DEFAULT)
        mtMSR       %r3

        /* IVPR initialization.*/
        e_lis       %r3, HI(__ivpr1_base__)
        e_or2i      %r3, LO(__ivpr1_base__)
        mtIVPR      %r3

        se_blr
#endif /* BOOT_CORE1 */

        /*
         * Core 0 exceptions vectors.
         */
        .section    .core0_ivors, "axv"
        .globl      IVORS
IVORS:
        e_b         _IVOR0
        .align      4
        e_b         _IVOR1
        .align      4
        e_b         _IVOR2
        .align      4
        e_b         _IVOR3
        .align      4
        e_b         _IVOR4
        .align      4
        e_b         _IVOR5
        .align      4
        e_b         _IVOR6
        .align      4
        e_b         _IVOR7
        .align      4
        e_b         _IVOR8
        .align      4
        e_b         _IVOR9
        .align      4
        e_b         _IVOR10
        .align      4
        e_b         _IVOR11
        .align      4
        e_b         _IVOR12
        .align      4
        e_b         _IVOR13
        .align      4
        e_b         _IVOR14
        .align      4
        e_b         _IVOR15
        .align      4
        e_b         _IVOR32
        .align      4
        e_b         _IVOR33
        .align      4
        e_b         _IVOR34

#if (BOOT_CORE1 == 1)
        /*
         * Core 1 exceptions vectors.
         */
        .section    .core1_ivors, "axv"
        .globl      C1_IVORS
C1_IVORS:
        e_b         _C1_IVOR0
        .align      4
        e_b         _C1_IVOR1
        .align      4
        e_b         _C1_IVOR2
        .align      4
        e_b         _C1_IVOR3
        .align      4
        e_b         _C1_IVOR4
        .align      4
        e_b         _C1_IVOR5
        .align      4
        e_b         _C1_IVOR6
        .align      4
        e_b         _C1_IVOR7
        .align      4
        e_b         _C1_IVOR8
        .align      4
        e_b         _C1_IVOR9
        .align      4
        e_b         _C1_IVOR10
        .align      4
        e_b         _C1_IVOR11
        .align      4
        e_b         _C1_IVOR12
        .align      4
        e_b         _C1_IVOR13
        .align      4
        e_b         _C1_IVOR14
        .align      4
        e_b         _C1_IVOR15
        .align      4
        e_b         _C1_IVOR32
        .align      4
        e_b         _C1_IVOR33
        .align      4
        e_b         _C1_IVOR34
#endif /* BOOT_CORE1 */

        .section    .handlers, "axv"

        /*
         * Unhandled exceptions handler for core 0.
         */
        .align      2
        .weak       _IVOR0,  _IVOR1,  _IVOR2,  _IVOR3
        .weak       _IVOR4,  _IVOR5,  _IVOR6,  _IVOR7
        .weak       _IVOR8,  _IVOR9,  _IVOR10, _IVOR11
        .weak       _IVOR12, _IVOR13, _IVOR14, _IVOR15
        .weak       _IVOR32, _IVOR33, _IVOR34
        .weak       _unhandled_exception0
        .type       _unhandled_exception0, @function
_IVOR0:
_IVOR1:
_IVOR2:
_IVOR3:
_IVOR4:
_IVOR5:
_IVOR6:
_IVOR7:
_IVOR8:
_IVOR9:
_IVOR10:
_IVOR11:
_IVOR12:
_IVOR13:
_IVOR14:
_IVOR15:
_IVOR32:
_IVOR33:
_IVOR34:
_unhandled_exception0:
        se_b        _unhandled_exception0
#if (BOOT_CORE1 == 1)
        /*
         * Unhandled exceptions handler for core 1.
         */
        .align      2
        .weak       _C1_IVOR0,  _C1_IVOR1,  _C1_IVOR2,  _C1_IVOR3
        .weak       _C1_IVOR4,  _C1_IVOR5,  _C1_IVOR6,  _C1_IVOR7
        .weak       _C1_IVOR8,  _C1_IVOR9,  _C1_IVOR10, _C1_IVOR11
        .weak       _C1_IVOR12, _C1_IVOR13, _C1_IVOR14, _C1_IVOR15
        .weak       _C1_IVOR32, _C1_IVOR33, _C1_IVOR34
        .weak       _unhandled_exception1
        .type       _unhandled_exception1, @function
_C1_IVOR0:
_C1_IVOR1:
_C1_IVOR2:
_C1_IVOR3:
_C1_IVOR4:
_C1_IVOR5:
_C1_IVOR6:
_C1_IVOR7:
_C1_IVOR8:
_C1_IVOR9:
_C1_IVOR10:
_C1_IVOR11:
_C1_IVOR12:
_C1_IVOR13:
_C1_IVOR14:
_C1_IVOR15:
_C1_IVOR32:
_C1_IVOR33:
_C1_IVOR34:
_unhandled_exception1:
        se_b        _unhandled_exception1
#endif /* BOOT_CORE1 */
#endif /* !defined(__DOXYGEN__) */

/** @} */

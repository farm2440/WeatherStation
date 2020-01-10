/*******************************************************************************
* File Name: Timeout.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the Timeout
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_Timeout_H)
#define CY_TCPWM_Timeout_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Timeout_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Timeout_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Timeout_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Timeout_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Timeout_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Timeout_QUAD_ENCODING_MODES            (0lu)
#define Timeout_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define Timeout_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Timeout_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Timeout_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Timeout_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Timeout_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Timeout_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Timeout_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Timeout_TC_RUN_MODE                    (0lu)
#define Timeout_TC_COUNTER_MODE                (0lu)
#define Timeout_TC_COMP_CAP_MODE               (0lu)
#define Timeout_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Timeout_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Timeout_TC_COUNT_SIGNAL_MODE           (3lu)
#define Timeout_TC_START_SIGNAL_MODE           (0lu)
#define Timeout_TC_STOP_SIGNAL_MODE            (0lu)
#define Timeout_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Timeout_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Timeout_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Timeout_TC_START_SIGNAL_PRESENT        (0lu)
#define Timeout_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Timeout_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Timeout_TC_INTERRUPT_MASK              (2lu)

/* PWM Mode */
/* Parameters */
#define Timeout_PWM_KILL_EVENT                 (0lu)
#define Timeout_PWM_STOP_EVENT                 (0lu)
#define Timeout_PWM_MODE                       (4lu)
#define Timeout_PWM_OUT_N_INVERT               (0lu)
#define Timeout_PWM_OUT_INVERT                 (0lu)
#define Timeout_PWM_ALIGN                      (0lu)
#define Timeout_PWM_RUN_MODE                   (0lu)
#define Timeout_PWM_DEAD_TIME_CYCLE            (0lu)
#define Timeout_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Timeout_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Timeout_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Timeout_PWM_START_SIGNAL_MODE          (0lu)
#define Timeout_PWM_STOP_SIGNAL_MODE           (0lu)
#define Timeout_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Timeout_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Timeout_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Timeout_PWM_START_SIGNAL_PRESENT       (0lu)
#define Timeout_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Timeout_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Timeout_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Timeout_TC_PERIOD_VALUE                (65535lu)
#define Timeout_TC_COMPARE_VALUE               (3000lu)
#define Timeout_TC_COMPARE_BUF_VALUE           (65535lu)
#define Timeout_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Timeout_PWM_PERIOD_VALUE               (65535lu)
#define Timeout_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Timeout_PWM_PERIOD_SWAP                (0lu)
#define Timeout_PWM_COMPARE_VALUE              (65535lu)
#define Timeout_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Timeout_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Timeout__LEFT 0
#define Timeout__RIGHT 1
#define Timeout__CENTER 2
#define Timeout__ASYMMETRIC 3

#define Timeout__X1 0
#define Timeout__X2 1
#define Timeout__X4 2

#define Timeout__PWM 4
#define Timeout__PWM_DT 5
#define Timeout__PWM_PR 6

#define Timeout__INVERSE 1
#define Timeout__DIRECT 0

#define Timeout__CAPTURE 2
#define Timeout__COMPARE 0

#define Timeout__TRIG_LEVEL 3
#define Timeout__TRIG_RISING 0
#define Timeout__TRIG_FALLING 1
#define Timeout__TRIG_BOTH 2

#define Timeout__INTR_MASK_TC 1
#define Timeout__INTR_MASK_CC_MATCH 2
#define Timeout__INTR_MASK_NONE 0
#define Timeout__INTR_MASK_TC_CC 3

#define Timeout__UNCONFIG 8
#define Timeout__TIMER 1
#define Timeout__QUAD 3
#define Timeout__PWM_SEL 7

#define Timeout__COUNT_UP 0
#define Timeout__COUNT_DOWN 1
#define Timeout__COUNT_UPDOWN0 2
#define Timeout__COUNT_UPDOWN1 3


/* Prescaler */
#define Timeout_PRESCALE_DIVBY1                ((uint32)(0u << Timeout_PRESCALER_SHIFT))
#define Timeout_PRESCALE_DIVBY2                ((uint32)(1u << Timeout_PRESCALER_SHIFT))
#define Timeout_PRESCALE_DIVBY4                ((uint32)(2u << Timeout_PRESCALER_SHIFT))
#define Timeout_PRESCALE_DIVBY8                ((uint32)(3u << Timeout_PRESCALER_SHIFT))
#define Timeout_PRESCALE_DIVBY16               ((uint32)(4u << Timeout_PRESCALER_SHIFT))
#define Timeout_PRESCALE_DIVBY32               ((uint32)(5u << Timeout_PRESCALER_SHIFT))
#define Timeout_PRESCALE_DIVBY64               ((uint32)(6u << Timeout_PRESCALER_SHIFT))
#define Timeout_PRESCALE_DIVBY128              ((uint32)(7u << Timeout_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Timeout_MODE_TIMER_COMPARE             ((uint32)(Timeout__COMPARE         <<  \
                                                                  Timeout_MODE_SHIFT))
#define Timeout_MODE_TIMER_CAPTURE             ((uint32)(Timeout__CAPTURE         <<  \
                                                                  Timeout_MODE_SHIFT))
#define Timeout_MODE_QUAD                      ((uint32)(Timeout__QUAD            <<  \
                                                                  Timeout_MODE_SHIFT))
#define Timeout_MODE_PWM                       ((uint32)(Timeout__PWM             <<  \
                                                                  Timeout_MODE_SHIFT))
#define Timeout_MODE_PWM_DT                    ((uint32)(Timeout__PWM_DT          <<  \
                                                                  Timeout_MODE_SHIFT))
#define Timeout_MODE_PWM_PR                    ((uint32)(Timeout__PWM_PR          <<  \
                                                                  Timeout_MODE_SHIFT))

/* Quad Modes */
#define Timeout_MODE_X1                        ((uint32)(Timeout__X1              <<  \
                                                                  Timeout_QUAD_MODE_SHIFT))
#define Timeout_MODE_X2                        ((uint32)(Timeout__X2              <<  \
                                                                  Timeout_QUAD_MODE_SHIFT))
#define Timeout_MODE_X4                        ((uint32)(Timeout__X4              <<  \
                                                                  Timeout_QUAD_MODE_SHIFT))

/* Counter modes */
#define Timeout_COUNT_UP                       ((uint32)(Timeout__COUNT_UP        <<  \
                                                                  Timeout_UPDOWN_SHIFT))
#define Timeout_COUNT_DOWN                     ((uint32)(Timeout__COUNT_DOWN      <<  \
                                                                  Timeout_UPDOWN_SHIFT))
#define Timeout_COUNT_UPDOWN0                  ((uint32)(Timeout__COUNT_UPDOWN0   <<  \
                                                                  Timeout_UPDOWN_SHIFT))
#define Timeout_COUNT_UPDOWN1                  ((uint32)(Timeout__COUNT_UPDOWN1   <<  \
                                                                  Timeout_UPDOWN_SHIFT))

/* PWM output invert */
#define Timeout_INVERT_LINE                    ((uint32)(Timeout__INVERSE         <<  \
                                                                  Timeout_INV_OUT_SHIFT))
#define Timeout_INVERT_LINE_N                  ((uint32)(Timeout__INVERSE         <<  \
                                                                  Timeout_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Timeout_TRIG_RISING                    ((uint32)Timeout__TRIG_RISING)
#define Timeout_TRIG_FALLING                   ((uint32)Timeout__TRIG_FALLING)
#define Timeout_TRIG_BOTH                      ((uint32)Timeout__TRIG_BOTH)
#define Timeout_TRIG_LEVEL                     ((uint32)Timeout__TRIG_LEVEL)

/* Interrupt mask */
#define Timeout_INTR_MASK_TC                   ((uint32)Timeout__INTR_MASK_TC)
#define Timeout_INTR_MASK_CC_MATCH             ((uint32)Timeout__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Timeout_CC_MATCH_SET                   (0x00u)
#define Timeout_CC_MATCH_CLEAR                 (0x01u)
#define Timeout_CC_MATCH_INVERT                (0x02u)
#define Timeout_CC_MATCH_NO_CHANGE             (0x03u)
#define Timeout_OVERLOW_SET                    (0x00u)
#define Timeout_OVERLOW_CLEAR                  (0x04u)
#define Timeout_OVERLOW_INVERT                 (0x08u)
#define Timeout_OVERLOW_NO_CHANGE              (0x0Cu)
#define Timeout_UNDERFLOW_SET                  (0x00u)
#define Timeout_UNDERFLOW_CLEAR                (0x10u)
#define Timeout_UNDERFLOW_INVERT               (0x20u)
#define Timeout_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Timeout_PWM_MODE_LEFT                  (Timeout_CC_MATCH_CLEAR        |   \
                                                         Timeout_OVERLOW_SET           |   \
                                                         Timeout_UNDERFLOW_NO_CHANGE)
#define Timeout_PWM_MODE_RIGHT                 (Timeout_CC_MATCH_SET          |   \
                                                         Timeout_OVERLOW_NO_CHANGE     |   \
                                                         Timeout_UNDERFLOW_CLEAR)
#define Timeout_PWM_MODE_ASYM                  (Timeout_CC_MATCH_INVERT       |   \
                                                         Timeout_OVERLOW_SET           |   \
                                                         Timeout_UNDERFLOW_CLEAR)

#if (Timeout_CY_TCPWM_V2)
    #if(Timeout_CY_TCPWM_4000)
        #define Timeout_PWM_MODE_CENTER                (Timeout_CC_MATCH_INVERT       |   \
                                                                 Timeout_OVERLOW_NO_CHANGE     |   \
                                                                 Timeout_UNDERFLOW_CLEAR)
    #else
        #define Timeout_PWM_MODE_CENTER                (Timeout_CC_MATCH_INVERT       |   \
                                                                 Timeout_OVERLOW_SET           |   \
                                                                 Timeout_UNDERFLOW_CLEAR)
    #endif /* (Timeout_CY_TCPWM_4000) */
#else
    #define Timeout_PWM_MODE_CENTER                (Timeout_CC_MATCH_INVERT       |   \
                                                             Timeout_OVERLOW_NO_CHANGE     |   \
                                                             Timeout_UNDERFLOW_CLEAR)
#endif /* (Timeout_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Timeout_CMD_CAPTURE                    (0u)
#define Timeout_CMD_RELOAD                     (8u)
#define Timeout_CMD_STOP                       (16u)
#define Timeout_CMD_START                      (24u)

/* Status */
#define Timeout_STATUS_DOWN                    (1u)
#define Timeout_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Timeout_Init(void);
void   Timeout_Enable(void);
void   Timeout_Start(void);
void   Timeout_Stop(void);

void   Timeout_SetMode(uint32 mode);
void   Timeout_SetCounterMode(uint32 counterMode);
void   Timeout_SetPWMMode(uint32 modeMask);
void   Timeout_SetQDMode(uint32 qdMode);

void   Timeout_SetPrescaler(uint32 prescaler);
void   Timeout_TriggerCommand(uint32 mask, uint32 command);
void   Timeout_SetOneShot(uint32 oneShotEnable);
uint32 Timeout_ReadStatus(void);

void   Timeout_SetPWMSyncKill(uint32 syncKillEnable);
void   Timeout_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Timeout_SetPWMDeadTime(uint32 deadTime);
void   Timeout_SetPWMInvert(uint32 mask);

void   Timeout_SetInterruptMode(uint32 interruptMask);
uint32 Timeout_GetInterruptSourceMasked(void);
uint32 Timeout_GetInterruptSource(void);
void   Timeout_ClearInterrupt(uint32 interruptMask);
void   Timeout_SetInterrupt(uint32 interruptMask);

void   Timeout_WriteCounter(uint32 count);
uint32 Timeout_ReadCounter(void);

uint32 Timeout_ReadCapture(void);
uint32 Timeout_ReadCaptureBuf(void);

void   Timeout_WritePeriod(uint32 period);
uint32 Timeout_ReadPeriod(void);
void   Timeout_WritePeriodBuf(uint32 periodBuf);
uint32 Timeout_ReadPeriodBuf(void);

void   Timeout_WriteCompare(uint32 compare);
uint32 Timeout_ReadCompare(void);
void   Timeout_WriteCompareBuf(uint32 compareBuf);
uint32 Timeout_ReadCompareBuf(void);

void   Timeout_SetPeriodSwap(uint32 swapEnable);
void   Timeout_SetCompareSwap(uint32 swapEnable);

void   Timeout_SetCaptureMode(uint32 triggerMode);
void   Timeout_SetReloadMode(uint32 triggerMode);
void   Timeout_SetStartMode(uint32 triggerMode);
void   Timeout_SetStopMode(uint32 triggerMode);
void   Timeout_SetCountMode(uint32 triggerMode);

void   Timeout_SaveConfig(void);
void   Timeout_RestoreConfig(void);
void   Timeout_Sleep(void);
void   Timeout_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Timeout_BLOCK_CONTROL_REG              (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Timeout_BLOCK_CONTROL_PTR              ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Timeout_COMMAND_REG                    (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Timeout_COMMAND_PTR                    ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Timeout_INTRRUPT_CAUSE_REG             (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Timeout_INTRRUPT_CAUSE_PTR             ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Timeout_CONTROL_REG                    (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__CTRL )
#define Timeout_CONTROL_PTR                    ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__CTRL )
#define Timeout_STATUS_REG                     (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__STATUS )
#define Timeout_STATUS_PTR                     ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__STATUS )
#define Timeout_COUNTER_REG                    (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__COUNTER )
#define Timeout_COUNTER_PTR                    ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__COUNTER )
#define Timeout_COMP_CAP_REG                   (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__CC )
#define Timeout_COMP_CAP_PTR                   ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__CC )
#define Timeout_COMP_CAP_BUF_REG               (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__CC_BUFF )
#define Timeout_COMP_CAP_BUF_PTR               ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__CC_BUFF )
#define Timeout_PERIOD_REG                     (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__PERIOD )
#define Timeout_PERIOD_PTR                     ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__PERIOD )
#define Timeout_PERIOD_BUF_REG                 (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Timeout_PERIOD_BUF_PTR                 ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Timeout_TRIG_CONTROL0_REG              (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Timeout_TRIG_CONTROL0_PTR              ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Timeout_TRIG_CONTROL1_REG              (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Timeout_TRIG_CONTROL1_PTR              ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Timeout_TRIG_CONTROL2_REG              (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Timeout_TRIG_CONTROL2_PTR              ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Timeout_INTERRUPT_REQ_REG              (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR )
#define Timeout_INTERRUPT_REQ_PTR              ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR )
#define Timeout_INTERRUPT_SET_REG              (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR_SET )
#define Timeout_INTERRUPT_SET_PTR              ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR_SET )
#define Timeout_INTERRUPT_MASK_REG             (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR_MASK )
#define Timeout_INTERRUPT_MASK_PTR             ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR_MASK )
#define Timeout_INTERRUPT_MASKED_REG           (*(reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Timeout_INTERRUPT_MASKED_PTR           ( (reg32 *) Timeout_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Timeout_MASK                           ((uint32)Timeout_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Timeout_RELOAD_CC_SHIFT                (0u)
#define Timeout_RELOAD_PERIOD_SHIFT            (1u)
#define Timeout_PWM_SYNC_KILL_SHIFT            (2u)
#define Timeout_PWM_STOP_KILL_SHIFT            (3u)
#define Timeout_PRESCALER_SHIFT                (8u)
#define Timeout_UPDOWN_SHIFT                   (16u)
#define Timeout_ONESHOT_SHIFT                  (18u)
#define Timeout_QUAD_MODE_SHIFT                (20u)
#define Timeout_INV_OUT_SHIFT                  (20u)
#define Timeout_INV_COMPL_OUT_SHIFT            (21u)
#define Timeout_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Timeout_RELOAD_CC_MASK                 ((uint32)(Timeout_1BIT_MASK        <<  \
                                                                            Timeout_RELOAD_CC_SHIFT))
#define Timeout_RELOAD_PERIOD_MASK             ((uint32)(Timeout_1BIT_MASK        <<  \
                                                                            Timeout_RELOAD_PERIOD_SHIFT))
#define Timeout_PWM_SYNC_KILL_MASK             ((uint32)(Timeout_1BIT_MASK        <<  \
                                                                            Timeout_PWM_SYNC_KILL_SHIFT))
#define Timeout_PWM_STOP_KILL_MASK             ((uint32)(Timeout_1BIT_MASK        <<  \
                                                                            Timeout_PWM_STOP_KILL_SHIFT))
#define Timeout_PRESCALER_MASK                 ((uint32)(Timeout_8BIT_MASK        <<  \
                                                                            Timeout_PRESCALER_SHIFT))
#define Timeout_UPDOWN_MASK                    ((uint32)(Timeout_2BIT_MASK        <<  \
                                                                            Timeout_UPDOWN_SHIFT))
#define Timeout_ONESHOT_MASK                   ((uint32)(Timeout_1BIT_MASK        <<  \
                                                                            Timeout_ONESHOT_SHIFT))
#define Timeout_QUAD_MODE_MASK                 ((uint32)(Timeout_3BIT_MASK        <<  \
                                                                            Timeout_QUAD_MODE_SHIFT))
#define Timeout_INV_OUT_MASK                   ((uint32)(Timeout_2BIT_MASK        <<  \
                                                                            Timeout_INV_OUT_SHIFT))
#define Timeout_MODE_MASK                      ((uint32)(Timeout_3BIT_MASK        <<  \
                                                                            Timeout_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Timeout_CAPTURE_SHIFT                  (0u)
#define Timeout_COUNT_SHIFT                    (2u)
#define Timeout_RELOAD_SHIFT                   (4u)
#define Timeout_STOP_SHIFT                     (6u)
#define Timeout_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Timeout_CAPTURE_MASK                   ((uint32)(Timeout_2BIT_MASK        <<  \
                                                                  Timeout_CAPTURE_SHIFT))
#define Timeout_COUNT_MASK                     ((uint32)(Timeout_2BIT_MASK        <<  \
                                                                  Timeout_COUNT_SHIFT))
#define Timeout_RELOAD_MASK                    ((uint32)(Timeout_2BIT_MASK        <<  \
                                                                  Timeout_RELOAD_SHIFT))
#define Timeout_STOP_MASK                      ((uint32)(Timeout_2BIT_MASK        <<  \
                                                                  Timeout_STOP_SHIFT))
#define Timeout_START_MASK                     ((uint32)(Timeout_2BIT_MASK        <<  \
                                                                  Timeout_START_SHIFT))

/* MASK */
#define Timeout_1BIT_MASK                      ((uint32)0x01u)
#define Timeout_2BIT_MASK                      ((uint32)0x03u)
#define Timeout_3BIT_MASK                      ((uint32)0x07u)
#define Timeout_6BIT_MASK                      ((uint32)0x3Fu)
#define Timeout_8BIT_MASK                      ((uint32)0xFFu)
#define Timeout_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Timeout_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Timeout_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Timeout_QUAD_ENCODING_MODES     << Timeout_QUAD_MODE_SHIFT))       |\
         ((uint32)(Timeout_CONFIG                  << Timeout_MODE_SHIFT)))

#define Timeout_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Timeout_PWM_STOP_EVENT          << Timeout_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Timeout_PWM_OUT_INVERT          << Timeout_INV_OUT_SHIFT))         |\
         ((uint32)(Timeout_PWM_OUT_N_INVERT        << Timeout_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Timeout_PWM_MODE                << Timeout_MODE_SHIFT)))

#define Timeout_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Timeout_PWM_RUN_MODE         << Timeout_ONESHOT_SHIFT))
            
#define Timeout_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Timeout_PWM_ALIGN            << Timeout_UPDOWN_SHIFT))

#define Timeout_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Timeout_PWM_KILL_EVENT      << Timeout_PWM_SYNC_KILL_SHIFT))

#define Timeout_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Timeout_PWM_DEAD_TIME_CYCLE  << Timeout_PRESCALER_SHIFT))

#define Timeout_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Timeout_PWM_PRESCALER        << Timeout_PRESCALER_SHIFT))

#define Timeout_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Timeout_TC_PRESCALER            << Timeout_PRESCALER_SHIFT))       |\
         ((uint32)(Timeout_TC_COUNTER_MODE         << Timeout_UPDOWN_SHIFT))          |\
         ((uint32)(Timeout_TC_RUN_MODE             << Timeout_ONESHOT_SHIFT))         |\
         ((uint32)(Timeout_TC_COMP_CAP_MODE        << Timeout_MODE_SHIFT)))
        
#define Timeout_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Timeout_QUAD_PHIA_SIGNAL_MODE   << Timeout_COUNT_SHIFT))           |\
         ((uint32)(Timeout_QUAD_INDEX_SIGNAL_MODE  << Timeout_RELOAD_SHIFT))          |\
         ((uint32)(Timeout_QUAD_STOP_SIGNAL_MODE   << Timeout_STOP_SHIFT))            |\
         ((uint32)(Timeout_QUAD_PHIB_SIGNAL_MODE   << Timeout_START_SHIFT)))

#define Timeout_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Timeout_PWM_SWITCH_SIGNAL_MODE  << Timeout_CAPTURE_SHIFT))         |\
         ((uint32)(Timeout_PWM_COUNT_SIGNAL_MODE   << Timeout_COUNT_SHIFT))           |\
         ((uint32)(Timeout_PWM_RELOAD_SIGNAL_MODE  << Timeout_RELOAD_SHIFT))          |\
         ((uint32)(Timeout_PWM_STOP_SIGNAL_MODE    << Timeout_STOP_SHIFT))            |\
         ((uint32)(Timeout_PWM_START_SIGNAL_MODE   << Timeout_START_SHIFT)))

#define Timeout_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Timeout_TC_CAPTURE_SIGNAL_MODE  << Timeout_CAPTURE_SHIFT))         |\
         ((uint32)(Timeout_TC_COUNT_SIGNAL_MODE    << Timeout_COUNT_SHIFT))           |\
         ((uint32)(Timeout_TC_RELOAD_SIGNAL_MODE   << Timeout_RELOAD_SHIFT))          |\
         ((uint32)(Timeout_TC_STOP_SIGNAL_MODE     << Timeout_STOP_SHIFT))            |\
         ((uint32)(Timeout_TC_START_SIGNAL_MODE    << Timeout_START_SHIFT)))
        
#define Timeout_TIMER_UPDOWN_CNT_USED                                                          \
                ((Timeout__COUNT_UPDOWN0 == Timeout_TC_COUNTER_MODE)                  ||\
                 (Timeout__COUNT_UPDOWN1 == Timeout_TC_COUNTER_MODE))

#define Timeout_PWM_UPDOWN_CNT_USED                                                            \
                ((Timeout__CENTER == Timeout_PWM_ALIGN)                               ||\
                 (Timeout__ASYMMETRIC == Timeout_PWM_ALIGN))               
        
#define Timeout_PWM_PR_INIT_VALUE              (1u)
#define Timeout_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Timeout_H */

/* [] END OF FILE */

/*******************************************************************************
* File Name: Timeout.c
* Version 2.10
*
* Description:
*  This file provides the source code to the API for the Timeout
*  component
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

#include "Timeout.h"

uint8 Timeout_initVar = 0u;


/*******************************************************************************
* Function Name: Timeout_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Timeout configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Timeout__QUAD == Timeout_CONFIG)
        Timeout_CONTROL_REG = Timeout_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Timeout_TRIG_CONTROL1_REG  = Timeout_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Timeout_SetInterruptMode(Timeout_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Timeout_SetCounterMode(Timeout_COUNT_DOWN);
        Timeout_WritePeriod(Timeout_QUAD_PERIOD_INIT_VALUE);
        Timeout_WriteCounter(Timeout_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Timeout__QUAD == Timeout_CONFIG) */

    #if (Timeout__TIMER == Timeout_CONFIG)
        Timeout_CONTROL_REG = Timeout_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Timeout_TRIG_CONTROL1_REG  = Timeout_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Timeout_SetInterruptMode(Timeout_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Timeout_WritePeriod(Timeout_TC_PERIOD_VALUE );

        #if (Timeout__COMPARE == Timeout_TC_COMP_CAP_MODE)
            Timeout_WriteCompare(Timeout_TC_COMPARE_VALUE);

            #if (1u == Timeout_TC_COMPARE_SWAP)
                Timeout_SetCompareSwap(1u);
                Timeout_WriteCompareBuf(Timeout_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Timeout_TC_COMPARE_SWAP) */
        #endif  /* (Timeout__COMPARE == Timeout_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Timeout_CY_TCPWM_V2 && Timeout_TIMER_UPDOWN_CNT_USED && !Timeout_CY_TCPWM_4000)
            Timeout_WriteCounter(1u);
        #elif(Timeout__COUNT_DOWN == Timeout_TC_COUNTER_MODE)
            Timeout_WriteCounter(Timeout_TC_PERIOD_VALUE);
        #else
            Timeout_WriteCounter(0u);
        #endif /* (Timeout_CY_TCPWM_V2 && Timeout_TIMER_UPDOWN_CNT_USED && !Timeout_CY_TCPWM_4000) */
    #endif  /* (Timeout__TIMER == Timeout_CONFIG) */

    #if (Timeout__PWM_SEL == Timeout_CONFIG)
        Timeout_CONTROL_REG = Timeout_CTRL_PWM_BASE_CONFIG;

        #if (Timeout__PWM_PR == Timeout_PWM_MODE)
            Timeout_CONTROL_REG |= Timeout_CTRL_PWM_RUN_MODE;
            Timeout_WriteCounter(Timeout_PWM_PR_INIT_VALUE);
        #else
            Timeout_CONTROL_REG |= Timeout_CTRL_PWM_ALIGN | Timeout_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Timeout_CY_TCPWM_V2 && Timeout_PWM_UPDOWN_CNT_USED && !Timeout_CY_TCPWM_4000)
                Timeout_WriteCounter(1u);
            #elif (Timeout__RIGHT == Timeout_PWM_ALIGN)
                Timeout_WriteCounter(Timeout_PWM_PERIOD_VALUE);
            #else 
                Timeout_WriteCounter(0u);
            #endif  /* (Timeout_CY_TCPWM_V2 && Timeout_PWM_UPDOWN_CNT_USED && !Timeout_CY_TCPWM_4000) */
        #endif  /* (Timeout__PWM_PR == Timeout_PWM_MODE) */

        #if (Timeout__PWM_DT == Timeout_PWM_MODE)
            Timeout_CONTROL_REG |= Timeout_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Timeout__PWM_DT == Timeout_PWM_MODE) */

        #if (Timeout__PWM == Timeout_PWM_MODE)
            Timeout_CONTROL_REG |= Timeout_CTRL_PWM_PRESCALER;
        #endif  /* (Timeout__PWM == Timeout_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Timeout_TRIG_CONTROL1_REG  = Timeout_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Timeout_SetInterruptMode(Timeout_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Timeout__PWM_PR == Timeout_PWM_MODE)
            Timeout_TRIG_CONTROL2_REG =
                    (Timeout_CC_MATCH_NO_CHANGE    |
                    Timeout_OVERLOW_NO_CHANGE      |
                    Timeout_UNDERFLOW_NO_CHANGE);
        #else
            #if (Timeout__LEFT == Timeout_PWM_ALIGN)
                Timeout_TRIG_CONTROL2_REG = Timeout_PWM_MODE_LEFT;
            #endif  /* ( Timeout_PWM_LEFT == Timeout_PWM_ALIGN) */

            #if (Timeout__RIGHT == Timeout_PWM_ALIGN)
                Timeout_TRIG_CONTROL2_REG = Timeout_PWM_MODE_RIGHT;
            #endif  /* ( Timeout_PWM_RIGHT == Timeout_PWM_ALIGN) */

            #if (Timeout__CENTER == Timeout_PWM_ALIGN)
                Timeout_TRIG_CONTROL2_REG = Timeout_PWM_MODE_CENTER;
            #endif  /* ( Timeout_PWM_CENTER == Timeout_PWM_ALIGN) */

            #if (Timeout__ASYMMETRIC == Timeout_PWM_ALIGN)
                Timeout_TRIG_CONTROL2_REG = Timeout_PWM_MODE_ASYM;
            #endif  /* (Timeout__ASYMMETRIC == Timeout_PWM_ALIGN) */
        #endif  /* (Timeout__PWM_PR == Timeout_PWM_MODE) */

        /* Set other values from customizer */
        Timeout_WritePeriod(Timeout_PWM_PERIOD_VALUE );
        Timeout_WriteCompare(Timeout_PWM_COMPARE_VALUE);

        #if (1u == Timeout_PWM_COMPARE_SWAP)
            Timeout_SetCompareSwap(1u);
            Timeout_WriteCompareBuf(Timeout_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Timeout_PWM_COMPARE_SWAP) */

        #if (1u == Timeout_PWM_PERIOD_SWAP)
            Timeout_SetPeriodSwap(1u);
            Timeout_WritePeriodBuf(Timeout_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Timeout_PWM_PERIOD_SWAP) */
    #endif  /* (Timeout__PWM_SEL == Timeout_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Timeout_Enable
********************************************************************************
*
* Summary:
*  Enables the Timeout.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Timeout_BLOCK_CONTROL_REG |= Timeout_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Timeout__PWM_SEL == Timeout_CONFIG)
        #if (0u == Timeout_PWM_START_SIGNAL_PRESENT)
            Timeout_TriggerCommand(Timeout_MASK, Timeout_CMD_START);
        #endif /* (0u == Timeout_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Timeout__PWM_SEL == Timeout_CONFIG) */

    #if (Timeout__TIMER == Timeout_CONFIG)
        #if (0u == Timeout_TC_START_SIGNAL_PRESENT)
            Timeout_TriggerCommand(Timeout_MASK, Timeout_CMD_START);
        #endif /* (0u == Timeout_TC_START_SIGNAL_PRESENT) */
    #endif /* (Timeout__TIMER == Timeout_CONFIG) */
    
    #if (Timeout__QUAD == Timeout_CONFIG)
        #if (0u != Timeout_QUAD_AUTO_START)
            Timeout_TriggerCommand(Timeout_MASK, Timeout_CMD_RELOAD);
        #endif /* (0u != Timeout_QUAD_AUTO_START) */
    #endif  /* (Timeout__QUAD == Timeout_CONFIG) */
}


/*******************************************************************************
* Function Name: Timeout_Start
********************************************************************************
*
* Summary:
*  Initializes the Timeout with default customizer
*  values when called the first time and enables the Timeout.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Timeout_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Timeout_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Timeout_Start() routine.
*
*******************************************************************************/
void Timeout_Start(void)
{
    if (0u == Timeout_initVar)
    {
        Timeout_Init();
        Timeout_initVar = 1u;
    }

    Timeout_Enable();
}


/*******************************************************************************
* Function Name: Timeout_Stop
********************************************************************************
*
* Summary:
*  Disables the Timeout.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_BLOCK_CONTROL_REG &= (uint32)~Timeout_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Timeout. This function is used when
*  configured as a generic Timeout and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Timeout to operate in
*   Values:
*   - Timeout_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Timeout_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Timeout_MODE_QUAD - Quadrature decoder
*         - Timeout_MODE_PWM - PWM
*         - Timeout_MODE_PWM_DT - PWM with dead time
*         - Timeout_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_MODE_MASK;
    Timeout_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Timeout_MODE_X1 - Counts on phi 1 rising
*         - Timeout_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Timeout_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_QUAD_MODE_MASK;
    Timeout_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Timeout_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Timeout_PRESCALE_DIVBY2    - Divide by 2
*         - Timeout_PRESCALE_DIVBY4    - Divide by 4
*         - Timeout_PRESCALE_DIVBY8    - Divide by 8
*         - Timeout_PRESCALE_DIVBY16   - Divide by 16
*         - Timeout_PRESCALE_DIVBY32   - Divide by 32
*         - Timeout_PRESCALE_DIVBY64   - Divide by 64
*         - Timeout_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_PRESCALER_MASK;
    Timeout_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Timeout runs
*  continuously or stops when terminal count is reached.  By default the
*  Timeout operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_ONESHOT_MASK;
    Timeout_CONTROL_REG |= ((uint32)((oneShotEnable & Timeout_1BIT_MASK) <<
                                                               Timeout_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetPWMMode(uint32 modeMask)
{
    Timeout_TRIG_CONTROL2_REG = (modeMask & Timeout_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Timeout_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_PWM_SYNC_KILL_MASK;
    Timeout_CONTROL_REG |= ((uint32)((syncKillEnable & Timeout_1BIT_MASK)  <<
                                               Timeout_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_PWM_STOP_KILL_MASK;
    Timeout_CONTROL_REG |= ((uint32)((stopOnKillEnable & Timeout_1BIT_MASK)  <<
                                                         Timeout_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_PRESCALER_MASK;
    Timeout_CONTROL_REG |= ((uint32)((deadTime & Timeout_8BIT_MASK) <<
                                                          Timeout_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - Timeout_INVERT_LINE   - Inverts the line output
*         - Timeout_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_INV_OUT_MASK;
    Timeout_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Timeout_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_WriteCounter(uint32 count)
{
    Timeout_COUNTER_REG = (count & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 Timeout_ReadCounter(void)
{
    return (Timeout_COUNTER_REG & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Timeout_COUNT_UP       - Counts up
*     - Timeout_COUNT_DOWN     - Counts down
*     - Timeout_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Timeout_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_UPDOWN_MASK;
    Timeout_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_WritePeriod(uint32 period)
{
    Timeout_PERIOD_REG = (period & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Timeout_ReadPeriod(void)
{
    return (Timeout_PERIOD_REG & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_RELOAD_CC_MASK;
    Timeout_CONTROL_REG |= (swapEnable & Timeout_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_WritePeriodBuf(uint32 periodBuf)
{
    Timeout_PERIOD_BUF_REG = (periodBuf & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Timeout_ReadPeriodBuf(void)
{
    return (Timeout_PERIOD_BUF_REG & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_CONTROL_REG &= (uint32)~Timeout_RELOAD_PERIOD_MASK;
    Timeout_CONTROL_REG |= ((uint32)((swapEnable & Timeout_1BIT_MASK) <<
                                                            Timeout_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Timeout_WriteCompare(uint32 compare)
{
    #if (Timeout_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Timeout_CY_TCPWM_4000) */

    #if (Timeout_CY_TCPWM_4000)
        currentMode = ((Timeout_CONTROL_REG & Timeout_UPDOWN_MASK) >> Timeout_UPDOWN_SHIFT);

        if (((uint32)Timeout__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Timeout__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Timeout_CY_TCPWM_4000) */
    
    Timeout_COMP_CAP_REG = (compare & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Timeout_ReadCompare(void)
{
    #if (Timeout_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Timeout_CY_TCPWM_4000) */

    #if (Timeout_CY_TCPWM_4000)
        currentMode = ((Timeout_CONTROL_REG & Timeout_UPDOWN_MASK) >> Timeout_UPDOWN_SHIFT);
        
        regVal = Timeout_COMP_CAP_REG;
        
        if (((uint32)Timeout__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Timeout__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Timeout_16BIT_MASK);
    #else
        return (Timeout_COMP_CAP_REG & Timeout_16BIT_MASK);
    #endif /* (Timeout_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Timeout_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
* Note:
*  It is not recommended to use the value equal to "0" or equal to 
*  "period value" in Center or Asymmetric align PWM modes on the 
*  PSoC 4100/PSoC 4200 devices.
*  PSoC 4000 devices write the 16 bit compare register with the decremented 
*  compare value in the Up counting mode (except 0x0u), and the incremented 
*  compare value in the Down counting mode (except 0xFFFFu).
*
*******************************************************************************/
void Timeout_WriteCompareBuf(uint32 compareBuf)
{
    #if (Timeout_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Timeout_CY_TCPWM_4000) */

    #if (Timeout_CY_TCPWM_4000)
        currentMode = ((Timeout_CONTROL_REG & Timeout_UPDOWN_MASK) >> Timeout_UPDOWN_SHIFT);

        if (((uint32)Timeout__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Timeout__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Timeout_CY_TCPWM_4000) */
    
    Timeout_COMP_CAP_BUF_REG = (compareBuf & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
* Note:
*  PSoC 4000 devices read the incremented compare register value in the 
*  Up counting mode (except 0xFFFFu), and the decremented value in the 
*  Down counting mode (except 0x0u).
*
*******************************************************************************/
uint32 Timeout_ReadCompareBuf(void)
{
    #if (Timeout_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Timeout_CY_TCPWM_4000) */

    #if (Timeout_CY_TCPWM_4000)
        currentMode = ((Timeout_CONTROL_REG & Timeout_UPDOWN_MASK) >> Timeout_UPDOWN_SHIFT);

        regVal = Timeout_COMP_CAP_BUF_REG;
        
        if (((uint32)Timeout__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Timeout__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Timeout_16BIT_MASK);
    #else
        return (Timeout_COMP_CAP_BUF_REG & Timeout_16BIT_MASK);
    #endif /* (Timeout_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Timeout_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 Timeout_ReadCapture(void)
{
    return (Timeout_COMP_CAP_REG & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 Timeout_ReadCaptureBuf(void)
{
    return (Timeout_COMP_CAP_BUF_REG & Timeout_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Timeout_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timeout_TRIG_LEVEL     - Level
*     - Timeout_TRIG_RISING    - Rising edge
*     - Timeout_TRIG_FALLING   - Falling edge
*     - Timeout_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_TRIG_CONTROL1_REG &= (uint32)~Timeout_CAPTURE_MASK;
    Timeout_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timeout_TRIG_LEVEL     - Level
*     - Timeout_TRIG_RISING    - Rising edge
*     - Timeout_TRIG_FALLING   - Falling edge
*     - Timeout_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_TRIG_CONTROL1_REG &= (uint32)~Timeout_RELOAD_MASK;
    Timeout_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timeout_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timeout_TRIG_LEVEL     - Level
*     - Timeout_TRIG_RISING    - Rising edge
*     - Timeout_TRIG_FALLING   - Falling edge
*     - Timeout_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_TRIG_CONTROL1_REG &= (uint32)~Timeout_START_MASK;
    Timeout_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timeout_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timeout_TRIG_LEVEL     - Level
*     - Timeout_TRIG_RISING    - Rising edge
*     - Timeout_TRIG_FALLING   - Falling edge
*     - Timeout_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_TRIG_CONTROL1_REG &= (uint32)~Timeout_STOP_MASK;
    Timeout_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timeout_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Timeout_TRIG_LEVEL     - Level
*     - Timeout_TRIG_RISING    - Rising edge
*     - Timeout_TRIG_FALLING   - Falling edge
*     - Timeout_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_TRIG_CONTROL1_REG &= (uint32)~Timeout_COUNT_MASK;
    Timeout_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Timeout_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - Timeout_CMD_CAPTURE    - Trigger Capture/Switch command
*     - Timeout_CMD_RELOAD     - Trigger Reload/Index command
*     - Timeout_CMD_STOP       - Trigger Stop/Kill command
*     - Timeout_CMD_START      - Trigger Start/phiB command
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Timeout_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Timeout_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Timeout.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Timeout_STATUS_DOWN    - Set if counting down
*     - Timeout_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Timeout_ReadStatus(void)
{
    return ((Timeout_STATUS_REG >> Timeout_RUNNING_STATUS_SHIFT) |
            (Timeout_STATUS_REG & Timeout_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Timeout_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Timeout_INTR_MASK_TC       - Terminal count mask
*     - Timeout_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetInterruptMode(uint32 interruptMask)
{
    Timeout_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Timeout_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - Timeout_INTR_MASK_TC       - Terminal count mask
*     - Timeout_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Timeout_GetInterruptSourceMasked(void)
{
    return (Timeout_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Timeout_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - Timeout_INTR_MASK_TC       - Terminal count mask
*     - Timeout_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Timeout_GetInterruptSource(void)
{
    return (Timeout_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Timeout_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Timeout_INTR_MASK_TC       - Terminal count mask
*     - Timeout_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_ClearInterrupt(uint32 interruptMask)
{
    Timeout_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Timeout_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Timeout_INTR_MASK_TC       - Terminal count mask
*     - Timeout_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SetInterrupt(uint32 interruptMask)
{
    Timeout_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */

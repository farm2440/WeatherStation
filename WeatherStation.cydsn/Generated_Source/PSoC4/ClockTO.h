/*******************************************************************************
* File Name: ClockTO.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_ClockTO_H)
#define CY_CLOCK_ClockTO_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void ClockTO_StartEx(uint32 alignClkDiv);
#define ClockTO_Start() \
    ClockTO_StartEx(ClockTO__PA_DIV_ID)

#else

void ClockTO_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void ClockTO_Stop(void);

void ClockTO_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 ClockTO_GetDividerRegister(void);
uint8  ClockTO_GetFractionalDividerRegister(void);

#define ClockTO_Enable()                         ClockTO_Start()
#define ClockTO_Disable()                        ClockTO_Stop()
#define ClockTO_SetDividerRegister(clkDivider, reset)  \
    ClockTO_SetFractionalDividerRegister((clkDivider), 0u)
#define ClockTO_SetDivider(clkDivider)           ClockTO_SetDividerRegister((clkDivider), 1u)
#define ClockTO_SetDividerValue(clkDivider)      ClockTO_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define ClockTO_DIV_ID     ClockTO__DIV_ID

#define ClockTO_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define ClockTO_CTRL_REG   (*(reg32 *)ClockTO__CTRL_REGISTER)
#define ClockTO_DIV_REG    (*(reg32 *)ClockTO__DIV_REGISTER)

#define ClockTO_CMD_DIV_SHIFT          (0u)
#define ClockTO_CMD_PA_DIV_SHIFT       (8u)
#define ClockTO_CMD_DISABLE_SHIFT      (30u)
#define ClockTO_CMD_ENABLE_SHIFT       (31u)

#define ClockTO_CMD_DISABLE_MASK       ((uint32)((uint32)1u << ClockTO_CMD_DISABLE_SHIFT))
#define ClockTO_CMD_ENABLE_MASK        ((uint32)((uint32)1u << ClockTO_CMD_ENABLE_SHIFT))

#define ClockTO_DIV_FRAC_MASK  (0x000000F8u)
#define ClockTO_DIV_FRAC_SHIFT (3u)
#define ClockTO_DIV_INT_MASK   (0xFFFFFF00u)
#define ClockTO_DIV_INT_SHIFT  (8u)

#else 

#define ClockTO_DIV_REG        (*(reg32 *)ClockTO__REGISTER)
#define ClockTO_ENABLE_REG     ClockTO_DIV_REG
#define ClockTO_DIV_FRAC_MASK  ClockTO__FRAC_MASK
#define ClockTO_DIV_FRAC_SHIFT (16u)
#define ClockTO_DIV_INT_MASK   ClockTO__DIVIDER_MASK
#define ClockTO_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_ClockTO_H) */

/* [] END OF FILE */

/*******************************************************************************
* File Name: PinWindCE.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PinWindCE_ALIASES_H) /* Pins PinWindCE_ALIASES_H */
#define CY_PINS_PinWindCE_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PinWindCE_0			(PinWindCE__0__PC)
#define PinWindCE_0_PS		(PinWindCE__0__PS)
#define PinWindCE_0_PC		(PinWindCE__0__PC)
#define PinWindCE_0_DR		(PinWindCE__0__DR)
#define PinWindCE_0_SHIFT	(PinWindCE__0__SHIFT)
#define PinWindCE_0_INTR	((uint16)((uint16)0x0003u << (PinWindCE__0__SHIFT*2u)))

#define PinWindCE_INTR_ALL	 ((uint16)(PinWindCE_0_INTR))


#endif /* End Pins PinWindCE_ALIASES_H */


/* [] END OF FILE */

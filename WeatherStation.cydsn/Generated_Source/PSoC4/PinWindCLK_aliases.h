/*******************************************************************************
* File Name: PinWindCLK.h  
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

#if !defined(CY_PINS_PinWindCLK_ALIASES_H) /* Pins PinWindCLK_ALIASES_H */
#define CY_PINS_PinWindCLK_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PinWindCLK_0			(PinWindCLK__0__PC)
#define PinWindCLK_0_PS		(PinWindCLK__0__PS)
#define PinWindCLK_0_PC		(PinWindCLK__0__PC)
#define PinWindCLK_0_DR		(PinWindCLK__0__DR)
#define PinWindCLK_0_SHIFT	(PinWindCLK__0__SHIFT)
#define PinWindCLK_0_INTR	((uint16)((uint16)0x0003u << (PinWindCLK__0__SHIFT*2u)))

#define PinWindCLK_INTR_ALL	 ((uint16)(PinWindCLK_0_INTR))


#endif /* End Pins PinWindCLK_ALIASES_H */


/* [] END OF FILE */

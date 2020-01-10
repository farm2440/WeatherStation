/*******************************************************************************
* File Name: PinWindRX.h  
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

#if !defined(CY_PINS_PinWindRX_ALIASES_H) /* Pins PinWindRX_ALIASES_H */
#define CY_PINS_PinWindRX_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PinWindRX_0			(PinWindRX__0__PC)
#define PinWindRX_0_PS		(PinWindRX__0__PS)
#define PinWindRX_0_PC		(PinWindRX__0__PC)
#define PinWindRX_0_DR		(PinWindRX__0__DR)
#define PinWindRX_0_SHIFT	(PinWindRX__0__SHIFT)
#define PinWindRX_0_INTR	((uint16)((uint16)0x0003u << (PinWindRX__0__SHIFT*2u)))

#define PinWindRX_INTR_ALL	 ((uint16)(PinWindRX_0_INTR))


#endif /* End Pins PinWindRX_ALIASES_H */


/* [] END OF FILE */

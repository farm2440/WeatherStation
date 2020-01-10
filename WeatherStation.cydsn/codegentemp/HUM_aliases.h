/*******************************************************************************
* File Name: HUM.h  
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

#if !defined(CY_PINS_HUM_ALIASES_H) /* Pins HUM_ALIASES_H */
#define CY_PINS_HUM_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HUM_0			(HUM__0__PC)
#define HUM_0_PS		(HUM__0__PS)
#define HUM_0_PC		(HUM__0__PC)
#define HUM_0_DR		(HUM__0__DR)
#define HUM_0_SHIFT	(HUM__0__SHIFT)
#define HUM_0_INTR	((uint16)((uint16)0x0003u << (HUM__0__SHIFT*2u)))

#define HUM_INTR_ALL	 ((uint16)(HUM_0_INTR))


#endif /* End Pins HUM_ALIASES_H */


/* [] END OF FILE */

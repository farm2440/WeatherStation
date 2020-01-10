/*******************************************************************************
* File Name: PinWindCE.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PinWindCE_H) /* Pins PinWindCE_H */
#define CY_PINS_PinWindCE_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinWindCE_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} PinWindCE_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PinWindCE_Read(void);
void    PinWindCE_Write(uint8 value);
uint8   PinWindCE_ReadDataReg(void);
#if defined(PinWindCE__PC) || (CY_PSOC4_4200L) 
    void    PinWindCE_SetDriveMode(uint8 mode);
#endif
void    PinWindCE_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinWindCE_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PinWindCE_Sleep(void); 
void PinWindCE_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PinWindCE__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PinWindCE_DRIVE_MODE_BITS        (3)
    #define PinWindCE_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinWindCE_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PinWindCE_SetDriveMode() function.
         *  @{
         */
        #define PinWindCE_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PinWindCE_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PinWindCE_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PinWindCE_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PinWindCE_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PinWindCE_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PinWindCE_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PinWindCE_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PinWindCE_MASK               PinWindCE__MASK
#define PinWindCE_SHIFT              PinWindCE__SHIFT
#define PinWindCE_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinWindCE_SetInterruptMode() function.
     *  @{
     */
        #define PinWindCE_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PinWindCE_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PinWindCE_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PinWindCE_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PinWindCE__SIO)
    #define PinWindCE_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PinWindCE__PC) && (CY_PSOC4_4200L)
    #define PinWindCE_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PinWindCE_USBIO_DISABLE              ((uint32)(~PinWindCE_USBIO_ENABLE))
    #define PinWindCE_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PinWindCE_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PinWindCE_USBIO_ENTER_SLEEP          ((uint32)((1u << PinWindCE_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PinWindCE_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinWindCE_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PinWindCE_USBIO_SUSPEND_SHIFT)))
    #define PinWindCE_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PinWindCE_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinWindCE_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PinWindCE__PC)
    /* Port Configuration */
    #define PinWindCE_PC                 (* (reg32 *) PinWindCE__PC)
#endif
/* Pin State */
#define PinWindCE_PS                     (* (reg32 *) PinWindCE__PS)
/* Data Register */
#define PinWindCE_DR                     (* (reg32 *) PinWindCE__DR)
/* Input Buffer Disable Override */
#define PinWindCE_INP_DIS                (* (reg32 *) PinWindCE__PC2)

/* Interrupt configuration Registers */
#define PinWindCE_INTCFG                 (* (reg32 *) PinWindCE__INTCFG)
#define PinWindCE_INTSTAT                (* (reg32 *) PinWindCE__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PinWindCE_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PinWindCE__SIO)
    #define PinWindCE_SIO_REG            (* (reg32 *) PinWindCE__SIO)
#endif /* (PinWindCE__SIO_CFG) */

/* USBIO registers */
#if !defined(PinWindCE__PC) && (CY_PSOC4_4200L)
    #define PinWindCE_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PinWindCE_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PinWindCE_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PinWindCE_DRIVE_MODE_SHIFT       (0x00u)
#define PinWindCE_DRIVE_MODE_MASK        (0x07u << PinWindCE_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PinWindCE_H */


/* [] END OF FILE */

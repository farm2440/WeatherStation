/*******************************************************************************
* File Name: PinWindRX.h  
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

#if !defined(CY_PINS_PinWindRX_H) /* Pins PinWindRX_H */
#define CY_PINS_PinWindRX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinWindRX_aliases.h"


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
} PinWindRX_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PinWindRX_Read(void);
void    PinWindRX_Write(uint8 value);
uint8   PinWindRX_ReadDataReg(void);
#if defined(PinWindRX__PC) || (CY_PSOC4_4200L) 
    void    PinWindRX_SetDriveMode(uint8 mode);
#endif
void    PinWindRX_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinWindRX_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PinWindRX_Sleep(void); 
void PinWindRX_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PinWindRX__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PinWindRX_DRIVE_MODE_BITS        (3)
    #define PinWindRX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinWindRX_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PinWindRX_SetDriveMode() function.
         *  @{
         */
        #define PinWindRX_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PinWindRX_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PinWindRX_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PinWindRX_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PinWindRX_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PinWindRX_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PinWindRX_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PinWindRX_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PinWindRX_MASK               PinWindRX__MASK
#define PinWindRX_SHIFT              PinWindRX__SHIFT
#define PinWindRX_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinWindRX_SetInterruptMode() function.
     *  @{
     */
        #define PinWindRX_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PinWindRX_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PinWindRX_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PinWindRX_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PinWindRX__SIO)
    #define PinWindRX_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PinWindRX__PC) && (CY_PSOC4_4200L)
    #define PinWindRX_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PinWindRX_USBIO_DISABLE              ((uint32)(~PinWindRX_USBIO_ENABLE))
    #define PinWindRX_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PinWindRX_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PinWindRX_USBIO_ENTER_SLEEP          ((uint32)((1u << PinWindRX_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PinWindRX_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinWindRX_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PinWindRX_USBIO_SUSPEND_SHIFT)))
    #define PinWindRX_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PinWindRX_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinWindRX_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PinWindRX__PC)
    /* Port Configuration */
    #define PinWindRX_PC                 (* (reg32 *) PinWindRX__PC)
#endif
/* Pin State */
#define PinWindRX_PS                     (* (reg32 *) PinWindRX__PS)
/* Data Register */
#define PinWindRX_DR                     (* (reg32 *) PinWindRX__DR)
/* Input Buffer Disable Override */
#define PinWindRX_INP_DIS                (* (reg32 *) PinWindRX__PC2)

/* Interrupt configuration Registers */
#define PinWindRX_INTCFG                 (* (reg32 *) PinWindRX__INTCFG)
#define PinWindRX_INTSTAT                (* (reg32 *) PinWindRX__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PinWindRX_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PinWindRX__SIO)
    #define PinWindRX_SIO_REG            (* (reg32 *) PinWindRX__SIO)
#endif /* (PinWindRX__SIO_CFG) */

/* USBIO registers */
#if !defined(PinWindRX__PC) && (CY_PSOC4_4200L)
    #define PinWindRX_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PinWindRX_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PinWindRX_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PinWindRX_DRIVE_MODE_SHIFT       (0x00u)
#define PinWindRX_DRIVE_MODE_MASK        (0x07u << PinWindRX_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PinWindRX_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: PinWindCLK.h  
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

#if !defined(CY_PINS_PinWindCLK_H) /* Pins PinWindCLK_H */
#define CY_PINS_PinWindCLK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PinWindCLK_aliases.h"


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
} PinWindCLK_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PinWindCLK_Read(void);
void    PinWindCLK_Write(uint8 value);
uint8   PinWindCLK_ReadDataReg(void);
#if defined(PinWindCLK__PC) || (CY_PSOC4_4200L) 
    void    PinWindCLK_SetDriveMode(uint8 mode);
#endif
void    PinWindCLK_SetInterruptMode(uint16 position, uint16 mode);
uint8   PinWindCLK_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PinWindCLK_Sleep(void); 
void PinWindCLK_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PinWindCLK__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PinWindCLK_DRIVE_MODE_BITS        (3)
    #define PinWindCLK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PinWindCLK_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PinWindCLK_SetDriveMode() function.
         *  @{
         */
        #define PinWindCLK_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PinWindCLK_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PinWindCLK_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PinWindCLK_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PinWindCLK_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PinWindCLK_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PinWindCLK_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PinWindCLK_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PinWindCLK_MASK               PinWindCLK__MASK
#define PinWindCLK_SHIFT              PinWindCLK__SHIFT
#define PinWindCLK_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PinWindCLK_SetInterruptMode() function.
     *  @{
     */
        #define PinWindCLK_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PinWindCLK_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PinWindCLK_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PinWindCLK_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PinWindCLK__SIO)
    #define PinWindCLK_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PinWindCLK__PC) && (CY_PSOC4_4200L)
    #define PinWindCLK_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PinWindCLK_USBIO_DISABLE              ((uint32)(~PinWindCLK_USBIO_ENABLE))
    #define PinWindCLK_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PinWindCLK_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PinWindCLK_USBIO_ENTER_SLEEP          ((uint32)((1u << PinWindCLK_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PinWindCLK_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinWindCLK_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PinWindCLK_USBIO_SUSPEND_SHIFT)))
    #define PinWindCLK_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PinWindCLK_USBIO_SUSPEND_DEL_SHIFT)))
    #define PinWindCLK_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PinWindCLK__PC)
    /* Port Configuration */
    #define PinWindCLK_PC                 (* (reg32 *) PinWindCLK__PC)
#endif
/* Pin State */
#define PinWindCLK_PS                     (* (reg32 *) PinWindCLK__PS)
/* Data Register */
#define PinWindCLK_DR                     (* (reg32 *) PinWindCLK__DR)
/* Input Buffer Disable Override */
#define PinWindCLK_INP_DIS                (* (reg32 *) PinWindCLK__PC2)

/* Interrupt configuration Registers */
#define PinWindCLK_INTCFG                 (* (reg32 *) PinWindCLK__INTCFG)
#define PinWindCLK_INTSTAT                (* (reg32 *) PinWindCLK__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PinWindCLK_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PinWindCLK__SIO)
    #define PinWindCLK_SIO_REG            (* (reg32 *) PinWindCLK__SIO)
#endif /* (PinWindCLK__SIO_CFG) */

/* USBIO registers */
#if !defined(PinWindCLK__PC) && (CY_PSOC4_4200L)
    #define PinWindCLK_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PinWindCLK_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PinWindCLK_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PinWindCLK_DRIVE_MODE_SHIFT       (0x00u)
#define PinWindCLK_DRIVE_MODE_MASK        (0x07u << PinWindCLK_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PinWindCLK_H */


/* [] END OF FILE */

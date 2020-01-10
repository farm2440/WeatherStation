/*******************************************************************************
* File Name: HUM.h  
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

#if !defined(CY_PINS_HUM_H) /* Pins HUM_H */
#define CY_PINS_HUM_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HUM_aliases.h"


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
} HUM_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HUM_Read(void);
void    HUM_Write(uint8 value);
uint8   HUM_ReadDataReg(void);
#if defined(HUM__PC) || (CY_PSOC4_4200L) 
    void    HUM_SetDriveMode(uint8 mode);
#endif
void    HUM_SetInterruptMode(uint16 position, uint16 mode);
uint8   HUM_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HUM_Sleep(void); 
void HUM_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HUM__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HUM_DRIVE_MODE_BITS        (3)
    #define HUM_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HUM_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HUM_SetDriveMode() function.
         *  @{
         */
        #define HUM_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HUM_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HUM_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HUM_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HUM_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HUM_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HUM_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HUM_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HUM_MASK               HUM__MASK
#define HUM_SHIFT              HUM__SHIFT
#define HUM_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HUM_SetInterruptMode() function.
     *  @{
     */
        #define HUM_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HUM_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HUM_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HUM_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HUM__SIO)
    #define HUM_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HUM__PC) && (CY_PSOC4_4200L)
    #define HUM_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HUM_USBIO_DISABLE              ((uint32)(~HUM_USBIO_ENABLE))
    #define HUM_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HUM_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HUM_USBIO_ENTER_SLEEP          ((uint32)((1u << HUM_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HUM_USBIO_SUSPEND_DEL_SHIFT)))
    #define HUM_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HUM_USBIO_SUSPEND_SHIFT)))
    #define HUM_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HUM_USBIO_SUSPEND_DEL_SHIFT)))
    #define HUM_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HUM__PC)
    /* Port Configuration */
    #define HUM_PC                 (* (reg32 *) HUM__PC)
#endif
/* Pin State */
#define HUM_PS                     (* (reg32 *) HUM__PS)
/* Data Register */
#define HUM_DR                     (* (reg32 *) HUM__DR)
/* Input Buffer Disable Override */
#define HUM_INP_DIS                (* (reg32 *) HUM__PC2)

/* Interrupt configuration Registers */
#define HUM_INTCFG                 (* (reg32 *) HUM__INTCFG)
#define HUM_INTSTAT                (* (reg32 *) HUM__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HUM_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HUM__SIO)
    #define HUM_SIO_REG            (* (reg32 *) HUM__SIO)
#endif /* (HUM__SIO_CFG) */

/* USBIO registers */
#if !defined(HUM__PC) && (CY_PSOC4_4200L)
    #define HUM_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HUM_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HUM_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HUM_DRIVE_MODE_SHIFT       (0x00u)
#define HUM_DRIVE_MODE_MASK        (0x07u << HUM_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HUM_H */


/* [] END OF FILE */

/*******************************************************************************
* File Name: Timeout_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
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

static Timeout_BACKUP_STRUCT Timeout_backup;


/*******************************************************************************
* Function Name: Timeout_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Timeout_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_Sleep(void)
{
    if(0u != (Timeout_BLOCK_CONTROL_REG & Timeout_MASK))
    {
        Timeout_backup.enableState = 1u;
    }
    else
    {
        Timeout_backup.enableState = 0u;
    }

    Timeout_Stop();
    Timeout_SaveConfig();
}


/*******************************************************************************
* Function Name: Timeout_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Timeout_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Timeout_Wakeup(void)
{
    Timeout_RestoreConfig();

    if(0u != Timeout_backup.enableState)
    {
        Timeout_Enable();
    }
}


/* [] END OF FILE */

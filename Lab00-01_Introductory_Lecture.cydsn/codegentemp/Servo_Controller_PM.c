/*******************************************************************************
* File Name: Servo_Controller_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Servo_Controller.h"

static Servo_Controller_backupStruct Servo_Controller_backup;


/*******************************************************************************
* Function Name: Servo_Controller_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_Controller_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Servo_Controller_SaveConfig(void) 
{

    #if(!Servo_Controller_UsingFixedFunction)
        #if(!Servo_Controller_PWMModeIsCenterAligned)
            Servo_Controller_backup.PWMPeriod = Servo_Controller_ReadPeriod();
        #endif /* (!Servo_Controller_PWMModeIsCenterAligned) */
        Servo_Controller_backup.PWMUdb = Servo_Controller_ReadCounter();
        #if (Servo_Controller_UseStatus)
            Servo_Controller_backup.InterruptMaskValue = Servo_Controller_STATUS_MASK;
        #endif /* (Servo_Controller_UseStatus) */

        #if(Servo_Controller_DeadBandMode == Servo_Controller__B_PWM__DBM_256_CLOCKS || \
            Servo_Controller_DeadBandMode == Servo_Controller__B_PWM__DBM_2_4_CLOCKS)
            Servo_Controller_backup.PWMdeadBandValue = Servo_Controller_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(Servo_Controller_KillModeMinTime)
             Servo_Controller_backup.PWMKillCounterPeriod = Servo_Controller_ReadKillTime();
        #endif /* (Servo_Controller_KillModeMinTime) */

        #if(Servo_Controller_UseControl)
            Servo_Controller_backup.PWMControlRegister = Servo_Controller_ReadControlRegister();
        #endif /* (Servo_Controller_UseControl) */
    #endif  /* (!Servo_Controller_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: Servo_Controller_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_Controller_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_Controller_RestoreConfig(void) 
{
        #if(!Servo_Controller_UsingFixedFunction)
            #if(!Servo_Controller_PWMModeIsCenterAligned)
                Servo_Controller_WritePeriod(Servo_Controller_backup.PWMPeriod);
            #endif /* (!Servo_Controller_PWMModeIsCenterAligned) */

            Servo_Controller_WriteCounter(Servo_Controller_backup.PWMUdb);

            #if (Servo_Controller_UseStatus)
                Servo_Controller_STATUS_MASK = Servo_Controller_backup.InterruptMaskValue;
            #endif /* (Servo_Controller_UseStatus) */

            #if(Servo_Controller_DeadBandMode == Servo_Controller__B_PWM__DBM_256_CLOCKS || \
                Servo_Controller_DeadBandMode == Servo_Controller__B_PWM__DBM_2_4_CLOCKS)
                Servo_Controller_WriteDeadTime(Servo_Controller_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(Servo_Controller_KillModeMinTime)
                Servo_Controller_WriteKillTime(Servo_Controller_backup.PWMKillCounterPeriod);
            #endif /* (Servo_Controller_KillModeMinTime) */

            #if(Servo_Controller_UseControl)
                Servo_Controller_WriteControlRegister(Servo_Controller_backup.PWMControlRegister);
            #endif /* (Servo_Controller_UseControl) */
        #endif  /* (!Servo_Controller_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: Servo_Controller_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_Controller_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void Servo_Controller_Sleep(void) 
{
    #if(Servo_Controller_UseControl)
        if(Servo_Controller_CTRL_ENABLE == (Servo_Controller_CONTROL & Servo_Controller_CTRL_ENABLE))
        {
            /*Component is enabled */
            Servo_Controller_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            Servo_Controller_backup.PWMEnableState = 0u;
        }
    #endif /* (Servo_Controller_UseControl) */

    /* Stop component */
    Servo_Controller_Stop();

    /* Save registers configuration */
    Servo_Controller_SaveConfig();
}


/*******************************************************************************
* Function Name: Servo_Controller_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Servo_Controller_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Servo_Controller_Wakeup(void) 
{
     /* Restore registers values */
    Servo_Controller_RestoreConfig();

    if(Servo_Controller_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        Servo_Controller_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */

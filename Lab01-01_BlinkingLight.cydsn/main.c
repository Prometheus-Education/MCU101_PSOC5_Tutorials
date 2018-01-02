/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    LED_BLUE_Write(1);

    for(;;)
    {
        /* Place your application code here. */
        LED_BLUE_Write(1);
        CyDelay(1000);
        LED_BLUE_Write(0);
        CyDelay(1000);
    }
}

/* [] END OF FILE */

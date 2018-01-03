/* ========================================
 *
 * Copyright Prometheus Education, Inc, 2018
 * All Rights Reserved
 * Open Source, MIT License.
 *
 * No assurances given, this is educational software,
 * Prometheus Education, Inc. is not liable for damages or malfunctions.
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

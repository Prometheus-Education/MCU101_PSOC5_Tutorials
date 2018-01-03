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
    Blue_LED_Write(0);
    Servo_Controller_Start();
    UART_1_Start();
    ADC_SAR_1_Start();
    ADC_SAR_1_StartConvert();
   

    for(;;) //REPEAT FOREVER
    {
        /* Place your application code here. */
//        if(ADC_SAR_1_GetResult16() < 2048 )  //if the light sensor is below some limit
//        {
//            Blue_LED_Write(1);  //Turn the Blue LED ON
//        }
//        else
//        {
//            Blue_LED_Write(0);//Turn the Blue LED OFF
//        }
        
        
        
        Blue_LED_Write(1);  //Turn the Blue LED ON
        Servo_Controller_WriteCompare1(5);  //set PWM to go high for 5% of time
        UART_1_PutString("Rotate this way\n\r");
        CyDelay(1000);  //wait for 1s
        
        Blue_LED_Write(0);//Turn the Blue LED OFF
        Servo_Controller_WriteCompare1(10); //set PWM to go high for 10% of time
        UART_1_PutString("Rotate that way\n\r");
        CyDelay(1000);//wait for 1s
        
        
    }
}

/* [] END OF FILE */

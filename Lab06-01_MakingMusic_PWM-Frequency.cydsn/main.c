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

//NOTE: Make sure to update the definition below to match the PWM source clock
#define PWM_CLOCK 1000000

void Shutdown_PWM_Module(uint8_t module_number)
{
    //this function shuts down the corresponding PWM module
    
    if( 1 == module_number )
    {
        PWM_1_Stop();
    }
    else if( 2 == module_number )
    {
        PWM_2_Stop();
    }
    else if( 3 == module_number )
    {
        PWM_3_Stop();
    }
}

void Set_PWM_Period( uint16_t period, uint8_t module_number)
{
    //this function sets the period of the corresponding PWM module
    // as well as sets the compare value to half of the period
    // so that the duty cycle is 50%
    
    if( 1 == module_number )
    {
        PWM_1_WritePeriod( period );
        PWM_1_WriteCompare( period >> 1 ); //shift left 1 to divide by 2
        PWM_1_Start();
    }
    else if( 2 == module_number )
    {
        PWM_2_WritePeriod( period );
        PWM_2_WriteCompare( period >> 1 ); //shift left 1 to divide by 2
        PWM_2_Start();
    }
    else if( 3 == module_number )
    {
        PWM_3_WritePeriod( period );
        PWM_3_WriteCompare( period >> 1 ); //shift left 1 to divide by 2
        PWM_3_Start();
    }
}

void Set_PWM_Note( uint16_t freq, uint8_t module_number )
{
    //takes a desired frequency in Hz, then sets the numbered PWM module to that note.  A freq of 0 is OFF
    uint16_t period;
    
    //if freq = 0, then turn the module OFF
    if( 0 == freq )
    {
        Shutdown_PWM_Module(module_number);
    }
    else  //else then calculate and set the period for the PWM module
    {
        period = PWM_CLOCK / freq;
        
        Set_PWM_Period( period, module_number);
    }
}

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        Set_PWM_Note( 100, 1 ); //set PWM module 1 to 100Hz
        Set_PWM_Note( 50, 2 );  //set PWM module 2 to 50Hz
        Set_PWM_Note( 70, 3 );  //set PWM module 3 to 70Hz
        CyDelay(1000); 
        Set_PWM_Note( 0, 1 );   //shut down PWM module 1
        Set_PWM_Note( 0, 2 );   //shut down PWM module 2
        Set_PWM_Note( 0, 3 );   //shut down PWM module 3
        CyDelay(1000);
    }
}

/* [] END OF FILE */

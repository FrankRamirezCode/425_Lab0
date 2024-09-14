/**
 * @file main.c
 *
 * @brief Main source code for the GPIO program.
 *
 * This file contains the main entry point and function definitions for the GPIO program.
 * It interfaces with the following:
 *  - User LED (RGB) Tiva C Series TM4C123G LaunchPad
 *	- EduBase Board LEDs (LED0 - LED3)
 *	- EduBase Board Push Buttons (SW2 - SW5)
 *
 * To verify the pinout of the user LED, refer to the Tiva C Series TM4C123G LaunchPad User's Guide
 * Link: https://www.ti.com/lit/pdf/spmu296
 *
 * @author Aaron Nanas
 */
 
#include "TM4C123GH6PM.h"
#include "SysTick_Delay.h"
#include "GPIO.h"

int main(void)
{
	// Initialize the SysTick Timer used to provide a blocking delay function
	SysTick_Delay_Init();
	
	// Initialize the RGB LED (Port F)
	RGB_LED_Init();
	
	//Initialize the LEDs on the Edubase board (Port B)
	EduBase_LEDs_Init();
	
	//Initialize the buttons (SW2-SW5) on the Edubase board (Port D)
	EduBase_Button_Init();

	while(1)
	{
		uint8_t edubase_button_status = Get_EduBase_Button_Status();
		//EduBase_LEDs_Output(edubase_button_status);
		LED_Controller(edubase_button_status);
	}
}

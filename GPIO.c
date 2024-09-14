/**
 * @file GPIO.c
 *
 * @brief Source code for the GPIO driver.
 *
 * This file contains the function definitions for the GPIO driver.
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

#include "GPIO.h"
#include "TM4C123GH6PM.h"

// Constant definitions for the user LED (RGB) colors
const uint8_t RGB_LED_OFF 		= 0x00;
const uint8_t RGB_LED_RED 		= 0x02;
const uint8_t RGB_LED_BLUE 		= 0x04;
const uint8_t RGB_LED_GREEN 	= 0x08;

// Constant definitions for the EduBase board LEDs
const uint8_t EDUBASE_LED_ALL_OFF = 0x0;
const uint8_t EDUBASE_LED_ALL_ON	= 0xF;

void RGB_LED_Init(void)
{
	// Enable the clock to Port F
	SYSCTL->RCGCGPIO |= 0x20;

	// Set PF1, PF2, and PF3 as output GPIO pins
	GPIOF->DIR |= 0x0E;
	
	// Configure PF1, PF2, and PF3 to function as GPIO pins
	GPIOF->AFSEL &= ~0x0E;
	
	// Enable digital functionality for PF1, PF2, and PF3
	GPIOF->DEN |= 0x0E;
	
	// Initialize the output of the RGB LED to zero
	GPIOF->DATA &= ~0x0E;
}

void RGB_LED_Output(uint8_t led_value)
{
	// Set the output of the RGB LED
	GPIOF->DATA = (GPIOF->DATA & 0xF1) | led_value;
}

uint8_t RGB_LED_Status(void)
{
	// Assign the value of Port F to a local variable
	// and only read the values of the following bits: 3, 2, and 1
	// Then, return the local variable's value
	uint8_t RGB_LED_Status = GPIOF->DATA & 0x0E;
	return RGB_LED_Status;
}

void EduBase_LEDs_Init(void)
{
	// Enable the clock to Port B
	SYSCTL->RCGCGPIO |= 0x02;

	// Set PF1, PF2, and PF3 as output GPIO pins
	GPIOB->DIR |= 0x0F;
	
	// Configure PB0, PB1, PB2, and PB3 to function as GPIO pins
	GPIOB->AFSEL &= ~0x0F;
	
	// Enable digital functionality for PB0, PB1, PB2, and PB3
	GPIOB->DEN |= 0x0F;
	
	// Initialize the output of the RGB LED to zero
	GPIOB->DATA &= ~0x0F;
}

void EduBase_LEDs_Output(uint8_t led_value)
{
	//Set the output of the LEDs
	GPIOB->DATA = (GPIOB ->DATA & 0xF0) | led_value;
}

void EduBase_Button_Init(void)
{
	//Enable the clock to port D
	SYSCTL->RCGCGPIO |= 0x08;
	
	// Set PD0-PD3 as input GPIO pins
	GPIOD->DIR &= ~0x0F;
	
	// Config PD0-PD3 to function as GPIO pins
	GPIOD->AFSEL &= ~0x0F;
	
	//Enable digital functionality for PD0-PD3
	GPIOD->DEN |= 0x0F;
}

uint8_t Get_EduBase_Button_Status(void)
{
	//Assign the value of Port D to a local var
	//and only read the values of bits: 3,2,1,0
	//Then return local var value
	uint8_t button_status = GPIOD->DATA & 0x0F;
	return button_status;
}

/**
* @brief Binary_Up_Counter sets the LED to green and then starts a binary counter on the boards LEDs. 
*	It starts from 0 and then rises to 15, delaying 200 ms inbetween. Sequence stops if SW5 is not pressed or if it concludes through
*	 the for loop
* @param button_status an uint8_t represents the status of the board buttons. Its then used to set up the LED pattern
* @return None
**/
void Binary_Up_Counter(void)
{
	RGB_LED_Output(RGB_LED_GREEN);
	
	for (int led_count = 0; led_count <= 0x0F; led_count++)
	{
		EduBase_LEDs_Output(led_count);
		SysTick_Delay1ms(200);
		uint8_t button_status = Get_EduBase_Button_Status();
		if(button_status != 0x01)
		{
			break;
		}
	}
}

/**
* @brief Binary_Down_Counter sets the LED to green and then starts a binary counter on the boards LEDs. 
*	It starts from 15 and then descends to 0, delaying 200 ms inbetween. Sequence stops if SW4 is not pressed or if it concludes through
*	 the for loop
* @param button_status an uint8_t represents the status of the board buttons. Its then used to set up the LED pattern
* @return None
**/
void Binary_Down_Counter(void)
{
	RGB_LED_Output(RGB_LED_GREEN);
	
	for (int led_count = 0x0F; led_count >= 0x00; led_count --)
	{
		EduBase_LEDs_Output(led_count);
		SysTick_Delay1ms(200);
		uint8_t button_status = Get_EduBase_Button_Status();
		if(button_status != 0x02)
		{
			break;
		}
	}
}

void Ring_Counter(void)
{
	RGB_LED_Output(RGB_LED_BLUE);
	
	for (int i = 1; i <= 8 ; i  = i*2)
	{
		EduBase_LEDs_Output(i);
		SysTick_Delay1ms(200);
		uint8_t button_status = Get_EduBase_Button_Status();
		if(button_status != 0x04)
		{
			break;
		}
	}
}

void Reverse_Ring_Counter(void)
{
	RGB_LED_Output(RGB_LED_BLUE);
	
	for (int i = 8; i >= 1 ; i = i / 2)
	{
		EduBase_LEDs_Output(i);
		SysTick_Delay1ms(200);
		uint8_t button_status = Get_EduBase_Button_Status();
		if(button_status != 0x08)
		{
			break;
		}
	}
}

/** LED_Controller selects and executes an LED pattern based on the status of the board buttons.
* @param button_status an uint8_t represents the status of the board buttons. Its then used to set up the LED pattern
* @return None
**/
void LED_Controller(uint8_t button_status)
{
    switch(button_status)
    {
        // No buttons are pressed
        case 0x00:
        {
            RGB_LED_Output(RGB_LED_OFF);
            EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
        }
        break;

        // SW5 is pressed
        case 0x01:
        {
            Binary_Up_Counter();
        }
        break;

        // SW4 is pressed
        case 0x02:
        {
            Binary_Down_Counter();
        }
        break;

        // SW3 is pressed
        case 0x04:
        {
						Ring_Counter();
        }
        break;

        // SW2 is pressed
        case 0x08:
        {
					Reverse_Ring_Counter();
        }
        break;

        default:
        {
            RGB_LED_Output(RGB_LED_OFF);
            EduBase_LEDs_Output(EDUBASE_LED_ALL_OFF);
        }
    }
}


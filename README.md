# 425_Lab0 - GPIO Lab
Lab covering GPIO for the Tiva TM4C123GH6PM

We interface with the following:
- RGB LED of the TM4C123G LaunchPad
- EduBase Board Push Buttons (SW2 - SW5)
- EduBase Board LEDs (LED0 - LED3)

We begin with the initiation of specific ports needed to interface with the peripherals onboard the EduBaseV2. The current layout has the Push Buttons assigned to Port D, and the LEDS are assigned to Port B. The LED's on the Tiva LaunchPad are utilized as well, and these are assigned to Port F. 

These ports have to go through a few steps to be used in this Lab. They are as follows:
Port B is used as an example

* Enabling the Clock to the Port
	SYSCTL->RCGCGPIO =| 0x02;
* Setting the Port as either an input or output
	GPIOB->DIR |= 0x0F; //Output in this example
* Configuring the pins to be used as GPIO (as they can have other purposes aside from IO)
	GPIOB->AFSEL &= ~0x0F;
* Enabling digital functionality to the pins
	GPIOB->DEN |= 0x0F;
* Initialize the pins output to zero
	GPIOB->DATA &= ~0x0F;


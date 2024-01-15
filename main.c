
#ifndef F_CPU					
#define F_CPU 1000000UL			// define it now as 1 MHz unsigned long
#endif

#include <avr/io.h>				
#include <util/delay.h>		
#include <avr/interrupt.h>

#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit)))

volatile uint8_t button_pressed;

int main(void) {
	button_pressed = 0;
	PCICR = (1 << PCIE1);     // Enable pin change interrupt for PCINT14 to PCINT8
    PCMSK1 = (1 << PCINT13);  // Enable PCINT13 interrupt
	
	sei();				


	DDRC &= ~(1 << PC5);	// set PC5 for input
	DDRD = 0xFF;			// all pin d set for output
	PORTC |= (1 << PC5);		// set PC5 internal pull-up resistor
    while (1) {
		if(button_pressed){
			PORTD^=(1 << PD1) | (1 << PD3) | (1 << PD5) | (1 << PD7);
			_delay_ms(250);
			PORTD^=(1 << PD0) | (1 << PD2) | (1 << PD4) | (1 << PD6);
			}
		else{
			PORTD = 0xFF;
		}
	}
	return(0);					
}

ISR(PCINT1_vect) {
	_delay_ms(40);
	if(BIT_IS_CLEAR(PINC, PC5)) {			// if switch is pressed
		button_pressed = !button_pressed;
	}
		else{}
}



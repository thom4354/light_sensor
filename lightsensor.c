#include <avr/io.h>
#include <avr/interrupt.h>

static volatile uint8_t lux_reading = 0;

ISR(TWI_vect){
	//Read ADCH
	lux_reading = ADCH;
	
	//Send data over I2C
	TWDR = lux_reading;
	TWCR |= 0b10000000;
}



int main(void){
	//Set up I2C and ADC
	TWCR |= 0b11000101;
	ADMUX |= 0b01100111;
	ADCSRA |= 0b11100111;

	//Enable interrupts and loop forever
	sei();
	while(1);
	return 0;
}


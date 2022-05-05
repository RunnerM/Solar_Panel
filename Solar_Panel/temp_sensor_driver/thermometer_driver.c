/*
 * thermometer_driver.c
 *
 * Created: 2022-05-05 2:03:15 PM
 *  Author: pente
 */ 


#include "thermometer_driver.h"

#include <avr/interrupt.h>

static void (*on_done_cb)(uint16_t);

void init_thermometer(void) {

	PRR0 &= ~(_BV(PRADC) | _BV(PRTIM1)) ;

	//Setting the voltage reference (5V)
	ADMUX |= _BV(REFS0);

	//Adjust result to left
	ADMUX |= _BV(ADLAR);

	DDRK &= ~(_BV(PK7));
	DIDR0 |= _BV(ADC0D);

	//Input Channel Selection ADC15 - 
	//MUX5..0 -> 100111
	ADMUX |= _BV(MUX2) | _BV(MUX1); // | _BV(MUX0);
	ADCSRB |= _BV(MUX5);

	//Selecting ADC prescaler - Set out the frequency ADC clock
	ADCSRA |= _BV(ADPS0) | _BV(ADPS1) | _BV(ADPS2);

	//ADATE - Enable Auto Trigger
	ADCSRA |= _BV(ADATE);

	//ADIE - Interrupt Enable
	ADCSRA |= _BV(ADIE);

	//ADEN - Turn on Analog Digital Converter
	ADCSRA |= _BV(ADEN);
}

void thermometer_set_on_done_cb(void (*cb)(uint16_t)) {
	on_done_cb = cb;
}

void thermometer_measure(void) {
	// start conversion
	ADCSRA |= _BV(ADSC);
}

ISR(ADC_vect) {
	uint8_t analog = ADCH;
	on_done_cb(analog);
}

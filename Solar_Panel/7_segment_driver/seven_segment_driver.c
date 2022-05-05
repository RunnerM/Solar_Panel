/*
 * seven_segment_driver.c
 *
 * Created: 2022-04-01 9:07:31 AM
 *  Author: pente
 */ 


#include "seven_segment_driver.h"
volatile uint8_t digit_counter;

uint8_t first_digit = 0b11111111;
uint8_t second_digit = 0b11111111;
uint8_t third_digit = 0b11111111;
uint8_t fourth_digit = 0b11111111;
uint8_t numbers[] = {ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE};


void init_display(){
	OCR4A = 8192;  //240HZ ==> 60/digit
	TCCR4B |= _BV(WGM42);// Setting the timer to CTC mode.
	TCCR4B |= _BV(CS41);// Prescaler 8
	TCCR4A |= _BV(COM4A0);//Output compare match
	TIMSK4 |= _BV(OCIE4A);//Enabling the mask of the timer.
	//Set Up SPI 
	DDRB |= 1 << 0| 1 << 1 | 1 << 2;
	DDRF |=  1 << 0| 1 << 1 | 1 << 2 | 1 << 3;
	
	//data order, leading edge, 
	SPCR &= ~(1 << DORD | 1 << CPHA);
	// Master and enable, polarity rising edge. (Turn off SPI interrupt if turned on it breakers control.)
	SPCR |= 1 << MSTR | 1 << SPE | 1 << CPOL /*| 1 << SPIE */| 1 << DORD;
	//SPI speed CLK/2
	SPCR &= ~(1 << SPR1 | 1 << SPR0);
	//SPSR |= 1 << SPI2X;

	PORTB &= ~(1 << PB0);
	PORTF |= 1 << 0| 1 << 1 | 1 << 2 | 1 << 3;
}
void printint_4u(uint16_t value){
	if(value/1000==0)
		first_digit=BLANK;
	else
		first_digit = numbers[value/1000];
		
	if ((value/1000==0) & (value%1000/100==0))
		second_digit=BLANK;
	else
		second_digit = numbers[(value%1000/100)];
	
	if((value/1000==0) & (value%1000/100==0) & (value%100/10==0))
		third_digit=BLANK;
	else
		third_digit = numbers[(value%100/10)];
	if((value/1000==0) & (value%1000/100==0) & (value%100/10==0) & (value%10/1==0))
		third_digit=BLANK;
	else
		fourth_digit = numbers[(value%10/1)];
		
	if (value==0)
		fourth_digit=ZERO;
}


ISR(TIMER4_COMPA_vect){
	//turn off previous turn on next.
	if(digit_counter==0)
		PORTF |=  1 << 3;
	else
		PORTF |=  1 << (digit_counter-1);
	
	PORTB |= 1 << PB0;//store pulse.
	PORTB &= ~(1 << PB0);
	PORTF &=  ~(1 << digit_counter);
	switch (digit_counter)
	{
			case 0:
				SPDR = second_digit;
				digit_counter++;
				break;
			case 1:
				SPDR = third_digit;
				digit_counter++;
				break;
			case 2:
				SPDR = fourth_digit;
				digit_counter++;
				break;
			case 3:
				SPDR = first_digit;
				digit_counter = 0;
				break;
	}	
}

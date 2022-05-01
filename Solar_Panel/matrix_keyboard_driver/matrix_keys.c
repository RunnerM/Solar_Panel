/*
 * matrix_keys.c
 *
 * Created: 2022-04-29 8:36:54 AM
 *  Author: pente
 */ 
#include <avr/io.h>

typedef struct key_matrix_descr_t
{
	volatile uint8_t* ddr_row;
	volatile uint8_t* pin_row;
	volatile uint8_t* port_row;
	uint8_t bit_row;
	volatile uint8_t* ddr_col;
	volatile uint8_t* pin_col;
	volatile uint8_t* port_col;
	uint8_t bit_col;
} key_matrix_descr_t;

uint8_t key_pressed_flag;

//Port map:
/*

T0 - PD7
OC0B - PG5
OC1B - PB6
OC2B - PH6

OC3B - PE4
ICP4 - PL4
OC4B - PH4
T5 - PL2

*/
static key_matrix_descr_t key_desc[] = {
	//First row
	{&DDRD, &PIND, &PORTD, PD7, &DDRE, &PINE, &PORTE, PE4},	// 1
	{&DDRD, &PIND, &PORTD, PD7, &DDRL, &PINL, &PORTL, PL4},	// 2
	{&DDRD, &PIND, &PORTD, PD7, &DDRH, &PINH, &PORTH, PH4},	// 3
	{&DDRD, &PIND, &PORTD, PD7, &DDRL, &PINL, &PORTL, PL2},	// A
	//Second row
	{&DDRG, &PING, &PORTG, PG5, &DDRE, &PINE, &PORTE, PE4},	// 4
	{&DDRG, &PING, &PORTG, PG5, &DDRL, &PINL, &PORTL, PL4},	// 5
	{&DDRG, &PING, &PORTG, PG5, &DDRH, &PINH, &PORTH, PH4},	// 6
	{&DDRG, &PING, &PORTG, PG5, &DDRL, &PINL, &PORTL, PL2},	// B
	//Third row
	{&DDRB, &PINB, &PORTB, PB6, &DDRE, &PINE, &PORTE, PE4},	// 7
	{&DDRB, &PINB, &PORTB, PB6, &DDRL, &PINL, &PORTL, PL4},	// 8
	{&DDRB, &PINB, &PORTB, PB6, &DDRH, &PINH, &PORTH, PH4},	// 9
	{&DDRB, &PINB, &PORTB, PB6, &DDRL, &PINL, &PORTL, PL2},	// C
	//Forth row
	{&DDRH, &PINH, &PORTH, PH6, &DDRE, &PINE, &PORTE, PE4},	// *
	{&DDRH, &PINH, &PORTH, PH6, &DDRL, &PINL, &PORTL, PL4},	// 0
	{&DDRH, &PINH, &PORTH, PH6, &DDRH, &PINH, &PORTH, PH4},	// #
	{&DDRH, &PINH, &PORTH, PH6, &DDRL, &PINL, &PORTL, PL2},	// D
};

char key_value[16] = {'1','2','3','A','4','5','6','B','7','8','9','C','*','0','#','D'};


void init_matrix_keyboard(){
	// Initialize input-pin for keys
	for(uint8_t i=0; i<16; i++)
	{
		// Initialize Data Direction Register for each key col pin (input)
		*(key_desc[i].ddr_col) &= ~_BV(key_desc[i].bit_col);
		
		// Enable Pull-ups on each key input
		*(key_desc[i].port_col) |= _BV(key_desc[i].bit_col);
		
		// Initialize Data Direction Register for each key row pin. (output)
		*(key_desc[i].ddr_row) |= _BV(key_desc[i].bit_row);
		// Set every row to 1 initially
		*(key_desc[i].pin_row) |= _BV(key_desc[i].bit_row);
	}
}

char getxkey(){
	for (uint8_t j=0; j<16; j++)
	{
		//activate row
		*(key_desc[j].pin_row) |= _BV(key_desc[j].bit_row);
		//read column
		key_pressed_flag = (*(key_desc[j].pin_col) & _BV(key_desc[j].bit_col))==0;
		//deactivate row
		*(key_desc[j].pin_row) &= ~_BV(key_desc[j].bit_row);
		if(key_pressed_flag){
			return key_value[j];
		}	
	}
}

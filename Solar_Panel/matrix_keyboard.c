
#include "matrix_keyboard.h"

#include <stdint.h>
#include <avr/io.h>

#define ROWS 4
#define COLS 4

#define NONE -1

static uint8_t keys[4][4] = {
	{ 1,	2,	3,	A },
	{ 4,	5,	6,	B },
	{ 7,	8,	9,	C },
	{ STAR,	0,	HASH,	D }
};

int pressedColumn();

void matrix_keyboard_init(void) {

	// WHO TF DESIGNED THIS FCK PIECE OF SHIT SHIELD??? none of these ports are in any order, complete bullshit, i have to hardcode all that shit now

	// configure rows as outputs
	DDRD |= _BV(PD7);
	DDRG |= _BV(PG5);
	DDRB |= _BV(PB6);
	DDRH |= _BV(PH6);

	// set rows to HIGH
	PORTD |= _BV(PD7);
	PORTG |= _BV(PG5);
	PORTB |= _BV(PB6);
	PORTH |= _BV(PH6);

	// configure columns as inputs
	DDRE &= ~(_BV(PE4));
	DDRL &= ~(_BV(PL0));
	DDRH &= ~(_BV(PH4));
	DDRL &= ~(_BV(PL2));

	// enable pullup resistors
	PORTE |= _BV(PE4);
	PORTL |= _BV(PL0);
	PORTH |= _BV(PH4);
	PORTL |= _BV(PL2);
}

int8_t matrix_keyboard_get_key() {
	// fuck u

	PORTD &= ~(_BV(PD7));
	int c = pressedColumn();
	PORTD |= _BV(PD7);

	if(NONE != c)
		return keys[0][c];

	PORTG &= ~(_BV(PG5));
	c = pressedColumn();
	PORTG |= _BV(PG5);

	if(NONE != c)
		return keys[1][c];

	PORTB &= ~(_BV(PB6));
	c = pressedColumn();
	PORTB |= _BV(PB6);

	if(NONE != c)
		return keys[2][c];

	PORTH &= ~(_BV(PH6));
	c = pressedColumn();
	PORTH |= _BV(PH6);

	if(NONE != c)
		return keys[3][c];

	return NONE;
}

int pressedColumn() {
	if(~PINE & _BV(PE4))
		return 0;

	else if(~PINL & _BV(PL0))
		return 1;

	else if(~PINH & _BV(PH4))
		return 2;

	else if(~PINL & _BV(PL2))
		return 3;

	return NONE;
}

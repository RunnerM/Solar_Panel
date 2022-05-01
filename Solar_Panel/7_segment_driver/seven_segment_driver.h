/*
 * seven_segment_driver.h
 *
 * Created: 2022-04-01 9:07:06 AM
 *  Author: pente
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>

#ifndef SEVEN_SEGMENT_DRIVER_H_
#define SEVEN_SEGMENT_DRIVER_H_

#define ZERO  0b00000011
#define ONE  0b10011111
#define TWO  0b00100101
#define THREE  0b00001101
#define FOUR  0b10011001
#define FIVE  0b01001001
#define SIX  0b01000001
#define SEVEN  0b00011111
#define EIGHT  0b00000001
#define NINE  0b00001001
#define DOT  0b11111110
#define BLANK 0b11111111

void init_display();
void printint_4u(uint16_t value);

#endif /* SEVEN_SEGMENT_DRIVER_H_ */
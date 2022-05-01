/*
 * Solar_Panel.c
 *
 * Created: 2022-04-29 8:22:49 AM
 * Author : pente
 */ 

#include <avr/io.h>
#include "7_segment_driver/seven_segment_driver.h"
#include "matrix_keyboard_driver/matrix_keys.h"

int key;


int main(void)
{
	cli();
	init_matrix_keyboard();
	init_display();
	printint_4u(0);
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		for (int i= 9999;i>0;i--)
		{
			printint_4u(i);
			key=0;
			while (key<10000)
			{
				key++;
			}
		}
	}
}


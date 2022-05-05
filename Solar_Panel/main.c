/*
 * Solar_Panel.c
 *
 * Created: 2022-04-29 8:22:49 AM
 * Author : pente
 */ 

#include <avr/io.h>
#include "7_segment_driver/seven_segment_driver.h"
#include "matrix_keyboard_driver/matrix_keys.h"
#include "key_driver/key_driver_abstract.h"
#include "led_driver/led_driver.h"
#include "temp_sensor_driver/thermometer_driver.h"

typedef enum {
	LOW_STATE,
	HIGH_STATE, 
	TEMP_STATE,
} state_t;

//types and const variables;
typedef struct ascci_key_t
{
	char key;
	uint8_t value;
} ascci_key_t;
static const ascci_key_t ascii_map[10] = {
	{'1',1},
	{'2',2},
	{'3',3},
	{'4',4},
	{'5',5},
	{'6',6},
	{'7',7},
	{'8',8},
	{'9',9},
	{'0',0}
};


//global variables
uint16_t keyx;
uint8_t key;
uint8_t value;
uint8_t low=20;
uint8_t high=30;
uint8_t low_saved=20;
uint8_t high_saved=30;
uint8_t current_temp=25;

state_t state=TEMP_STATE;

//props
uint8_t ascii_mapper(char key);

uint8_t ascii_mapper(char key){
	for (int i = 0;i<10;i++){
		if (key== ascii_map[i].key)
		{
			return ascii_map[i].value;
		}
	}
	return 0;
}

void term_result_handler(uint16_t result){
	current_temp=result;
}


int main(void)
{
	cli();
	init_matrix_keyboard();
	init_display();
	init_keys();
	init_leds();
	init_thermometer();
	thermometer_set_on_done_cb(term_result_handler);
	sei();
	
    /* Replace with your application code */
    while (1) 
    {
		if(scan_key()==1){
			low=low_saved;
			state=LOW_STATE;
		}
		if(scan_key()==2){
			high=high_saved;
			state=HIGH_STATE;
		}
		
		if (scan_key()==3)
		{
			low=low_saved;
			high=high_saved;
			state=TEMP_STATE;
		}
			
		key=getxkey();
		if ((LOW_STATE==state) & (key!='@'))
		{
			if(low==low_saved){
				low=key;
			}else{
				low=(low*10)+ascii_mapper(key);
			}
		}
		
		if ((HIGH_STATE==state) & (key!='@'))
		{
			if(high==high_saved){
				high=key;
			}else{
				high=(high*10)+ascii_mapper(key);
			}
		}
		if (key=='*')
		{
			low=low_saved;
			high=high_saved;
			state=TEMP_STATE;
		}
		if (key=='#')
		{
			low_saved=low;
			high_saved=high;
			state=TEMP_STATE;
		}
		
		if(state==HIGH_STATE){
			printint_4u(high);
		}
		if (state==LOW_STATE)
		{
			printint_4u(low);
		}
		if(state==TEMP_STATE){
			printint_4u(current_temp);
		}
		
		thermometer_measure();
		
		if(current_temp<low_saved)
			lightbar(0);
		if(current_temp>high_saved)
			lightbar(1);
		
		for (int i=0; i<30000;i++)
		{}
	}
}



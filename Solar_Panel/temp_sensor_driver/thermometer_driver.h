/*
 * thermometer_driver.h
 *
 * Created: 2022-05-05 2:03:15 PM
 *  Author: pente
 */ 
#include <avr/io.h>
#ifndef THERMOMETER_DRIVER_H_
#define THERMOMETER_DRIVER_H_

void init_thermometer(void);

void thermometer_set_on_done_cb(void (*cb)(uint16_t result));

void thermometer_measure(void);

#endif /* THERMOMETER_DRIVER_H_ */

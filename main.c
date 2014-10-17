/*
 * main.c
 *
 *  Created on: Oct 13, 2014
 *      Author: jcobb
 */

// BUG FOR MISSING SYMBOLS
// https://bugs.eclipse.org/bugs/show_bug.cgi?id=364227


#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>
#include "pwm.h"

uint8_t duty_cycle = 0;



int main() {

	pwm_init();

	while (1) {

		pwm_tick();

		PORTB ^= ~(1 << PB0);
		_delay_ms(100);

	}

	return 0;
}


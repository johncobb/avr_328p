/*
 * pwm.c
 *
 *  Created on: Oct 13, 2014
 *      Author: jcobb
 */

#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>


void pwm_init()
{
	DDRB |= _BV(PB0);

	OCR0A = 128;

	TCCR0A |= _BV(COM0A1);
	TCCR0A |= _BV(WGM01) | _BV(WGM00);

	TCCR0B |= _BV(CS01);
}

void pwm_tick()
{

}


ISR(PCINT0_vect)
{

}

/*
 * twi.c
 *
 *  Created on: Oct 14, 2014
 *      Author: jcobb
 */

#include <avr/io.h>
#include <util/twi.h>
#include "twi.h"

void twi_init()
{
	// Set SCL to 400 kHz
	TWSR = 0x00;
	TWBR = 0x0c;
	// TWI Enable
	TWCR = _BV(TWEN);

}

void twi_start()
{
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	while((TWCR & _BV(TWINT)) == 0);
}

void twi_tick()
{

}

void twi_stop()
{
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void twi_write(uint8_t data)
{
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	while ((TWCR & _BV(TWINT)) == 0);
}

uint8_t twi_read_ack()
{
	TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	while ((TWCR & _BV(TWINT)) == 0);

	return TWDR;

}

uint8_t twi_read_nack()
{
	TWCR = _BV(TWINT) | _BV(TWEN);
	while((TWCR & _BV(TWINT)) == 0);

	return TWDR;
}

uint8_t twi_get_status()
{
	uint8_t status;
	// mask status
	status = TWSR &TW_NO_INFO;
	return status;
}

uint8_t twi_write_byte(uint8_t address, uint8_t data)
{
    twi_start();
    if (twi_get_status() != TW_START)
        return ERROR;
    //select device address
    twi_write(TWIADDRESS);
    if (twi_get_status() != TW_MT_DATA_ACK)
        return ERROR;
    //write byte
    twi_write(data);
    if (twi_get_status() != TW_MT_DATA_ACK)
        return ERROR;
    twi_stop();
    return SUCCESS;
}

uint8_t twi_read_byte(uint8_t address, uint8_t *data)
{
	twi_start();
    if (twi_get_status() != TW_START)
        return ERROR;
    //select device address
    twi_write(address);
    if (twi_get_status() != TW_MT_DATA_ACK)
        return ERROR;
    // send start
    twi_start();
    if(twi_get_status() != TW_REP_START)
    	return ERROR;
    // select device and send read bit
    twi_write(address | TW_READ);
    if(twi_get_status() != TW_MR_SLA_ACK)
    	return ERROR;
    *data = twi_read_nack();
    if(twi_get_status() != TW_MR_DATA_NACK)
    	return ERROR;
    twi_stop();

    return SUCCESS;



}

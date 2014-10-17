/*
 * twi.h
 *
 *  Created on: Oct 14, 2014
 *      Author: jcobb
 */

#ifndef TWI_H_
#define TWI_H_

// http://www.atmel.com/Images/doc2564.pdf
// SCL Frequency = CPU CLOCK/(16+2(TWBR)*4^TWPS
// AVR315 Page 4
// TWBR Value of TWI Bit rate register
// TWPS Value of prescalar bits in TWI status register


// Clock frequency AVR315 Page 5
// 8 MHz @ 400 kHz TWBR = 2 TWPS = 0
// 8 MHz @ 100 kHz TWBR = 32 TWPS = 0

#define SUCCESS 0x00
#define ERROR 	0xff
#define TWIADDRESS 0b10100000


void twi_init();
void twi_start();
void twi_tick();
void twi_stop();
void twi_write(uint8_t data);
uint8_t twi_read_ack();
uint8_t twi_read_nack();
uint8_t twi_get_status();

uint8_t twi_write_byte(uint8_t address, uint8_t data);
uint8_t twi_read_byte(uint8_t address, uint8_t *data);

#endif /* TWI_H_ */

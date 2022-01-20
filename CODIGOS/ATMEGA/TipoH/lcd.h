/*
 * LCD16X2.h
 *
 * Created: 28/07/2019 21:12:02
 *  Author: Marlon
 */ 


#ifndef LCD16X2_H_
#define LCD16X2_H_

#include <avr/io.h>
#include <util/delay.h>

#define LCD_INST	0
#define LCD_DATA	1

// INSTRUCCIONES
#define LINEA1		0x80
#define LINEA2		0xC0
#define LINEA3		0x94
#define LINEA4		0xD4
#define CLEAR		0x01

// FUNCIONES B�SICAS
void lcd_start();
void lcd_write(uint8_t type, uint8_t inst_data);
void lcd_init();

// FUNCIONES COMPUESTAS
void lcd_print(char *s);

#endif /* LCD16X2_H_ */

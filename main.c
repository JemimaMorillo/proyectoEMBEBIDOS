#define F_CPU 16000000UL
#define BAUD 9600

#ifndef MAX
#define MAX 100
#endif

#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "DEF_ATMEGA328P.h"
#include "UART.h"
#include "LCD.h"
#include "DHT22.h"


int main(void)
{     
	char printbuff[10];
        char printbuff_2[10];
	float temperatura;
	float humedad;
	DDRB |= (1<<3);	//Pin como salida
	                          
	uint8_t contador=200;
	serial_begin();
	LCD_init();

	DHT22_init();
	
    while (1) 
    {	
		contador++;
		if(contador>=200){			//Para leer el DHT22 cada 200x10ms = 2000ms y no utilizar retardos bloqueantes de 2s
			contador=0;
			
			uint8_t status = DHT22_read(&temperatura, &humedad);
			if (status)
			{
			    if (    ( (37.5<temperatura) && (temperatura<38.5)) && ( (58<humedad) && (humedad<60))   ){	
				  
	                           PORTB &= ~ (1<<3);	//Nivel alto
				   LCD_clear();
				   LCD_printf(" Temp. ");
				   dtostrf(temperatura, 2, 2, printbuff);
				  
			           LCD_printf(printbuff);
				   LCD_printf(" C");
				   
				   LCD_segunda_linea();
				   LCD_printf(" Hume. ");
			          
				   dtostrf(humedad, 2, 2, printbuff_2);
				   
			           LCD_printf(printbuff_2);
				   LCD_printf(" %");
			       
			       
			           char buffer[MAX];
                                   strcat(strcpy(buffer, printbuff), ",");
			           strcat(buffer, printbuff_2);
				    strcat(buffer, ",");
			           strcat(buffer, "0"); 
			           _delay_ms(200);
				   enviar2raspi2(buffer);
				    
				
			       
			} else{  
			       
	                           PORTB |= (1<<3);	//Nivel alto
			           
			           LCD_clear();
				   LCD_printf(" PELIGRO!!! ");
			           LCD_segunda_linea();
				    
			           dtostrf(temperatura, 2, 2, printbuff);
			           serial_println_str(printbuff); 
				   LCD_printf(printbuff);
				   LCD_printf("C  ");
				   dtostrf(humedad, 2, 2, printbuff_2);
			           serial_println_str(printbuff_2); 
				   LCD_printf(printbuff_2);
				   LCD_printf(" %");
			            
			           char buffer[MAX];
                                   strcat(strcpy(buffer, printbuff), ",");
			           strcat(buffer, printbuff_2);
			           strcat(buffer, ",");
			           strcat(buffer, "1"); 
			         _delay_ms(200);
			           enviar2raspi2(buffer);
			   
			   }
			
			}
			else
			{
				LCD_clear();
				LCD_printf("Error");
				printf("ERROR\n\r");
			}
		
		}else{
			_delay_ms(10);
			
		}		
    }
}

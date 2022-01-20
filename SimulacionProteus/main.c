#define MAX_STR 50
#define BAUD 9600
#ifndef MAX
#define MAX 100
#endif

#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "uart.h"
#include "lcd.h"
#include "dht22.h"



int main(void)
{        
	char printbuff[10];       //Se crean una lista de caracteres que almacenara los bits de de temperatura y humedad captados por el sensor
        char printbuff_2[10];
	float temperatura;    //creacion de vairabels flotantes que nos permitira visualizar la informacion de forma numerica
	float humedad;
	DDRB |= (1<<3);	//Pin como salida
        DDRB |= (1<<4);	//Pin como salida
	                          
	uint8_t contador=200;
	serial_begin();
	DHT22_init();
        lcd_init();

	
	
    while (1) 
    {	
		contador++;
		if(contador>=200){			//Para leer el DHT22 cada 200x10ms = 2000ms y no utilizar retardos bloqueantes de 2s
			contador=0;
			
			uint8_t status = DHT22_read(&temperatura, &humedad);
			if (status)
			{
			    if (    ( (37.5<temperatura) && (temperatura<38.5)) && ( (58<humedad) && (humedad<60))   ){	
				  
	                           PORTB &= ~ (1<<5);	//NiveL BAJO
			           PORTB &= ~ (1<<6);	//NiveL BAJO
				   lcd_write(LCD_INST, CLEAR);
			           
				   lcd_print(" Temp. ");
				   dtostrf(temperatura, 2, 2, printbuff);
				  
			           lcd_print(printbuff);
				   lcd_print(" C");
				   
				  lcd_write(LCD_INST, LINEA2);
				   lcd_print(" Hume. ");
			          
				   dtostrf(humedad, 2, 2, printbuff_2);
				   
			           lcd_print(printbuff_2);
				   lcd_print(" %");
			       
			       
			           char buffer[MAX];
                                   strcat(strcpy(buffer, printbuff), ",");
			           strcat(buffer, printbuff_2);
				    strcat(buffer, ",");
			           strcat(buffer, "0"); 
			           _delay_ms(200);
				   enviar2raspi2(buffer);
				    
				
			       
			} else{  
			       
	                           PORTB |= (1<<5);	//Nivel alto
			           PORTB |= (1<<6);	//Nivel alto
			           
			           lcd_write(LCD_INST, CLEAR);
				   lcd_print(" PELIGRO!!! ");
			           lcd_write(LCD_INST, LINEA2);
				    
			           dtostrf(temperatura, 2, 2, printbuff);
			           serial_println_str(printbuff); 
				   lcd_print(printbuff);
				   lcd_print("C  ");
				   dtostrf(humedad, 2, 2, printbuff_2);
			           serial_println_str(printbuff_2); 
				   lcd_print(printbuff_2);
				   lcd_print(" %");
			            
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
				  lcd_write(LCD_INST, CLEAR);
				lcd_print("Error");
				printf("ERROR\n\r");
			}
		
		}else{
			_delay_ms(10);
			
		}		
    }
}


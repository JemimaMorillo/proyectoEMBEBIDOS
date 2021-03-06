#include "uart.h"

#define MAX_STR 50
#define BAUD 9600
/******************************************************************************************************************************/
/*                                                Funciones privadas o internas de la libreria						*/
/******************************************************************************************************************************/
volatile unsigned char rx_buffer[MAX_STR] = {0};
volatile unsigned char current_size = 0;
bool isReady = false;





void serial_begin(){
	cli();
	float valor_UBBR0 = 0;
	UCSR0A=0b00000010;	//el bit 1 (U2X0) se pone en uno para duplicar la velocidad y poder utilizar frecuencias desde 1MHz
	UCSR0B=0b10011000;	//habilitar interrupcion por recepcion / transmisiÃ³n y recepciÃ³n habilitados a 8 bits
	UCSR0C=0b00000110;	//asÃ­ncrono, sin bit de paridad, 1 bit de parada a 8 bits
	valor_UBBR0 = F_CPU/(16.0*BAUD);	//Definir la constante BAUD al inicio del cÃ³digo
        if(UCSR0A & (1<<U2X0)) valor_UBBR0 *= 2;
	UBRR0=valor_UBBR0 - 1;
        sei();
}

unsigned char serial_read_char(){
	if(UCSR0A&(1<<7)){  //si el bit7 del registro UCSR0A se ha puesto a 1
		return UDR0;    //devuelve el dato almacenado en el registro UDR0
	}
	else//sino
	return 0;//retorna 0
}

void serial_print_char(unsigned char caracter){
        if(caracter==0) return;
	while(!(UCSR0A&(1<<5)));    // mientras el registro UDR0 esté lleno espera
	UDR0 = caracter;            //cuando el el registro UDR0 está vacio se envia el //caracter
}

void serial_print_str(char *cadena){	//cadena de caracteres de tipo char
	while(*cadena !=0x00){			//mientras el último valor de la cadena sea diferente
							        //al caracter nulo
		serial_print_char(*cadena);	//transmite los caracteres de cadena
		cadena++;				//incrementa la ubicación de los caracteres en cadena
								//para enviar el siguiente caracter de cadena
	}
}

void serial_println_str(char *cadena){
	serial_print_str(cadena);
	serial_print_char('\r');
	serial_print_char('\n');
}




void enviar2raspi2(char *cadena){
_delay_ms(1500);
serial_println_str(cadena);     
}

void init_pins(){
DDRB |= ((1 << DDB5)); //asignar a puerto b5 como salida//pin 13 de arduino 
DDRB |= ((1 << DDB3)); //asignar a puerto b3 como salida//pin 11 de arduino 
DDRB |= ((1 << DDB2)); //asignar a puerto b2 como salida//pin 10 de arduino 
}



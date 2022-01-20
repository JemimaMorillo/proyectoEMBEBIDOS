#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

void DHT22_init(void);
uint8_t  DHT22_read(float *dht_temperatura, float *dht_humedad);
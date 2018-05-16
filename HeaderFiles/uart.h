#ifndef DEF_USART
#define DEF_USART

#include <avr/io.h>
#include "../HeaderFiles/constants.h"

void setup_UART();
char recieve_UART();
//void transmit_UART(unsigned int data)

#endif

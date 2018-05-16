#include "../HeaderFiles/uart.h"


void setup_UART() {
  //setting the BAUD rate
  UBRR1H = (unsigned char)(BAUD_RATE>>8);
  UBRR1L = (unsigned char)BAUD_RATE;

	//Asynchronous or Synchronous mode for USART protocol
	//Synchronous (UMSEL11=1) of asynchronous (UMSEL11=0)
	//Datasheet p.178 - 19.2
	UCSR1C &= ~_BV(UMSEL11);

	//Double or single speed (asynchronous mode only)
	//Hier hopelijk op single speed?
	//Datasheet p.178 - 19.2
	UCSR1A &= ~_BV(U2X1);

  //enable reciever
  UCSR1B = (1<<RXEN1)|(1<<TXEN1);

  //set frame format: 8 data-bits, 2 stop-bits
  UCSR1C = (1<<USBS1)|(3<<UCSZ10);
}
char recieve_UART() {
  //wait for data to be recieved by checking the flags
  while(!(UCSR1A & (1<<RXC1))) {
    ;
  }

  //Get and return recieved data from buffer
  return UDR1;
}

/*
void transmit_UART(unsigned int data) {
  //wait for transmit buffer to be empty
	while (!(UCSR1A & (1<<UDRE1))) {
	}

	UDR1 = data;
}
*/

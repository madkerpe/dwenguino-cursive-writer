/*MARIJN DE KERPEL - ELIEN LEDEGEN*/

#include "../HeaderFiles/setup.h"

void setup_LCD () {
  //Settings for LCD
  initBoard();
  initLCD();
  backlightOn();
}

void setup_interrupts() {
  //configure INT4 pin with falling edge
  //Datasheet p.92 - 12.0.1
  EICRB |= _BV(ISC41);
  EICRB &= ~_BV(ISC40);

  EIMSK |= _BV(PIN4);

  //Bit to allow global interrupts
  //Specific Bit 7 - I
  //Datasheet p.13
  SREG |= _BV(7);

  //INT4 pin of the MC as input and activate pull-up resistance
  DDRE |= _BV(PE4);
  PORTE |= _BV(PE4);

  PORTC |= _BV(PC0);
  DDRC &= ~_BV(PC0);

  PORTC |= _BV(PC1);
  DDRC &= ~_BV(PC1);
}

void setup_timer_interrupts() {
	//Global interrupts must be enabled, but we already did that

	/*Set when the timer generates an interrupt
	Output Compare A Match Interrupt = interrupt if it's the number in register OCR1A
	Datasheet p.143 - 15.10.17*/
  TIMSK1 |= _BV(OCIE1A);
  //here we turn it on


  //TCCR1A en TCCR1B om timer in modus;
  //CTC = Clear Timer Compare match = OCR1A made empty it there is a compare match
  //Datasheet p.138 - tabel 15.4
  TCCR1B &= ~_BV(WGM13);
  TCCR1B |= _BV(WGM12);
  TCCR1A &= ~_BV(WGM11);
  TCCR1A &= ~_BV(WGM10);

  //Sets the prescaler -> after how many clockticks the timer-register must be increased
  //here specific the prescaler is 8
  //Datasheet p.140 - tabel 15.5
  TCCR1B &= ~_BV(CS12);
  TCCR1B |= _BV(CS11);
  TCCR1B &= ~_BV(CS10);

  OCR1A = ((FK / PS) * WACHT_LENGTE);

  //we start in condition LOW
  PINC &= ~_BV(PC0);
  PINC &= ~_BV(PC1);

}

#include "../HeaderFiles/setup.h"

void setup_LCD () {
  //Instellingen voor LCD
  initBoard();
  initLCD();
  backlightOn();
}

void setup_interrupts() {
  //INT4 pin configureren met falling edge
  //Datasheet p.92 - 12.0.1
  EICRB |= _BV(ISC41);
  EICRB &= ~_BV(ISC40);

  //Voor een of andere reden moet deze enabled worden
  EIMSK |= _BV(PIN4);

  //Bit om interrupts globaal toe te laten
  //Specifiek Bit 7 - I
  //Datasheet p.13
  SREG |= _BV(7);

  //INT4 pin van de MC als invoer en pull-up weerstand activeren
  DDRE |= _BV(PE4);
  PORTE |= _BV(PE4);

  PORTC |= _BV(PC0);
  DDRC &= ~_BV(PC0);

  PORTC |= _BV(PC1);
  DDRC &= ~_BV(PC1);
}

void setup_timer_interrupts() {
  //Opnieuw moeten globale interrupts enabled worden
  //Maar dat hebben we al gedaan

  //Instellen wanneer de timer een interrupt genereert
  //Output Compare A Match Interrupt = interrupt als het getal,
  //in register OCR1A
  //Datasheet p.143 - 15.10.17
  TIMSK1 |= _BV(OCIE1A);
  //HIER ZETTEN WE HET AAN!


  //TCCR1A en TCCR1B om timer in modus;
  //CTC = Clear Timer Compare match = OCR1A leeg gemaakt bij compare match
  //Datasheet p.138 - tabel 15.4
  TCCR1B &= ~_BV(WGM13);
  TCCR1B |= _BV(WGM12);
  TCCR1A &= ~_BV(WGM11);
  TCCR1A &= ~_BV(WGM10);

  //Stelt de prescaler in;
  //om de hoeveel klokcycli de timer-register verhoogd moet worden
  //Hier specifiek 256 kolokcycli ---> 16000*4 per seconde
  //Datasheet p.140 - tabel 15.5
  TCCR1B &= ~_BV(CS12);
  TCCR1B |= _BV(CS11);
  TCCR1B &= ~_BV(CS10);

  //Output Compare A Match Interrupt; treshold
  //Hier specifiek 40000,
  //Dan interrupt om de 40/64 seconden
  OCR1A = ((FK / PS) * WACHT_LENGTE);

  //We zorgen dat we beginnen in LAAGe toestand
  PINC &= ~_BV(PC0);
  PINC &= ~_BV(PC1);

}

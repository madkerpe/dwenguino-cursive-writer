#include <avr/io.h>
#include <util/delay.h>

//We voegen enkele lib's toe om het LCD aan te sturen en om interrupts te gebruiken
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"
#include "avr/interrupt.h"

#define LAAG 0
#define SERVO_1 1
#define SERVO_2 2

volatile int toestand = SERVO_1;
volatile int threshold_servo_1 = 0;
volatile int threshold_servo_2 = 0;

int main(void)
{
/**************************************
Vanaf hier instellingen voor LCD
**************************************/

  initBoard();
  initLCD();
  backlightOn();

/**************************************
Vanaf hier instellingen voor interrupts
**************************************/


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


/********************************************
Vanaf hier instellingen voor Timer-interrupts
********************************************/

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
  TCCR1B |= _BV(CS12);
  TCCR1B &= ~_BV(CS11);
  TCCR1B &= ~_BV(CS10);

  //Output Compare A Match Interrupt; treshold
  //Hier specifiek 40000,
  //Dan interrupt om de 40/64 seconden
  OCR1A = 20000;

  //We zorgen dat we beginnen in LAAGe toestand
  PINC &= ~_BV(PC0);
  PINC &= ~_BV(PC1);

  int teller = 0;
  int vierkant[44][2] = {{92,85},{91,86},{90,87},{89,88},{88,89},{87,90},{87,91},{86,92},{85,94},{84,95},{83,96},{83,96},{83,97},{83,97},{84,98},{84,99},{84,99},{84,100},{84,101},{84,102},{84,103},{84,104},{84,104},{85,103},{86,101},{87,100},{88,99},{89,98},{90,97},{91,96},{91,95},{92,94},{93,93},{93,93},{93,92},{93,91},{93,91},{93,90},{93,89},{93,88},{93,87},{92,87},{92,86},{92,85}};

  while(1){

    for (teller = 0; teller < 3; i++) {

      int c_nummer = 0; 
      for (c_nummer; c_nummer < 44; c_nummer++) {

        threshold_servo_1 = vierkant[c_nummer][0];
        threshold_servo_2 = vierkant[c_nummer][1];

        _delay_ms(100)

      }


    }

  }

  return 0;
}


//Interupt als de zuid-knop wordt ingedrukt
ISR(INT4_vect) {

}


//Interupt als de timer een bepaalde waarde overschrijdt
ISR(TIMER1_COMPA_vect) {

  switch (toestand) {

    case LAAG: //we komen van LAAG en gaan naar SERVO_1
      toestand = SERVO_1;
      OCR1A = threshold_servo_1;
      PORTC |= _BV(PC0); //servo 1 gaat hoog //PORT(schrijven), NIET PIN(lezen)
      PORTC &= ~_BV(PC1); //servo 2 gaat laag

      break;

    case SERVO_1: //we komen van SERVO_1 en gaan naar SERVO_2
      toestand = SERVO_2;
      OCR1A = threshold_servo_2;
      PORTC &= ~_BV(PC0); //servo 1 gaat laag
      PORTC |= _BV(PC1); //servo 2 gaat hoog

      break;

    case SERVO_2: //we komen van SERVO_2 en gaan naar LAAG
      toestand = LAAG;
      OCR1A = 188;
      PORTC &= ~_BV(PC0); //servo 1 gaat laag (is normaal gezien overbodig)
      PORTC &= ~_BV(PC1); //servo 2 gaat laag
      break;

  }
}

#include <math.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

#include "HeaderFiles/constants.h"
#include "HeaderFiles/functions.h"
#include "HeaderFiles/figure.h"

//We voegen enkele lib's toe om het LCD aan te sturen en om interrupts te gebruiken
#include "HeaderFiles/dwenguinoBoard.h"
#include "HeaderFiles/dwenguinoLCD.h"
#include "avr/interrupt.h"

volatile unsigned int toestand = SERVO_1;
volatile unsigned int threshold_servo_1 = 0;
volatile unsigned int threshold_servo_2 = 0;
volatile unsigned int threshold_laag = 0;
float angle_pair[2];

volatile float global_rico = 0;
volatile float global_offset = 0;

void setup() {
	//correct
	global_rico = FK * (RL - LL) / (PS * 180);
	global_offset = FK * LL / PS;
	threshold_laag = ((FK / PS) * LAAG_LENGTE);
}

void determine_threshold(float angle, unsigned int* threshold) {
	float temp = (angle * global_rico)/10 + global_offset;
	*threshold = (int)temp;
}

void inverse_kinematics(float x, float y, float* angle_pair) {

	int distance = (int)(norm(x, y)*1000);

	int temp1 = ((ARMLENGTE_1 * ARMLENGTE_1 *1000*1000 + distance * distance - ARMLENGTE_2 * ARMLENGTE_2*1000*1000) / (2 * ARMLENGTE_1 * distance))*10;
	int hoek1 = my_acos(temp1) + my_atan(y *10000/ x);

	int temp2 = ((ARMLENGTE_1 * ARMLENGTE_1 *1000*1000 - distance * distance + ARMLENGTE_2 * ARMLENGTE_2*1000*1000) / (2 * ARMLENGTE_1 * ARMLENGTE_2))/100;
	int hoek2 = my_acos(temp2);

	angle_pair[0] = hoek1;
	angle_pair[1] = hoek2;
}

void draw_BP(BP* current_BP) {

	unsigned int sample_index = 0;
	for (sample_index; sample_index < BP_SAMPLE_SIZE + 1; sample_index++) {

		float t;
		if (sample_index == 0) {
			t = 0;
		}

		else {
			t = (float)sample_index / BP_SAMPLE_SIZE;
		}

		inverse_kinematics(calculate_x(current_BP, t), calculate_y(current_BP, t), angle_pair);

		determine_threshold(angle_pair[0], &threshold_servo_1);
		determine_threshold(angle_pair[1], &threshold_servo_2);
		_delay_ms(100);

	}
}

int main(void) {
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

/********************************************
Vanaf hier gedaan met hardware-setup
********************************************/
  setup();

	//vierkant
	BP* bp0 = create_BP(5, 4, 10, 4, 15, 4);
	BP* bp1 = create_BP(15, 4, 15, 9, 15, 14);
	BP* bp2 = create_BP(15, 14, 10, 14, 5, 14);
	BP* bp3 = create_BP(5, 14, 5, 9, 5, 4);
	BP* vierkant_array[4] = { bp0, bp1, bp2, bp3 };

/*
	//cirkel
	BP* bp4 = create_BP(5, 9, 5, 4, 10, 4);
	BP* bp5 = create_BP(10, 4, 15, 4, 15, 9);
	BP* bp6 = create_BP(15, 9, 15, 14, 10, 14);
	BP* bp7 = create_BP(10, 14, 5, 14, 5, 9);
	BP* cirkel_array[4] = { bp4, bp5, bp6, bp7 };
*/

	while (1) {

		unsigned int i = 0;
		for (i = 0; i < 4; i++) {
			draw_BP(vierkant_array[i]);
		}
	}

	// free(bp0);
	// free(bp1);
	// free(bp2);
	// free(bp3);
  //
	// free(bp4);
	// free(bp5);
	// free(bp6);
	// free(bp7);



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
      OCR1A = threshold_laag;
      PORTC &= ~_BV(PC0); //servo 1 gaat laag (is normaal gezien overbodig)
      PORTC &= ~_BV(PC1); //servo 2 gaat laag
      break;

  }
}

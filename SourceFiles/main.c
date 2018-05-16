#include <math.h>
#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

//We voegen enkele lib's toe om het LCD aan te sturen en om interrupts te gebruiken
#include "HeaderFiles/dwenguinoBoard.h"
#include "avr/interrupt.h"

#include "HeaderFiles/setup.h"
#include "HeaderFiles/uart.h"
#include "HeaderFiles/constants.h"
#include "HeaderFiles/math_functions.h"
#include "HeaderFiles/figure.h"


volatile unsigned int toestand = SERVO_1;
volatile unsigned int threshold_servo_1 = 0;
volatile unsigned int threshold_servo_2 = 0;
volatile unsigned int threshold_laag = 0;

float angle_pair[2];

volatile float global_rico = 0;
volatile float global_offset = 0;
volatile char ingelezen_byte = 0;

void setup_globals() {
  //A prioiri berekening van enkele waarden die vaak hergebruikt worden bij het berekenen van thresholds
	global_rico = FK * (RL - LL) / (PS * 180);
	global_offset = FK * LL / PS;
	threshold_laag = ((FK / PS) * LAAG_LENGTE);
}

void determine_threshold(float angle, unsigned int* threshold) {
	float temp = angle * global_rico + global_offset;
	*threshold = temp;
}

void inverse_kinematics(float x, float y, float* angle_pair) {

	float distance = norm(x, y);

	float temp1 = (ARMLENGTE_1 * ARMLENGTE_1 + distance * distance - ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * distance);
	float hoek1 = my_acos(temp1) + my_atan(y / x);

	float temp2 = (ARMLENGTE_1 * ARMLENGTE_1 - distance * distance + ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * ARMLENGTE_2);
	float hoek2 = my_acos(temp2);

	angle_pair[0] = hoek1 + SERVO_1_OFFSET;
	angle_pair[1] = hoek2 + SERVO_2_OFFSET;
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

void draw_figure(unsigned int array_size, BP* array[]) {

  unsigned int i;
  for (i = 0; i < array_size; i++) {
    draw_BP(array[i]);
  }

}

int main(void) {

  setup_interrupts();
  setup_timer_interrupts();
  setup_LCD();
  setup_globals();
  setup_UART();

  float startpos[2];
  inverse_kinematics(START_POSITION_X, START_POSITION_Y, startpos);
  determine_threshold(startpos[0], &threshold_servo_1);
  determine_threshold(startpos[1], &threshold_servo_2);

  BP* bp0;
  BP* bp1;
  BP* bp2;
  BP* bp3;
  BP* bp4;
  BP* bp5;
  BP* bp6;
  BP* bp7;
  BP* bp8;
  BP* bp9;

  char recieved_letter;

  while (1) {
    recieved_letter = recieve_UART();

    switch (recieved_letter) {
      case 'a':
        printCharToLCD('a', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.00, 0.50, 0.20, 0.50);
        bp1 = create_BP(0.20, 0.50, 0.40, 0.50, 0.40, 0.75);
        bp2 = create_BP(0.40, 0.75, 0.40, 1.00, 0.20, 1.00);
        bp3 = create_BP(0.20, 1.00, 0.00, 1.00, 0.00, 0.75);
        bp4 = create_BP(0.00, 0.75, 0.00, 1.00, 0.20, 1.00);
        bp5 = create_BP(0.20, 1.00, 0.40, 1.00, 0.40, 0.75);
        bp6 = create_BP(0.40, 0.75, 0.40, 0.62, 0.40, 0.50);
        bp7 = create_BP(0.40, 0.50, 0.40, 0.62, 0.40, 0.75);
        bp8 = create_BP(0.40, 0.75, 0.40, 1.25, 0.50, 0.75);
        BP* letter_a_array[9] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8 };
        draw_figure(9, letter_a_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        free(bp7);
        free(bp8);
        break;

      case 'b':
        printCharToLCD('b', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.30, 0.50, 0.25, 0.10);
        bp1 = create_BP(0.25, 0.10, 0.15, 0.00, 0.10, 0.10);
        bp2 = create_BP(0.10, 0.10, 0.10, 0.35, 0.10, 0.75);
        bp3 = create_BP(0.10, 0.75, 0.15, 1.00, 0.25, 1.00);
        bp4 = create_BP(0.25, 1.00, 0.35, 1.00, 0.40, 0.75);
        bp5 = create_BP(0.40, 0.75, 0.45, 0.75, 0.50, 0.75);
        BP* letter_b_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };
        draw_figure(6, letter_b_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        break;

      case 'c':
        printCharToLCD('c', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.05, 0.55, 0.25, 0.50);
        bp1 = create_BP(0.25, 0.50, 0.05, 0.55, 0.00, 0.75);
        bp2 = create_BP(0.00, 0.75, 0.00, 1.00, 0.25, 1.00);
        bp3 = create_BP(0.25, 1.00, 0.40, 0.90, 0.45, 0.75);
        bp4 = create_BP(0.45, 0.75, 0.47, 0.75, 0.50, 0.75);
        BP* letter_c_array[5] = { bp0, bp1, bp2, bp3, bp4 };
        draw_figure(5, letter_c_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        break;

      case 'd':
        printCharToLCD('d', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.00, 0.50, 0.20, 0.50);
        bp1 = create_BP(0.20, 0.50, 0.40, 0.50, 0.40, 0.75);
        bp2 = create_BP(0.40, 0.75, 0.40, 1.00, 0.20, 1.00);
        bp3 = create_BP(0.20, 1.00, 0.00, 1.00, 0.00, 0.75);
        bp4 = create_BP(0.00, 0.75, 0.00, 1.00, 0.20, 1.00);
        bp5 = create_BP(0.20, 1.00, 0.40, 1.00, 0.40, 0.75);
        bp6 = create_BP(0.40, 0.75, 0.40, 0.50, 0.40, 0.00);
        bp7 = create_BP(0.40, 0.00, 0.40, 0.50, 0.40, 0.75);
        bp8 = create_BP(0.40, 0.75, 0.40, 1.25, 0.50, 0.75);
        BP* letter_d_array[9] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8 };
        draw_figure(9, letter_d_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        free(bp7);
        free(bp8);
        break;

      case 'e':
        printCharToLCD('e', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 1.00, 0.12, 1.00);
        bp1 = create_BP(0.12, 1.00, 0.15, 1.00, 0.25, 0.90);
        bp2 = create_BP(0.25, 0.90, 0.45, 0.62, 0.25, 0.50);
        bp3 = create_BP(0.25, 0.50, 0.05, 0.62, 0.25, 0.90);
        bp4 = create_BP(0.25, 0.90, 0.35, 1.00, 0.38, 1.00);
        bp5 = create_BP(0.38, 1.00, 0.40, 1.00, 0.50, 0.75);
        BP* letter_e_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };
        draw_figure(6, letter_e_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        break;

      case 'f':
        printCharToLCD('f', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.40, 0.50, 0.35, 0.10);
        bp1 = create_BP(0.35, 0.10, 0.25, 0.00, 0.20, 0.10);
        bp2 = create_BP(0.20, 0.10, 0.20, 0.35, 0.20, 1.00);
        bp3 = create_BP(0.20, 1.00, 0.20, 0.75, 0.20, 0.65);
        bp4 = create_BP(0.20, 0.65, 0.10, 0.65, 0.05, 0.65);
        bp5 = create_BP(0.05, 0.65, 0.20, 0.65, 0.50, 0.65);
        BP* letter_f_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };
        draw_figure(6, letter_f_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        break;

      case 'g':
        printCharToLCD('g', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 0.75, 0.10, 0.50);
        bp1 = create_BP(0.10, 0.50, 0.10, 0.25, 0.25, 0.25);
        bp2 = create_BP(0.25, 0.25, 0.40, 0.25, 0.40, 0.50);
        bp3 = create_BP(0.40, 0.50, 0.40, 0.75, 0.25, 0.75);
        bp4 = create_BP(0.25, 0.75, 0.10, 0.75, 0.10, 0.50);
        bp5 = create_BP(0.10, 0.50, 0.10, 0.75, 0.25, 0.75);
        bp6 = create_BP(0.25, 0.75, 0.40, 0.75, 0.40, 0.50);
        bp7 = create_BP(0.40, 0.50, 0.40, 1.00, 0.25, 1.00);
        bp8 = create_BP(0.25, 1.00, 0.20, 1.00, 0.25, 0.90);
        bp9 = create_BP(0.25, 0.90, 0.30, 0.85, 0.50, 0.75);
        BP* letter_g_array[10] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8, bp9 };
        draw_figure(10, letter_g_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        free(bp7);
        free(bp8);
        free(bp9);
        break;

      case 'h':
        printCharToLCD('h', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.25, 0.50, 0.25, 0.25);
        bp1 = create_BP(0.25, 0.25, 0.17, 0.00, 0.10, 0.25);
        bp2 = create_BP(0.10, 0.25, 0.10, 0.75, 0.10, 1.00);
        bp3 = create_BP(0.10, 1.00, 0.10, 0.80, 0.10, 0.75);
        bp4 = create_BP(0.10, 0.75, 0.35, 0.40, 0.35, 0.95);
        bp5 = create_BP(0.35, 0.95, 0.35, 1.00, 0.50, 0.75);
        BP* letter_h_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };
        draw_figure(6, letter_h_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        break;

      case 'i':
        printCharToLCD('i', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.25, 1.00, 0.25, 0.50);
        bp1 = create_BP(0.25, 0.50, 0.25, 1.00, 0.50, 0.75);
        BP* letter_i_array[2] = { bp0, bp1 };
        draw_figure(2, letter_i_array);
        free(bp0);
        free(bp1);
        break;

      case 'j':
        printCharToLCD('j', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.25, 0.75, 0.25, 0.50);
        bp1 = create_BP(0.25, 0.50, 0.25, 1.00, 0.10, 1.00);
        bp2 = create_BP(0.10, 1.00, 0.00, 0.90, 0.50, 0.75);
        BP* letter_j_array[3] = { bp0, bp1, bp2 };
        draw_figure(3, letter_j_array);
        free(bp0);
        free(bp1);
        free(bp2);
        break;

      case 'k':
        printCharToLCD('k', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.25, 0.50, 0.25, 0.25);
        bp1 = create_BP(0.25, 0.25, 0.17, 0.00, 0.10, 0.25);
        bp2 = create_BP(0.10, 0.25, 0.10, 0.75, 0.10, 1.00);
        bp3 = create_BP(0.10, 1.00, 0.10, 0.80, 0.10, 0.65);
        bp4 = create_BP(0.10, 0.65, 0.25, 0.55, 0.25, 0.75);
        bp5 = create_BP(0.25, 0.75, 0.20, 1.00, 0.10, 0.80);
        bp6 = create_BP(0.10, 0.80, 0.15, 1.00, 0.30, 1.00);
        bp7 = create_BP(0.30, 1.00, 0.40, 1.00, 0.50, 0.75);
        BP* letter_k_array[8] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7 };
        draw_figure(8, letter_k_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        free(bp7);
        break;

      case 'l':
        printCharToLCD('l', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 1.00, 0.12, 1.00);
        bp1 = create_BP(0.12, 1.00, 0.15, 1.00, 0.25, 0.90);
        bp2 = create_BP(0.25, 0.90, 0.40, 0.50, 0.35, 0.25);
        bp3 = create_BP(0.35, 0.25, 0.25, 0.00, 0.15, 0.25);
        bp4 = create_BP(0.15, 0.25, 0.10, 0.50, 0.25, 0.90);
        bp5 = create_BP(0.25, 0.90, 0.35, 1.00, 0.38, 1.00);
        bp6 = create_BP(0.38, 1.00, 0.40, 1.00, 0.50, 0.75);
        BP* letter_l_array[7] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6 };
        draw_figure(7, letter_l_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        break;

      case 'm':
        printCharToLCD('m', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.05, 0.90, 0.10, 0.60);
        bp1 = create_BP(0.10, 0.60, 0.20, 0.50, 0.20, 1.00);
        bp2 = create_BP(0.20, 1.00, 0.20, 0.55, 0.25, 0.55);
        bp3 = create_BP(0.25, 0.55, 0.30, 0.55, 0.30, 1.00);
        bp4 = create_BP(0.30, 1.00, 0.30, 0.50, 0.40, 0.60);
        bp5 = create_BP(0.40, 0.60, 0.45, 0.90, 0.50, 0.75);
        BP* letter_m_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };
        draw_figure(6, letter_m_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        break;

      case 'n':
        printCharToLCD('n', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 0.90, 0.15, 0.60);
        bp1 = create_BP(0.15, 0.60, 0.30, 0.40, 0.28, 1.00);
        bp2 = create_BP(0.28, 1.00, 0.30, 0.55, 0.35, 0.55);
        bp3 = create_BP(0.35, 0.55, 0.40, 0.55, 0.40, 0.68);
        bp4 = create_BP(0.40, 0.68, 0.45, 0.90, 0.50, 0.75);
        BP* letter_n_array[5] = { bp0, bp1, bp2, bp3, bp4 };
        draw_figure(5, letter_n_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        break;

      case 'o':
        printCharToLCD('o', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.00, 0.50, 0.20, 0.50);
        bp1 = create_BP(0.20, 0.50, 0.40, 0.50, 0.40, 0.75);
        bp2 = create_BP(0.40, 0.75, 0.40, 1.00, 0.20, 1.00);
        bp3 = create_BP(0.20, 1.00, 0.00, 1.00, 0.00, 0.75);
        bp4 = create_BP(0.00, 0.75, 0.00, 1.00, 0.20, 1.00);
        bp5 = create_BP(0.20, 1.00, 0.40, 1.00, 0.40, 0.75);
        bp6 = create_BP(0.40, 0.75, 0.40, 1.25, 0.50, 0.75);
        BP* letter_o_array[7] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6 };
        draw_figure(7, letter_o_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        break;

      case 'p':
        printCharToLCD('p', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.15, 0.75, 0.20, 0.50);
        bp1 = create_BP(0.20, 0.50, 0.20, 0.75, 0.20, 1.00);
        bp2 = create_BP(0.20, 1.00, 0.20, 0.75, 0.20, 0.50);
        bp3 = create_BP(0.20, 0.50, 0.25, 0.35, 0.30, 0.50);
        bp4 = create_BP(0.30, 0.50, 0.35, 0.75, 0.50, 0.75);
        BP* letter_p_array[5] = { bp0, bp1, bp2, bp3, bp4 };
        draw_figure(5, letter_p_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        break;

      case 'q':
        printCharToLCD('q', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 0.75, 0.10, 0.50);
        bp1 = create_BP(0.10, 0.50, 0.10, 0.25, 0.25, 0.25);
        bp2 = create_BP(0.25, 0.25, 0.40, 0.25, 0.40, 0.50);
        bp3 = create_BP(0.40, 0.50, 0.40, 0.75, 0.25, 0.75);
        bp4 = create_BP(0.25, 0.75, 0.10, 0.75, 0.10, 0.50);
        bp5 = create_BP(0.10, 0.50, 0.10, 0.75, 0.25, 0.75);
        bp6 = create_BP(0.25, 0.75, 0.40, 0.75, 0.40, 0.50);
        bp7 = create_BP(0.40, 0.50, 0.40, 0.75, 0.40, 1.00);
        bp8 = create_BP(0.40, 1.00, 0.40, 0.75, 0.40, 0.50);
        bp9 = create_BP(0.40, 0.50, 0.40, 0.75, 0.50, 0.75);
        BP* letter_q_array[10] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8, bp9 };
        draw_figure(10, letter_q_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        free(bp7);
        free(bp8);
        free(bp9);
        break;

      case 'r':
        printCharToLCD('r', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 0.62, 0.10, 0.50);
        bp1 = create_BP(0.10, 0.50, 0.25, 0.55, 0.40, 0.50);
        bp2 = create_BP(0.40, 0.50, 0.35, 1.00, 0.45, 1.00);
        bp3 = create_BP(0.45, 1.00, 0.50, 1.00, 0.50, 0.75);
        BP* letter_r_array[4] = { bp0, bp1, bp2, bp3 };
        draw_figure(4, letter_r_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        break;

      case 's':
        printCharToLCD('s', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.15, 0.70, 0.35, 0.50);
        bp1 = create_BP(0.35, 0.50, 0.40, 0.50, 0.35, 0.75);
        bp2 = create_BP(0.35, 0.75, 0.30, 1.00, 0.10, 0.70);
        bp3 = create_BP(0.10, 0.70, 0.30, 1.00, 0.35, 0.75);
        bp4 = create_BP(0.35, 0.75, 0.40, 0.65, 0.50, 0.75);
        BP* letter_s_array[5] = { bp0, bp1, bp2, bp3, bp4 };
        draw_figure(5, letter_s_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        break;

      case 't':
        printCharToLCD('t', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.15, 0.75, 0.15, 0.00);
        bp1 = create_BP(0.15, 0.00, 0.15, 0.20, 0.15, 0.45);
        bp2 = create_BP(0.15, 0.45, 0.25, 0.40, 0.35, 0.35);
        bp3 = create_BP(0.35, 0.35, 0.25, 0.40, 0.15, 0.45);
        bp4 = create_BP(0.15, 0.45, 0.15, 0.65, 0.15, 0.75);
        bp5 = create_BP(0.15, 0.75, 0.15, 1.00, 0.35, 1.00);
        bp6 = create_BP(0.35, 1.00, 0.45, 1.00, 0.50, 0.75);
        BP* letter_t_array[7] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6 };
        draw_figure(7, letter_t_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        break;

      case 'u':
        printCharToLCD('u', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 0.75, 0.10, 0.50);
        bp1 = create_BP(0.10, 0.50, 0.10, 1.00, 0.25, 1.00);
        bp2 = create_BP(0.25, 1.00, 0.40, 1.00, 0.40, 0.50);
        bp3 = create_BP(0.40, 0.50, 0.40, 0.75, 0.50, 0.75);
        BP* letter_u_array[4] = { bp0, bp1, bp2, bp3 };
        draw_figure(4, letter_u_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        break;

      case 'v':
        printCharToLCD('v', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.05, 0.75, 0.05, 0.50);
        bp1 = create_BP(0.05, 0.50, 0.10, 0.55, 0.15, 0.50);
        bp2 = create_BP(0.15, 0.50, 0.15, 1.00, 0.25, 1.00);
        bp3 = create_BP(0.25, 1.00, 0.35, 1.00, 0.35, 0.50);
        bp4 = create_BP(0.35, 0.50, 0.40, 0.55, 0.45, 0.50);
        bp5 = create_BP(0.45, 0.50, 0.45, 0.75, 0.50, 0.75);
        BP* letter_v_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };
        draw_figure(6, letter_v_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        break;

      case 'w':
        printCharToLCD('w', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.05, 0.25, 0.20, 1.00);
        bp1 = create_BP(0.20, 1.00, 0.25, 1.00, 0.25, 0.80);
        bp2 = create_BP(0.25, 0.80, 0.25, 1.00, 0.30, 1.00);
        bp3 = create_BP(0.30, 1.00, 0.35, 0.25, 0.50, 0.75);
        BP* letter_w_array[4] = { bp0, bp1, bp2, bp3 };
        draw_figure(4, letter_w_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        break;

      case 'x':
        printCharToLCD('x', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 1.00, 0.12, 1.00);
        bp1 = create_BP(0.12, 1.00, 0.15, 1.00, 0.25, 0.80);
        bp2 = create_BP(0.25, 0.80, 0.25, 0.35, 0.05, 0.50);
        bp3 = create_BP(0.05, 0.50, 0.25, 0.35, 0.25, 0.80);
        bp4 = create_BP(0.25, 0.80, 0.25, 0.35, 0.45, 0.50);
        bp5 = create_BP(0.45, 0.50, 0.25, 0.35, 0.25, 0.80);
        bp6 = create_BP(0.25, 0.80, 0.35, 1.00, 0.38, 1.00);
        bp7 = create_BP(0.38, 1.00, 0.40, 1.00, 0.50, 0.75);
        BP* letter_x_array[8] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7 };
        draw_figure(8, letter_x_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        free(bp6);
        free(bp7);
        break;


      case 'y':
        printCharToLCD('y', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 0.75, 0.10, 0.50);
        bp1 = create_BP(0.10, 0.50, 0.10, 0.75, 0.25, 0.75);
        bp2 = create_BP(0.25, 0.75, 0.40, 0.75, 0.40, 0.50);
        bp3 = create_BP(0.40, 0.50, 0.40, 1.00, 0.25, 1.00);
        bp4 = create_BP(0.25, 1.00, 0.20, 1.00, 0.25, 0.90);
        bp5 = create_BP(0.25, 0.90, 0.30, 0.85, 0.50, 0.75);
        BP* letter_y_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };
        draw_figure(6, letter_y_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        free(bp5);
        break;

      case 'z':
        printCharToLCD('z', 1, 1);
        bp0 = create_BP(0.00, 0.75, 0.10, 0.62, 0.10, 0.50);
        bp1 = create_BP(0.10, 0.50, 0.25, 0.55, 0.40, 0.50);
        bp2 = create_BP(0.40, 0.50, 0.25, 0.75, 0.10, 1.00);
        bp3 = create_BP(0.10, 1.00, 0.25, 0.95, 0.40, 1.00);
        bp4 = create_BP(0.40, 1.00, 0.40, 0.85, 0.50, 0.75);
        BP* letter_z_array[5] = { bp0, bp1, bp2, bp3, bp4 };
        draw_figure(5, letter_z_array);
        free(bp0);
        free(bp1);
        free(bp2);
        free(bp3);
        free(bp4);
        break;


      }

      //hacky function to get to a value from another namespace
      set_x_offset(0.5*SCALE);

    }

  return 0;
}


//Interupt als de zuid-knop wordt ingedrukt
//function only used for debugging
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

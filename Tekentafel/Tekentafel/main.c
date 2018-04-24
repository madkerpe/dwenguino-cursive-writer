#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "figure.h"

#define LAAG 0
#define SERVO_1 1
#define SERVO_2 2

#define LL 700 //μs
#define RL 2300 //μs
#define FK 16000 //ticks per μs
#define PS 256 //dimentieloos
#define ARMLENGTE_1 14 //cm
#define ARMLENGTE_2 14 //cm

#define BP_SAMPLE_SIZE 10

#define PI 3.14159265359

volatile unsigned int toestand = SERVO_1;
volatile unsigned int threshold_servo_1 = 0;
volatile unsigned int threshold_servo_2 = 0;
volatile float global_rico = 0;
volatile float global_offset = 0;

void setup();
float radians_to_degrees(float rad);
float* inverse_kinematics(float x, float y);
int determine_threshold(float angle);

void setup() {
	global_rico = FK * (RL - LL) / (PS * 180); 
	global_offset = FK * LL / PS;
}

float radians_to_degrees(float rad) {
	return rad * 180 / PI;
}

float* inverse_kinematics(float x, float y) {
	float distance = sqrt(x*x + y * y);
	
	float temp1 = (ARMLENGTE_1 * ARMLENGTE_1 + distance * distance - ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * distance);
	float hoek1 = radians_to_degrees(acos(temp1) + atan(y / x));
	printf("hoek 1 = %f", hoek1);

	float temp2 = (ARMLENGTE_1 * ARMLENGTE_1 - distance * distance + ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * ARMLENGTE_2);
	float hoek2 = radians_to_degrees(acos(temp2));

	float angle_pair[2] = { hoek1, hoek2 };
	return angle_pair;
}


int determine_threshold(float angle) {
	return (int)(angle*global_rico + global_offset);
}

int main(void) {

	setup();

	BP *bp0 = create_BP(14, 10, 16, 10, 18, 10);
	BP* bp1 = create_BP(18, 10, 18, 12, 18, 14);
	BP* bp2 = create_BP(18, 14, 16, 14, 14, 14);
	BP* bp3 = create_BP(14, 14, 14, 12, 14, 10);

	BP bp_list_vierkant[4] = { bp0, bp1, bp2, bp3 };
	figure* vierkant = create_figure(4, bp_list_vierkant);

	BP *bp4 = create_BP(5, 5, 8, 10, 15, 5);
	BP* bp5 = create_BP(15, 5, 2, 10, 15, 5);

	BP bp_list_citroen[2] = { bp4, bp5 };
	figure* citroen = create_figure(2, bp_list_citroen);

	figure* current_figure = vierkant;

	printf("global_rico = %f & global_offset = %f", global_rico, global_offset);

	/*
	unsigned int i = 0;
	for (i; i < current_figure->amount_of_bp; i++) {
		BP current_BP = current_figure->bp_list[i];

		unsigned int j = 0;
		for (j; j < BP_SAMPLE_SIZE + 1; j++) {
			if (j == 0) {
				threshold_servo_1 = determine_threshold(calculate_x(&current_BP, 0));
				threshold_servo_2 = determine_threshold(calculate_y(&current_BP, 0));
				printf("#%d:%d#	  SERVO_1: %f  SERVO_2: %f\n", i, j, calculate_x(&current_BP, 0), calculate_y(&current_BP, 0));

			}
			
			else {
				threshold_servo_1 = determine_threshold(calculate_x(&current_BP, (float)j / BP_SAMPLE_SIZE));
				threshold_servo_2 = determine_threshold(calculate_y(&current_BP, (float)j / BP_SAMPLE_SIZE));
				printf("#%d:%d#	  SERVO_1: %f  SERVO_2: %f\n", i, j, calculate_x(&current_BP, (float)j / BP_SAMPLE_SIZE), calculate_y(&current_BP, (float)j / BP_SAMPLE_SIZE));
			}
			
			//_delay_ms(500);
			//delay(500);


			//printf("#%d:%d#	  SERVO_1: %d  SERVO_2: %d\n", i, j, threshold_servo_1, threshold_servo_2);

		}
	}
	*/

	getchar();

	return 0;
}



#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "functions.h"
#include "figure.h"


volatile unsigned int toestand = SERVO_1;
volatile unsigned int threshold_servo_1 = 0;
volatile unsigned int threshold_servo_2 = 0;
volatile unsigned int threshold_laag = 0;
volatile float global_rico = 0;
volatile float global_offset = 0;

void setup() {
	//correct
	global_rico = FK * (RL - LL) / (PS * 180);
	global_offset = FK * LL / PS;
	threshold_laag = ((FK / PS) * LAAG_LENGTE);

	printf("global_rico = %f & global_offset = %f & laag = %d\n\n", global_rico, global_offset, threshold_laag);
}

int determine_threshold(float angle) {
	//moeilijk om dit fout te hebben...
	double temp = angle * global_rico + global_offset;
	return (int)temp;
}

float* inverse_kinematics(float x, float y) {
	//correct

	float distance = norm(x, y);

	float temp1 = (ARMLENGTE_1 * ARMLENGTE_1 + distance * distance - ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * distance);
	float hoek1 = my_acos(temp1) + my_atan(y / x);
	//printf("hoek 1 = %f\n", hoek1);

	float temp2 = (ARMLENGTE_1 * ARMLENGTE_1 - distance * distance + ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * ARMLENGTE_2);
	float hoek2 = my_acos(temp2);
	//printf("hoek 2 = %f\n", hoek2);

	float angle_pair[2] = { hoek1, hoek2 };
	return angle_pair;
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

		float* angle_pair = inverse_kinematics(calculate_x(current_BP, t), calculate_y(current_BP, t));
		float alpha = angle_pair[0];
		float beta = angle_pair[1];

		threshold_servo_1 = determine_threshold(alpha);
		threshold_servo_2 = determine_threshold(beta);
		printf("#%d:	pos:(%.2f,%.2f) -> angle:(%.2f,%.2f) -> thres:(%d,%d)\n", sample_index, calculate_x(current_BP, t), calculate_y(current_BP, t), alpha, beta, threshold_servo_1, threshold_servo_2);
	}
}

int main(void) {

	setup();

	BP* bp0 = create_BP(0, 14, 7, 14, 14, 0);
	BP* bp1 = create_BP(14, 0, 3, 3, 0, 14);
	BP* bp_list[2] = { bp0, bp1};
	
	draw_BP(bp_list[0]);
	draw_BP(bp_list[1]);


	/*
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
	*/

	/*
	unsigned int i = 0;
	for (i; i < current_figure->amount_of_bp; i++) {
		BP current_BP = current_figure->bp_list[i];
	}
	*/

	/*
	printf("\n\n");
	float* angle_pair = inverse_kinematics(14, 14);
	float alpha = angle_pair[0];
	float beta = angle_pair[1];

	printf("\n\nalpha = %f  beta = %f\n", alpha, beta);
	*/

	getchar();

	return 0;
}



#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "functions.h"
#include "figure.h"

#define _DEBUG

#if defined(_WIN32) || defined(_WIN64)
#include <crtdbg.h>
#endif

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
	
	delay(1000);
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
		printf("#%2d:	pos:(%2.2f,%2.2f) -> angle:(%.2f,%.2f) -> thres:(%d,%d)\n", sample_index, calculate_x(current_BP, t), calculate_y(current_BP, t), alpha, beta, threshold_servo_1, threshold_servo_2);
		delay(1000);
	
	}
}

int main(void) {

	setup();
	figure* current_figure;

	//vierkant
	BP* bp0 = create_BP(5, 4, 10, 4, 15, 4);
	BP* bp1 = create_BP(15, 4, 15, 9, 15, 14);
	BP* bp2 = create_BP(15, 14, 10, 14, 5, 14);
	BP* bp3 = create_BP(5, 14, 5, 9, 5, 4);
	BP* vierkant_array[4] = { bp0, bp1, bp2, bp3 };
	figure* vierkant = create_figure(4, vierkant_array);

	//cirkel
	BP* bp0 = create_BP(5, 9, 5, 4, 10, 4);
	BP* bp1 = create_BP(10, 4, 15, 4, 15, 9);
	BP* bp2 = create_BP(15, 9, 15, 14, 10, 14);
	BP* bp3 = create_BP(10, 14, 5, 14, 5, 9);
	BP* cirkel_array[4] = { bp0, bp1, bp2, bp3 };
	figure* cirkel = create_figure(4, cirkel_array);


	current_figure = vierkant;

	while (1) {
		
		unsigned int i = 0;
		for (i = 0; i < current_figure->amount_of_bp; i++) {
			draw_BP(&(vierkant->bp_list[i]));
			delay(500);
		}
	
	}

	free(bp0);
	free(bp1);
	delete_figure(vierkant);

	getchar();

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
	_CrtDumpMemoryLeaks();

	/* Test for memory leaks */

	getchar();


	return 0;
}



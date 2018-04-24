#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "constants.h"
#include "figure.h"


volatile unsigned int toestand = SERVO_1;
volatile unsigned int threshold_servo_1 = 0;
volatile unsigned int threshold_servo_2 = 0;
volatile float global_rico = 0;
volatile float global_offset = 0;

void setup() {
	//correct
	global_rico = FK * (RL - LL) / (PS * 180);
	global_offset = FK * LL / PS;
}

int determine_threshold(float angle) {
	//moeilijk om dit fout te hebben...
	double temp = angle * global_rico + global_offset;
	return (int)temp;
}

int main(void) {

	setup();
	printf("global_rico = %f & global_offset = %f\n", global_rico, global_offset);

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



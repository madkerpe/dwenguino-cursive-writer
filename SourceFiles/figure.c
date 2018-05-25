/*MARIJN DE KERPEL - ELIEN LEDEGEN*/

#include "../HeaderFiles/figure.h"
#include "../HeaderFiles/constants.h"
#include <stdlib.h>

volatile float x_offset = START_POSITION_X;
volatile float y_offset = START_POSITION_Y;

BP * create_BP(float P0x, float P0y, float P1x, float P1y, float P2x, float P2y) {
	BP* bp = (BP*)malloc(sizeof(BP));

	bp->P0[0] = P0x;
	bp->P0[1] = P0y;

	bp->P1[0] = P1x;
	bp->P1[1] = P1y;

	bp->P2[0] = P2x;
	bp->P2[1] = P2y;

	return bp;
}

float calculate_x(BP* bpp, float t) {
	float temp = bpp->P0[0] * (1 - t)*(1 - t) + 2 * (1 - t)* t * bpp->P1[0] + bpp->P2[0] * t*t;
	return temp*SCALE + x_offset;
}

float calculate_y(BP * bpp, float t) {
	float temp = bpp->P0[1] * (1 - t)*(1 - t) + 2 * (1 - t)* t * bpp->P1[1] + bpp->P2[1] * t*t;
	return temp*SCALE + y_offset;
}

void set_x_offset(float dx) {
	x_offset += dx;
}

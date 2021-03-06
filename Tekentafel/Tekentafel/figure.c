#include "figure.h"
#include <stdlib.h>

BP * create_BP(unsigned int P0x, unsigned int P0y, unsigned int P1x, unsigned int P1y, unsigned int P2x, unsigned int P2y) {
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
	return bpp->P0[0] * (1 - t)*(1 - t) + 2 * (1 - t)* t * bpp->P1[0] + bpp->P2[0] * t*t;
}

float calculate_y(BP * bpp, float t) {
	return bpp->P0[1] * (1 - t)*(1 - t) + 2 * (1 - t)* t * bpp->P1[1] + bpp->P2[1] * t*t;
}

figure* create_figure(unsigned int new_amount_of_bp, BP* new_bp_array) {
	figure* fp = (figure*)malloc(sizeof(figure));
	BP* new_bp_list = malloc(new_amount_of_bp * sizeof(BP*));
	fp->amount_of_bp = new_amount_of_bp;

	unsigned int i = 0;
	for (i; i < new_amount_of_bp; i++) {
		
		new_bp_list[i] = new_bp_array[i];
	}

	fp->bp_list = new_bp_list;

	return fp;
}

void delete_figure(figure* fp) {
	free(fp->bp_list);
	free(fp);
}

/*
BP* get_BP_list(figure* current_figure) {
	return current_figure->bp_list;
}
*/
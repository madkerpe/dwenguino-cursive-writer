#include "../HeaderFiles/figure.h"
#include <stdlib.h>

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
	return bpp->P0[0] * (1 - t)*(1 - t) + 2 * (1 - t)* t * bpp->P1[0] + bpp->P2[0] * t*t;
}

float calculate_y(BP * bpp, float t) {
	return bpp->P0[1] * (1 - t)*(1 - t) + 2 * (1 - t)* t * bpp->P1[1] + bpp->P2[1] * t*t;
}

BP* vierkant() {
	BP* bp0 = create_BP(5, 4, 10, 4, 15, 4);
	BP* bp1 = create_BP(15, 4, 15, 9, 15, 14);
	BP* bp2 = create_BP(15, 14, 10, 14, 5, 14);
	BP* bp3 = create_BP(5, 14, 5, 9, 5, 4);
	BP* vierkant_array[4] = { bp0, bp1, bp2, bp3 };

	return vierkant_array;
}

BP* cirkel() {
	BP* bp0 = create_BP(5, 9, 5, 4, 10, 4);
	BP* bp1 = create_BP(10, 4, 15, 4, 15, 9);
	BP* bp2 = create_BP(15, 9, 15, 14, 10, 14);
	BP* bp3 = create_BP(10, 14, 5, 14, 5, 9);
	BP* cirkel_array[4] = { bp0, bp1, bp2, bp3 };

	return cirkel_array;
}

BP* letter_d() {
	BP* bp0 = create_BP(0, 0.25, 0, 0.5, 0.2, 0.5);
	BP* bp1 = create_BP(0.2, 0.5, 0.4, 0.5, 0.4, 0.25);
	BP* bp2 = create_BP(0.4, 0.25, 0.4, 0, 0.2, 0);
	BP* bp3 = create_BP(0.2, 0, 0, 0, 0, 0.25);
	BP* bp4 = create_BP(0, 0.25, 0, 0, 0.2, 0);
	BP* bp5 = create_BP(0.2, 0, 0.4, 0, 0.4, 0.25);
	BP* bp6 = create_BP(0.4, 0.25, 0.4, 0.5, 0.4, 1);
	BP* bp7 = create_BP(0.4, 1, 0.4, 0.5, 0.4, 0.25);
	BP* bp8 = create_BP(0.4, 0.25, 0.4, 0, 0.5, 0.25);
	BP* letter_d_array[9] = { bp0, bp1, bp2, bp3, bp4, bp5, bp6, bp7, bp8 };

	return letter_d_array;
}

BP* letter_w() {
	BP* bp0 = create_BP(0, 0.25, 0.05, 0.75, 0.2, 0);
	BP* bp1 = create_BP(0.2, 0, 0.25, 0, 0.25, 0.2);
	BP* bp2 = create_BP(0.25, 0.2, 0.25, 0, 0.3, 0);
	BP* bp3 = create_BP(0.3, 0, 0.45, 0.75, 0.5, 0.25);
	BP* letter_w_array[4] = { bp0, bp1, bp2, bp3 };

	return letter_w_array;
}
BP* letter_e() {
	BP* bp0 = create_BP(0, 0.25, 0.1, 0, 0.125, 0);
	BP* bp1 = create_BP(0.125, 0, 0.15, 0, 0.25, 0.1);
	BP* bp2 = create_BP(0.25, 0.1, 0.05, 0.375, 0.25, 0.5);
	BP* bp3 = create_BP(0.25, 0.5, 0.45, 0.375, 0.25, 0.1);
	BP* bp4 = create_BP(0.25, 0.1, 0.35, 0, 0.375, 0);
	BP* bp5 = create_BP(0.375, 0, 0.4, 0, 0.5, 0.25);
	BP* letter_e_array[6] = { bp0, bp1, bp2, bp3, bp4, bp5 };

	return letter_e_array;
}
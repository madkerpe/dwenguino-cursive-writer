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

BP* horizontale_raster() {
	BP* bp0 = create_BP(0, 0, 10, 0, 20, 0);
	//BP* bp1 = create_BP(0, 1, 10, 1, 20, 1);
	BP* bp2 = create_BP(0, 2, 10, 2, 20, 2);
	//BP* bp3 = create_BP(0, 3, 10, 3, 20, 3);
	BP* bp4 = create_BP(0, 4, 10, 4, 20, 4);
	//BP* bp5 = create_BP(0, 5, 10, 5, 20, 5);
	BP* bp6 = create_BP(0, 6, 10, 6, 20, 6);
	//BP* bp7 = create_BP(0, 7, 10, 7, 20, 7);
	BP* bp8 = create_BP(0, 8, 10, 8, 20, 8);
	//BP* bp9 = create_BP(0, 9, 10, 9, 20, 9);
	BP* bp10 = create_BP(0, 10, 10, 10, 20, 10);
	//BP* bp11 = create_BP(0, 11, 10, 11, 20, 11);
	BP* bp12 = create_BP(0, 12, 10, 12, 20, 12);
	//BP* bp13 = create_BP(0, 13, 10, 13, 20, 13);
	BP* bp14 = create_BP(0, 14, 10, 14, 20, 14);
	//BP* bp15 = create_BP(0, 15, 10, 15, 20, 15);
	BP* bp16 = create_BP(0, 16, 10, 16, 20, 16);
	BP* horizontale_raster_array[9] = {bp0, bp2, bp4, bp6, bp8, bp10, bp12, bp14, bp16 };

	return horizontale_raster_array;
}

BP* verticale_raster() {
	BP* bp0 = create_BP(0, 0, 0, 8, 0, 16);
	//BP* bp1 = create_BP(1, 0, 1, 8, 1, 16);
	BP* bp2 = create_BP(2, 0, 2, 8, 2, 16);
	//BP* bp3 = create_BP(3, 0, 3, 8, 3, 16);
	BP* bp4 = create_BP(4, 0, 4, 8, 4, 16);
	//BP* bp5 = create_BP(5, 0, 5, 8, 5, 16);
	BP* bp6 = create_BP(6, 0, 6, 8, 6, 16);
	//BP* bp7 = create_BP(7, 0, 7, 8, 7, 16);
	BP* bp8 = create_BP(8, 0, 8, 8, 8, 16);
	//BP* bp9 = create_BP(9, 0, 9, 8, 9, 16);
	BP* bp10 = create_BP(10, 0, 10, 8, 10, 16);
	//BP* bp11 = create_BP(11, 0, 11, 8, 11, 16);
	BP* bp12 = create_BP(12, 0, 12, 8, 12, 16);
	//BP* bp13 = create_BP(13, 0, 13, 8, 13, 16);
	BP* bp14 = create_BP(14, 0, 14, 8, 14, 16);
	//BP* bp15 = create_BP(15, 0, 15, 8, 15, 16);
	BP* bp16 = create_BP(16, 0, 16, 8, 16, 16);
	//BP* bp17 = create_BP(17, 0, 17, 8, 17, 16);
	BP* bp18 = create_BP(18, 0, 18, 8, 18, 16);
	//BP* bp19 = create_BP(19, 0, 19, 8, 19, 16);
	BP* bp20 = create_BP(20, 0, 20, 8, 20, 16);
	BP* verticale_raster_array[11] = {bp0, bp2, bp4, bp6, bp8, bp10, bp12, bp14, bp16, bp18, bp20};

	return verticale_raster_array;
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

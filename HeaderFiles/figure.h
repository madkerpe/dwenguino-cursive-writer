#ifndef DEF_FIGURE
#define DEF_FIGURE

typedef struct{
	unsigned int P0[2];
	unsigned int P1[2];
	unsigned int P2[2];
} BP;

BP* create_BP(unsigned int P0x, unsigned int P0y, unsigned int P1x, unsigned int P1y, unsigned int P2x, unsigned int P2y);

float calculate_x(BP* bpp, float t);
float calculate_y(BP* bpp, float t);


#endif

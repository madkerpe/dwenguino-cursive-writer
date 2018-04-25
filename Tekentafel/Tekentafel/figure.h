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

typedef struct {
	unsigned int amount_of_bp;
	BP* bp_list;
} figure;

figure* create_figure(unsigned int new_amount_of_bp, BP* new_bp_array);
BP* get_BP_list(figure* current_figure);
void delete_figure(figure* fp);

#endif

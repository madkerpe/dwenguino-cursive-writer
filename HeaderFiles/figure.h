#ifndef DEF_FIGURE
#define DEF_FIGURE

typedef struct{
	float P0[2];
	float P1[2];
	float P2[2];
} BP;

BP* create_BP(float P0x, float P0y, float P1x, float P1y, float P2x, float P2y);

float calculate_x(BP* bpp, float t);
float calculate_y(BP* bpp, float t);

/*
void inverse_kinematics(float x, float y, float* angle_pair);
void draw_BP(BP* current_BP);
void draw_figure(unsigned int array_size, BP* array[]);
*/

void set_x_offset(float dx);

#endif

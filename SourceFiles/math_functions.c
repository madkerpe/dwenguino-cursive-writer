#include "../HeaderFiles/math_functions.h"
#include "../HeaderFiles/constants.h"
#include "math.h"

float my_acos(float x) {
	return (180.0 / PI)*acos(x);
}

float my_atan(float x) {
	return (180.0 / PI)*atan(x);
}

float norm(float x, float y) {
	//return (float)sqrt(x*x + y * y);

	float row[NORM_BUFFER];
	row[0] = 1000;
	float getal = x * x + y * y;

	for (int i = 0; i < NORM_BUFFER - 1; i++) {
		row[i + 1] = (row[i] + (getal / row[i])) / 2;
	}

	return row[NORM_BUFFER - 1];
}

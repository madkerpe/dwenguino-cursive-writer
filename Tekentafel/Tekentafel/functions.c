#include "functions.h"
#include "constants.h"

float my_sin(float x) {
	//correct
	return sin(x*PI / 180);
}

float my_cos(float x) {
	//correct
	return cos(x*PI / 180);
}

float my_acos(float x) {
	//correct
	return (180.0 / PI)*acos(x);
}

float my_atan(float x) {
	//correct
	return (180.0 / PI)*atan(x);
}

float* inverse_kinematics(float x, float y) {
	//correct

	float distance = sqrt(x*x + y * y);

	float temp1 = (ARMLENGTE_1 * ARMLENGTE_1 + distance * distance - ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * distance);
	float hoek1 = my_acos(temp1) + my_atan(y / x);
	printf("hoek 1 = %f\n", hoek1);

	float temp2 = (ARMLENGTE_1 * ARMLENGTE_1 - distance * distance + ARMLENGTE_2 * ARMLENGTE_2) / (2 * ARMLENGTE_1 * ARMLENGTE_2);
	float hoek2 = my_acos(temp2);
	printf("hoek 2 = %f\n", hoek2);

	float angle_pair[2] = { hoek1, hoek2 };
	return angle_pair;
}
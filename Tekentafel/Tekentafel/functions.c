#include "functions.h"
#include "constants.h"
#include "math.h"

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

float norm(float x, float y) {
	return (float)sqrt(x*x + y * y);
}
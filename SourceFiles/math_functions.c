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
	return (float)sqrt(x*x + y * y);
}

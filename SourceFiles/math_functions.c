/*MARIJN DE KERPEL - ELIEN LEDEGEN*/

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
	//Babylonian method to approximate the square root
	float row[NORM_BUFFER];
	row[0] = 1000; //random number, higher than the square root
	float getal = x * x + y * y;

	for (int i = 0; i < NORM_BUFFER - 1; i++) {
		row[i + 1] = (row[i] + (getal / row[i])) / 2;
	}

	return row[NORM_BUFFER - 1];
}

#ifndef DEF_SETUP
#define DEF_SETUP

#include <stdlib.h>

#include <avr/io.h>
#include <util/delay.h>

#include "dwenguinoBoard.h"
#include "dwenguinoLCD.h"
#include "constants.h"

void setup_LCD();
void setup_interrupts();
void setup_timer_interrupts();

#endif

/* Controller
		has the code for the user interface (the input side).  This polls the joy-
		stick and sets values, or calls functions as needed
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* hardware platform libraries */
#include <mbed.h>

/* asteroids */
#include "model.h"
#include "asteroids.h"

/* Joystick 5-way switch
*/
typedef enum position { left,down,right,up,centre }btnId_t;
DigitalIn joystick[] = {P5_0, P5_1, P5_4, P5_2, P5_3};
bool jsPrsdAndRlsd(btnId_t b);

void controls(void)
{
	if (jsPrsdAndRlsd(up)) {
		joyUp = true;
		joyLeft = false;
		joyRight = false;
	}
	
	if (jsPrsdAndRlsd(down)) {
		joyDown = true;
	}
	
	if (jsPrsdAndRlsd(left)) {
		joyLeft = true;
		joyRight = false;
	}
		
	
	if (jsPrsdAndRlsd(right)) {
		joyRight = true;
		joyLeft = false;
	}
	
	if (jsPrsdAndRlsd(centre)) {
		createMissile(missiles);
	}
}

bool jsPrsdAndRlsd(btnId_t b) {
	bool result = false;
	uint32_t state;
	static uint32_t savedState[5] = {1,1,1,1,1};
	//initially all 1s: nothing pressed
	state = joystick[b].read();
	if ((savedState[b] == 0) && (state == 1)) {
		result = true;
	}
	savedState[b] = state;
	return result;
}

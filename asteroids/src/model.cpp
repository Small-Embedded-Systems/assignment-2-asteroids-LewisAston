/* Asteroids model
		handles updating the game state, moving the objects, and handling collisions
*/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#include "model.h"
#include "utils.h"
#include "asteroids.h"



/* If you want to initialise a linked list:
    You'll have to replace node_t with the right type

typedef struct node {
    some data per node
    struct node *next;
} node_t;
const size_t MAXSize = 10;
node_t data[MAXSize];
node_t *initialise()
{
    int c;
    for(c=0 ; c<(MAXSize-1) ; c++){
        data[c].next = &data[c+1];
    }
    data[c].next = NULL;
    return data;
}
*/



int x, y, x1, y1, x2, y2;
    int radius = 15;
    float angle = 0.0;
    float angle_stepsize = 0.025;
		/*double accel = 100;
    double accel_stepsize = 1;*/
		float PI = 3.1415926f;
		float velX;
		float velY;

void shipSpin() {
        // calculate x, y from a vector with known length and angle
        x = radius * cos (angle);
        y = radius * sin (angle);
				x1 = radius * cos (angle+ 3.83972);
        y1 = radius * sin (angle+ 3.83972);
				x2 = radius * cos (angle+ 2.44346);
        y2 = radius * sin (angle+ 2.44346);
	
				shipTipX = x+shipX;
				shipTipY = y+shipY;
				shipLftCrnrX = x1+shipX;
				shipLftCrnrY = y1+shipY;
				shipRghtCrnrX = x2+shipX;
				shipRghtCrnrY = y2+shipY;

        //angle += angle_stepsize;
	
				if (angle > 2 * PI) {
						angle = 0.1;
				}
				if (angle < 0 ) {
						angle = (2 * PI) - 0.1;
				}
				if (joyLeft == true) {
						angle += angle_stepsize;
				}
				if (joyRight == true) {
						angle -= angle_stepsize;
				}
				if (joyDown == true) {
						joyLeft = false;
						joyRight = false;
						joyDown = false;
						joyUp = false;
						angle = angle;
				}		
}
		
void shipThrust() {
		/*if (accel > 7 && joyUp == true) {
			accel -= accel_stepsize;
		}
		if (accel < 100 && joyUp == false) {
			accel += accel_stepsize;
		}*/
		velX = (10 * cos (angle));
		velY = (10 * sin (angle));
		if (joyUp == true /*|| accel !=100*/) {
				shipX += (velX / 20 /*accel*/);
				shipY += (velY / 20 /*accel*/);
		}	
}

void hitRock() {
	if (shields > 0 && rockX + 8 >= shipX -14 && shipX +8 <= rockX +14 && rockY >= shipY -14 && rockY <= shipY +14 ) {
		rockX = 140;
		shields--;
	} else if (shields < 1 && rockX + 8 >= shipX -14 && shipX +8 <= rockX +14 && rockY >= shipY -14 && rockY <= shipY +14 ) {
		rockX = 140;
		lives--;
	}
}

void onScreen() {
	if(shipY <= -10) {
		shipY = 272;
	}	else if(shipY >=282) {
		shipY = 0;
	}
	if(shipX <= -10) {
		shipX = 480;
	} else if(shipX >= 490) {
		shipX = 0;
	}
}

void physics(void) {
		onScreen();
		shipSpin();
		shipThrust();
		hitRock();
}


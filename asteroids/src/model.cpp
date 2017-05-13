/* Asteroids model
		handles updating the game state, moving the objects, and handling collisions
*/
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "model.h"
#include "utils.h"
#include "asteroids.h"

int x, y, x1, y1, x2, y2;
    int radius = 15;
    float angle = 0.0;
    float angle_stepsize = 0.025;
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
		velX = (10 * cos (angle));
		velY = (10 * sin (angle));
		if (joyUp == true) {
				shipX += (velX / 20);
				shipY += (velY / 20);
		}	
}

void shipOnScreen() {
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

void createRock(rock_t* head) {
	if (rockCount <5) {
		rock_t* current = head;
		while (current->next !=NULL) {
			current = current->next;
		}
		current->next = (rock_t*)malloc(sizeof(rock_t));
		current->next->p.x = randrange(10, 470);
		current->next->p.y = randrange(10, 260);
		current->next->v.x = randrange(-1, 2);
		current->next->v.y = randrange(-1, 2);
		if (current->next->v.x == 0 && current->next->v.y == 0) {
			current->next->v.x = 1;
			current->next->v.y = 1;
		}
		current->next->next = NULL;
		rockCount++;		
	}
}

void rockWrap(rock_t* head) {
	rock_t* current = head;
		if (current !=NULL) {
			current->p.x += current->v.x;
			current->p.y += current->v.y;
		
			if (current->p.x > 500) {
				current->p.x = -20;
			}
			if (current->p.x < -20) {
				current->p.x = 500;
			}
			if (current->p.y > 290) {
				current->p.y = -20;
			}
			if (current->p.y < -20) {
				current->p.y = 290;
			}
		current = current->next;
		rockWrap(current);
	}
}

void rockHit (rock_t* head) {
	rock_t* current = head;
		if (current !=NULL) {
			if (current->p.x < shipX +10 && current->p.x > shipX - 10 && current->p.y > shipY -10 && current->p.y < shipY + 10) {
				current->p.x = randrange(10, 470);
				current->p.y = randrange(10, 260);
				shields--;
				if (shields < 0) {
					lives--;
					shields = lives;
				} if (lives <=0) {
						gameOver();
				}
			}
		current = current->next;
		rockHit(current);
		}
}

void createMissile(shot_t* headS) {
	shot_t* currentS = headS;
	while (currentS->next !=NULL) {
			currentS = currentS->next;
	}
	currentS->next = (shot_t*)malloc(sizeof(shot_t));
	currentS->next->pS.x = shipTipX;
	currentS->next->pS.y = shipTipY;
	currentS->next->vS.x = velX;
	currentS->next->vS.y = velY;
	currentS->next->next = NULL;
	shotCount++;
}

void missileMethods(shot_t* headS) {
	shot_t* currentS = headS;
	while (currentS !=NULL) {
		currentS-> pS.x += currentS-> vS.x;
		currentS-> pS.y += currentS-> vS.y;
		currentS=currentS->next;
	}
}

void shootRock(rock_t* head, shot_t* headS) {
	rock_t* current = head;
	shot_t* currentS = headS;
	if (current !=NULL || currentS !=NULL) {
			if (currentS->pS.x < current->p.x +8 && currentS->pS.x > current->p.x - 8 && currentS->pS.y > current->p.y -8 && currentS->pS.y < current->p.y + 8) {
				current->p.x = randrange(10, 470);
				current->p.y = randrange(10, 260);
				score = score + 10;
		}
		current=current->next;
		currentS=currentS->next;
	}
}


void physics(void) {
		createRock(asteroids);
		rockWrap(asteroids);
		rockHit(asteroids);
		missileMethods(missiles);
		shootRock(asteroids, missiles);
		shipOnScreen();
		shipSpin();
		shipThrust();

}


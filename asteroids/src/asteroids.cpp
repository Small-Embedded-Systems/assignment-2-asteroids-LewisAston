/* Asteroids
    The game, it includes main and declares any global variables needed
		for the game state
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"
#include "utils.h"

/* Game state */
float elapsed_time; 
int   score;
int   lives;
int 	shields;
int frames;
int rockCount;
int shotCount;
struct ship player;
double shipX = 240;
double shipY = 146;
double rockX = 100;
double rockY = 100;
double shipTipX = shipX;
double shipTipY = shipY-15;
double shipRghtCrnrX = shipX +7;
double shipRghtCrnrY = shipY +10;
double shipLftCrnrX = shipX -7;
double shipLftCrnrY = shipY +10;
rock_t *asteroids;
shot_t *missiles;

float Dt = 0.01f;

Ticker model, view, controller;

bool paused = true;
/* The single user button needs to have the PullUp resistor enabled */
DigitalIn userbutton(P2_10,PullUp);
//initialises both asteroids and missile lists
void initialise() {
	asteroids = static_cast<rock_t*>(malloc(sizeof(rock_t)));
	asteroids->next = NULL;
	
	missiles = static_cast<shot_t*>(malloc(sizeof(shot_t)));
	missiles->next = NULL;
}

int main() {
		srand(time(0));
		initialise();
    init_DBuffer();

    view.attach( draw, 0.025);
    model.attach( physics, Dt);
    controller.attach( controls, 0.1);
    
		score = 0;
    lives = 3;
		shields = 3;
}

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

/* Game state */
float elapsed_time; 
int   score;
int   lives;
int 	shields;
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

float Dt = 0.01f;

Ticker model, view, controller;

bool paused = true;
/* The single user button needs to have the PullUp resistor enabled */
DigitalIn userbutton(P2_10,PullUp);
int main()
{

    init_DBuffer();
    

    view.attach( draw, 0.025);
    model.attach( physics, Dt);
    controller.attach( controls, 0.1);
    
    lives = 3;
		shields = 3;
    
    /* Pause to start */
    while( userbutton.read() ){ /* remember 1 is not pressed */
        paused=true;
        wait_ms(100);
    }
    paused = false;
    
    while(true) {
        
        
        
    }
}

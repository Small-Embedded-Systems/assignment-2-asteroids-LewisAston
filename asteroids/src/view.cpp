/* Asteroids view
		Handles all the drawing of the screen.  I can declare the display variable
		in here, as it isn’t needed in other parts of the program
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

#include "asteroids.h"
#include "model.h"
#include "utils.h"
#include "objects.h"

Display *graphics = Display::theDisplay();

const colour_t background = rgb(0,51,102); /* Midnight Blue */


/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
    uint16_t *bufferbase = graphics->getFb();
    uint16_t *nextbuffer = bufferbase+ (480*272);
    LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
    uint16_t *buffer = graphics->getFb();
    graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
    LPC_LCD->UPBASE = (uint32_t)buffer;
}
//draws game info
void drawInfo() {
		graphics->setCursor(400,15);
		graphics->printf("Score: %d", score);
		graphics->setCursor(210,15);
		graphics->printf("ASTEROIDS");
		for (int i=1;i<=lives;i++){
			graphics->drawTriangle(i*20,10,(i*20)-5,25,(i*20)+5,25,WHITE);
		}
}
//draws ship using lines for prefered design
void drawShip() {
		graphics->drawLine(shipTipX, shipTipY, shipRghtCrnrX, shipRghtCrnrY, WHITE); 
		graphics->drawLine(shipX, shipY, shipRghtCrnrX, shipRghtCrnrY, WHITE); 
		graphics->drawLine(shipLftCrnrX, shipLftCrnrY, shipX, shipY, WHITE); 
		graphics->drawLine(shipLftCrnrX, shipLftCrnrY, shipTipX, shipTipY, WHITE); 
}
//draws rock using 16 bit bitmap
void drawRock(rock_t *head) {
	rock_t* current = head;
	while ( current !=NULL) {
		graphics->drawBitmap(current->p.x,current->p.y,rock,16,16,WHITE);
		current = current->next;
	}
}
//draws missile as small circle
void drawMissile(shot_t *headS) {
	shot_t* currentS = headS;
	while ( currentS !=NULL) {
		graphics->fillCircle(currentS->pS.x, currentS->pS.y, 2, WHITE);
		currentS = currentS->next;
	}
}
//draws neccessary amount of shields, automatically changes if shields is set as something different
void drawShield() {
	for (int i=1;i<=shields;i++){
		graphics->drawCircle (shipX, shipY, 14 + (i*3), WHITE);
  }
}
//gameover screen after loosing all lives
void gameOver() {
	graphics->fillScreen(BLACK);
	graphics->setTextSize(4);
	graphics->setCursor(160,40);
	graphics->printf("GAME OVER");
	graphics->setTextSize(2);
	graphics->setCursor(180,100);
	graphics->printf("Your score = %d", score);
	graphics->setCursor(120,170);
	graphics->printf("press RESET to start again");
}

void draw(void)
{
	if (lives > 0) {
    graphics->fillScreen(background);
		drawInfo();
		drawShip();
		drawShield();
		drawRock(asteroids);
    drawMissile(missiles);
	} else {
		gameOver();
	}
	swap_DBuffer();
}

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

void drawInfo() {
		
		graphics->setCursor(400,15);
		graphics->printf("Score: ");
		graphics->setCursor(210,15);
		graphics->printf("ASTEROIDS");
		for (int i=1;i<=lives;i++){
		graphics->drawTriangle(i*20,10,(i*20)-5,25,(i*20)+5,25,WHITE);
		}
}

void drawShip() {
		graphics->drawLine(shipTipX, shipTipY, shipRghtCrnrX, shipRghtCrnrY, WHITE); 
		graphics->drawLine(shipX, shipY, shipRghtCrnrX, shipRghtCrnrY, WHITE); 
		graphics->drawLine(shipLftCrnrX, shipLftCrnrY, shipX, shipY, WHITE); 
		graphics->drawLine(shipLftCrnrX, shipLftCrnrY, shipTipX, shipTipY, WHITE); 
		
		/*graphics->setCursor(20,100);
		graphics->printf("angle = %f", angle);*/
}

void drawShield()
{
	for (int i=1;i<=shields;i++){
		graphics->drawCircle (shipX, shipY, 14 + (i*3), WHITE);
  }
}



void draw(void)
{
    graphics->fillScreen(background);
		drawInfo();
		drawShip();
		drawShield();
		
    swap_DBuffer();
}

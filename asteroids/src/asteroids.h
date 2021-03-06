/* Game state */
/*
		declares  common  datatypes  needed  for  the  game,  and  makes  the  data
		available to other modules via the extern type qualifier.
*/

extern float 	elapsed_time; /* time this ship has been active */
extern int   	score;        /* total score so far */
extern int   	lives;        /* lives remaining */
extern int	 	shields;
extern int 	 	rockCount;
extern int 	 	shotCount;
extern int 	 	frames;
extern double shipX;
extern double shipY;
extern double shipTipX;
extern double shipTipY;
extern double shipRghtCrnrX;
extern double shipRghtCrnrY;
extern double shipLftCrnrX;
extern double shipLftCrnrY;

extern struct ship player;

extern struct rock_t *asteroids; /* array of rocks / pointer to linked-list */
extern struct shot_t *missiles;  /* array of missiles / pointer to linked-list */

extern const float Dt; /* Time step for physics, needed for consistent motion */

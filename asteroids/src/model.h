/* Asteroids Model
		exposes the parts of the model needed elsewhere. Such as the fire
		function called by the controller.
*/
struct point {
    float x,y;
};
typedef struct point coordinate_t;
typedef struct point vector_t;

/* Some initial struct types if you want to use them */
struct ship {
    coordinate_t p;
    vector_t     v;
};

//rock struct 
typedef struct rock_t {
    coordinate_t p;
		vector_t v;
    struct rock_t* next; //iterates next rock in list
}rock_t; //recursive op
//shot struct
typedef struct shot_t {
    coordinate_t pS;
		vector_t vS;
    struct shot_t* next; //iterates next shot in list
}shot_t; //recursive op

extern bool joyUp;
extern bool joyLeft;
extern bool joyRight;
extern bool joyDown;
void shipSpin();
void shipThrust();
void gameOver();
extern float angle;
void physics(void);
void createMissile(shot_t *headS);

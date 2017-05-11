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

/* initial struts for building linked lists */
struct rock {
    coordinate_t p;
    struct rock *next;
};

struct missile {
    coordinate_t p;
    struct missile *next;
};

extern bool joyUp;
extern bool joyLeft;
extern bool joyRight;
extern bool joyDown;
void shipSpin();
void shipThrust();
extern float angle;
void physics(void);

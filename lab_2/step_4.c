#include "movement.h"

/**
 * step_4.c
 */
int main(void) {
    oi_t *sensor = oi_alloc();

	oi_init(sensor);

    move_forward(sensor, 200);
    
    oi_free(sensor);
	
}

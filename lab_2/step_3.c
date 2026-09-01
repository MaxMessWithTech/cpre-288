#include "movement.h"

/**
 * step_2.c
 */
int main(void) {
    oi_t *sensor = oi_alloc();

	oi_init(sensor);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            move_forward(sensor, 50);
            turn_cw(sensor, 90);
        }
        
    }
    
    oi_free(sensor);
	
}

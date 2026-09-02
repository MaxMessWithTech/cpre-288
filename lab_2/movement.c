#include "movement.h"

#define FAST_SPEED 150
#define FINE_SPEED 25
#define OFFSET_ANG 0
#define FINE_THRESHOLD_DIS 10       // mm
#define FINE_THRESHOLD_ANG 2       // degrees
#define PRECISION 0.01


int has_collided_left(oi_t *sensor) {
    return sensor->bumpLeft;
}

int has_collided_right(oi_t *sensor) {
    return sensor->bumpRight;
}

int has_collided(oi_t *sensor) {
    return has_collided_left(sensor) || has_collided_right(sensor);
}

void move_forward(oi_t *sensor, int centimeters) {
    oi_setWheels(FAST_SPEED, FAST_SPEED);

    int dist_traveled = 0; 
    
    while (dist_traveled < centimeters * 10) {
		oi_update(sensor);
		dist_traveled += sensor->distance;

        if (has_collided(sensor)) {
            avoid(sensor);
        }
	}

    oi_setWheels(0, 0); // stop
}

void move_backward(oi_t *sensor, int centimeters) {
    oi_setWheels(-FAST_SPEED, -FAST_SPEED);

    int dist_traveled = 0; 
    
    while (dist_traveled < centimeters * 10) {
		oi_update(sensor);
		dist_traveled += sensor->distance;

        if (has_collided(sensor)) {
            avoid(sensor);
        }
	}

    oi_setWheels(0, 0); // stop
}

/**
 * @name Move Internal
 * @brief Moves internally without 
 * @param sensor
 * @param cm positive for forward, negative for backward
 * @private
 */
void move_internal(oi_t *sensor, int cm) {
    const int mod = cm > 0;
    oi_setWheels(mod * FINE_SPEED, mod * FINE_SPEED);

    int dist_traveled = 0; 
    
    while (dist_traveled < cm * 10) {
		oi_update(sensor);
		dist_traveled += sensor->distance;
	}

    oi_setWheels(0, 0); // stop
}

void turn_cw(oi_t *sensor, int degrees) {
    double deg = 0.0;

    oi_setWheels(-FINE_SPEED, FINE_SPEED);
    
    while (deg < degrees - OFFSET_ANG - 15.0) {
		oi_update(sensor);
		deg = deg - sensor->angle;
		// printf("Fast: %f\n", deg);
	}

    oi_setWheels(-25, 25);
    
    while (((double)degrees - (double)OFFSET_ANG - deg) > PRECISION) {
        oi_update(sensor);
        deg = deg - sensor->angle;
        // printf("Slow: %f\n", deg);
    }

    oi_setWheels(0, 0); // stop
    oi_update(sensor);
    printf("Final: %f\n", deg);
}

void turn_ccw(oi_t *sensor, int degrees) {
    oi_setWheels(FINE_SPEED, -FINE_SPEED);

    int deg = 0; 
    
    while (deg < degrees - OFFSET_ANG) {
		oi_update(sensor);
		deg += sensor->angle;
	}

    oi_setWheels(0, 0); // stop
}

void avoid(oi_t *sensor) {
    /* 
        If collided back up 15 cm, turn 90 degrees, move laterally 25cm, then turn 90 degrees forward.
        If the collision occurs with the right bumper, the robot should initially spin 90 degrees to the left. 
        If the collision occurs with the left bumper, the platform should spin 90 degrees to the right.
        If both sensors report a collision, then pick a direction and perform a 90 degree spin.
    */

    // If right is triggered or if both are triggered
    if (has_collided_right(sensor)) {
        move_internal(sensor, -25);
        turn_ccw(sensor, 90);
        move_internal(sensor, 25);
        turn_cw(sensor, 90);
        move_internal(sensor, 25);
    }

    // If left is triggered
    else if (has_collided_right(sensor)) {
        move_internal(sensor, -25);
        turn_cw(sensor, 90);
        move_internal(sensor, 25);
        turn_ccw(sensor, 90);
        move_internal(sensor, 25);
    }

    // Otherwise nothing was triggered so do nothing
}

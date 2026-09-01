#include "movement.h"

#define MAX_SPEED 500
#define FINE_SPEED 100
#define FINE_THRESHOLD_DIS 10       // mm
#define FINE_THRESHOLD_ANG 2       // degrees


int has_collided_left(oi_t *sensor) {
    return sensor->bumpLeft;
}

int has_collided_right(oi_t *sensor) {
    return sensor->bumpRight;
}

int has_collided(oi_t *sensor) {
    return has_collided_left || has_collided_right;
}

void move_forward(oi_t *sensor, int centimeters) {
    oi_setWheels(MAX_SPEED, MAX_SPEED);

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
    oi_setWheels(-MAX_SPEED, -MAX_SPEED);

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
 * @private
 */
void move_internal(oi_t *sensor, int cm) {
    const int mod = cm > 0;
    oi_setWheels(mod * MAX_SPEED, mod * MAX_SPEED);

    int dist_traveled = 0; 
    
    while (dist_traveled < cm * 10) {
		oi_update(sensor);
		dist_traveled += sensor->distance;
	}

    oi_setWheels(0, 0); // stop
}

void turn_cw(oi_t *sensor, int degrees) {
    oi_setWheels(-MAX_SPEED, MAX_SPEED);

    int deg = 0; 
    
    while (deg < degrees) {
		oi_update(sensor);
		deg += sensor->angle;
	}

    if (deg > degrees)

    oi_setWheels(0, 0); // stop
}

void turn_ccw(oi_t *sensor, int degrees) {
    oi_setWheels(MAX_SPEED, -MAX_SPEED);

    int deg = 0; 
    
    while (deg < degrees) {
		oi_update(sensor);
		deg += sensor->angle;
	}

    if (deg > degrees)

    oi_setWheels(0, 0); // stop
}

void avoid(oi_t *sensor) {
    // If collided back up 15 cm, turn 90 degrees, move laterally 25cm, then turn 90 degrees forward.
    // If the collision occurs with the right bumper, the robot should initially spin 90 degrees to the left. 
    // If the collision occurs with the left bumper, the platform should spin 90 degrees to the right.
    // If both sensors report a collision, then pick a direction and perform a 90 degree spin.

    // If left is triggered or if both are triggered
    if (has_collided_left(sensor)) {

        return;
    }

    if (has_collided_right(sensor)) {

    }
}
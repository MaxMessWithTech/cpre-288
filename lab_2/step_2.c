#include "cyBot_uart.h"
#include "lcd.h"
#include "open_interface.h"
#include "Timer.h"

/**
 * step_2.c
 */
int main(void) {

	oi_t *sensor_data = oi_alloc();

	oi_init(sensor_data);

	double sum = 0;

	oi_setWheels(500, 500); // move forward; full speed

	while (sum < 1000) {
		oi_update(sensor_data);
		sum += sensor_data->distance;
	}
	
	oi_setWheels(0, 0); // stop
	oi_free(sensor_data);
}

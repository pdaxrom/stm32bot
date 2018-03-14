#include "main.h"
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "max7219.h"
#include "hcsr04.h"
#include "movement.h"

#define MOVEMENT_STEPS	16

static MOVEMENT movements[MOVEMENT_STEPS];
static int movements_counter;

int movement_init()
{
	movements_counter = 0;
}

int movement_add(MOVEMENT *m)
{
	if (movements_counter > sizeof(movements)/sizeof(MOVEMENT)) {
		memcpy(&movements[movements_counter], m, sizeof(MOVEMENT));

		movements_counter++;

		return MOVE_OK;
	}

	return MOVE_ERR_FULL_STEPS;
}

int movement_step()
{
	if (sonar_is_ready()) {
		char tmp[40];
		int distance = sonar_distance();
		sprintf(tmp, "Distance = %d\n\r", distance);
		uart_send_string(tmp);
		sonar_start();

		if (distance < 100) {
			moto_command(MOTO_STOP);
		} else {
			moto_command(MOTO_FWD);
		}

		return MOVE_OK;
	} else {
		return MOVE_ERR_SONAR_NOT_READY;
	}
}

#ifndef __MOVEMENT_H__
#define __MOVEMENT_H__

enum MOVEMENT_TYPE {
	MOVE_STOP = 0,
	MOVE_FORWARD,
	MOVE_BACKWARD,
	MOVE_TURN_LEFT,
	MOVE_TUNR_RIGHT
};

enum MOVEMENT_ERROR {
	MOVE_OK = 0,
	MOVE_ERR_FULL_STEPS,
	MOVE_ERR_NO_POWER,
	MOVE_ERR_SONAR_NOT_READY,
	MOVE_ERR_LEFT_WHEEL_BLOCKED,
	MOVE_ERR_RIGHT_WHEEL_BLOCKED,
	MOVE_ERR_FORWARD,
	MOVE_ERR_BACKWARD,
	MOVE_ERR_TURN_LEFT,
	MOVE_ERR_TURN_RIGHT
};

typedef struct {
	short type;
	short time;
	short data;
} MOVEMENT;

int movement_init();

int movement_add(MOVEMENT *m);

int movement_step();

#endif

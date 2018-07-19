#ifndef USER_MOTOR_OPERATION_H
#define USER_MOTOR_OPERATION_H

#include "motor_device.h"

/*
static void run_all_motors(my_motor_t *instance){
	motor_device_run(instance);
}
*/

my_motor_t* find_motor_instance(motor_can_receive_id id);


#endif


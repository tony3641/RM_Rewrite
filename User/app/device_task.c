#include "device_task.h"
#include "motor_device.h"
#include "cmsis_os.h"

extern my_motor_t *motors[];

void device_task(const void* argu){
		all_motors(motor_device_init);
		all_motors(motor_device_reset);
	
		while(1){
			all_motors(motor_device_run);
			motors_can_communicateA();
			motors_can_communicateB();
			osDelay(5);
	}
}


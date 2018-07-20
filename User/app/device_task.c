#include "device_task.h"
#include "motor_device.h"
#include "cmsis_os.h"

void device_task(const void* argu){
		all_motors(motor_device_init);
		while(1){
			all_motors(motor_device_run);
			osDelay(5);
	}
}


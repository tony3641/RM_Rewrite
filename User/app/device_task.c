#include "device_task.h"
#include "motor_device.h"
#include "cmsis_os.h"

extern my_motor_t *motors[];

my_motor_t *ma[4];
	
my_motor_t *mb[4];

void device_task(const void* argu){
	
		ma[0]=find_motor_by_id(CAN_M1_ID);
		ma[1]=find_motor_by_id(CAN_M2_ID);
		ma[2]=find_motor_by_id(CAN_M3_ID);
		ma[3]=find_motor_by_id(CAN_M4_ID);

	
	
		mb[0]=find_motor_by_id(CAN_M5_ID),
		mb[1]=find_motor_by_id(CAN_M6_ID),
		mb[2]=find_motor_by_id(CAN_M7_ID),
		mb[3]=find_motor_by_id(CAN_M8_ID);

		all_motors(motor_device_init);
		all_motors(motor_device_reset);
	
		while(1){
			all_motors(motor_device_run);
			motors_can_communicateA();
			motors_can_communicateB();
			osDelay(5);
	}
}


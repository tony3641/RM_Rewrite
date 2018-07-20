#include "motor_device.h"
#include "rm_hal_lib.h"
#include "pid.h"
#include "motor_operation.h"

#define motor &(my_motor_t)

#define chassis_lf motors[0]
#define chassis_lb motors[1]
#define chassis_rf motors[2]
#define chassis_rb motors[3]



my_motor_t *motors[4]={
motor{CAN_M1_ID,CAN_SEND_A},
motor{CAN_M2_ID,CAN_SEND_A},
motor{CAN_M3_ID,CAN_SEND_A},
motor{CAN_M4_ID,CAN_SEND_A},
};

void motor_device_init(my_motor_t *instance){
	if(1)//is 3508
	{
		pid_init(instance->pid_position,7000,2333,1.9,0,50);
		pid_init(instance->pid_speed,7000,2333,14,0.0381,8.6);
	}
	else if(0)//is 2006
	{
		pid_init(instance->pid_position,7000,2333,0.85,0.0003,20);
		pid_init(instance->pid_speed,7000,2333,12,0.0001,8);
	}
}

void motor_device_run(my_motor_t *instance) {
	
	
	switch(instance->mode){
		case open_loop:
			break;
		case speed_close_loop:
			*instance->current=pid_calc(instance->pid_speed,instance->motor_mesure->speed_rpm,instance->target_speed);
			break;
		case position_close_loop:
			*instance->current=pid_calc(instance->pid_position,instance->motor_mesure->total_angle,instance->target_position);
			break;
	}
	
	motor_device_can_communicate(instance,*instance->current);
}

static void motor_device_can_communicate(my_motor_t *instance, int16_t current) {
    static uint8_t _data[8];

//    data[0] = 0;
//    data[1] = 0;
//    data[2] = 0;
//    data[3] = 0;
//    data[4] = 0;
//    data[5] = 0;
//    data[6] = 0;
//    data[7] = 0;

    _data[to_index(instance->receive_id)] = current >> 8;
    _data[to_index(instance->receive_id) + 1] = current;

    write_can(CAN_1_CHANNEL_ID, confirm_group(instance) == 1 ? CAN_SEND_A : CAN_SEND_B, _data);
}

static short to_index(motor_can_receive_id id) {

    switch (id) {
        case CAN_M5_ID:
        case CAN_M1_ID:
            return 0;
        case CAN_M6_ID:
        case CAN_M2_ID:
            return 2;
        case CAN_M7_ID:
        case CAN_M3_ID:
            return 4;
        case CAN_M4_ID:
        case CAN_M8_ID:
            return 6;
        default:
            return 23333;
    }

}

static short confirm_group(my_motor_t *instance) {
    motor_can_receive_id id = instance->receive_id;
    if (id == CAN_M1_ID || id == CAN_M2_ID || id == CAN_M3_ID || id == CAN_M4_ID)
        return 1;
    else return 2;
}

motor_can_receive_id get_from_receive_id(uint32_t recv_id) {
    switch (recv_id) {
        case 0x201:
            return CAN_M1_ID;
        case 0x202:
            return CAN_M2_ID;
        case 0x203:
            return CAN_M3_ID;
        case 0x204:
            return CAN_M4_ID;
        case 0x205:
            return CAN_M5_ID;
        case 0x206:
            return CAN_M6_ID;
        case 0x207:
            return CAN_M7_ID;
        case 0x208:
            return CAN_M8_ID;
				default:
					return NULL;
    }
}


void all_motors(void (*application)(my_motor_t*)){
	for(int i =0;i<=sizeof(motors);i++)
		(*application)(motors[i]);
}

my_motor_t* find_motor_instance(motor_can_receive_id id){
	for(int i=0;i<=sizeof(motors);i++)
	 if(motors[i]->receive_id==id)
		 return motors[i];
	 else return NULL;
 }


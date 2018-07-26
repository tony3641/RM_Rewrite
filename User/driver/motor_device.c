#include "motor_device.h"
#include "rm_hal_lib.h"
#include "pid.h"
#include "motor_operation.h"
#include <string.h>

my_motor_t default_motor={.current=0};

my_motor_t motors[8];

//my_motor_t *motors_p[8];

extern moto_measure_t encoders[8];

void motors_array_init(void){
	motors[7]=new_motor{CAN_M8_ID,"3508"};
	
	for(int i=0;i<7;i++)
	{
		//motors_p[i]=&motors[i];
		motors[i].motor_mesure=&encoders[i];
	}
	
	
}


void motor_device_init(my_motor_t *instance){
	
	if(strcmp(instance->model,"3508")==0)
	{
		pid_init(&instance->pid_position,7000,2333,1.9,0,50);
		pid_init(&instance->pid_speed,7000,2333,14,0.0381,8.6);
	}
	else if(strcmp(instance->model,"2006")==0)
	{
		pid_init(&instance->pid_position,7000,2333,0.85,0.0003,20);
		pid_init(&instance->pid_speed,7000,2333,12,0.0001,8);
	}
}

void motor_device_run(my_motor_t *instance) {
	
	switch(instance->mode){
		case open_loop:
			break;
		case speed_close_loop:
			instance->current=pid_calc(&instance->pid_speed,instance->motor_mesure->speed_rpm,instance->target_speed);
			break;
		case position_close_loop:
			instance->current=pid_calc(&instance->pid_position,instance->motor_mesure->total_angle,instance->target_position);
			break;
	}
	
}

void motor_device_reset(my_motor_t *instance){
	instance->mode=open_loop;
	instance->target_position=0;
	instance->target_speed=0;
	instance->current=0;
}

//extern my_motor_t *ma[4];
	
//extern my_motor_t *mb[4];
	
void motors_can_communicateA(void){
	static uint8_t _data[8];
	
	_data[0]=motors[0].current>>8;
	_data[1]=motors[0].current;
	_data[2]=motors[1].current>>8;
	_data[3]=motors[1].current;
	_data[4]=motors[2].current>>8;
	_data[5]=motors[2].current;
	_data[6]=motors[3].current>>8;
	_data[7]=motors[3].current;
	
	write_can(CAN_1_CHANNEL_ID,CAN_SEND_A,_data);
}

void motors_can_communicateB(void){
	static uint8_t _data[8];

	
	_data[0]=motors[4].current>>8;
	_data[1]=motors[4].current;
	_data[2]=motors[5].current>>8;
	_data[3]=motors[5].current;
	_data[4]=motors[6].current>>8;
	_data[5]=motors[6].current;
	_data[6]=motors[7].current>>8;
	_data[7]=motors[7].current;
	
	write_can(CAN_1_CHANNEL_ID,CAN_SEND_B,_data);
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
					return CAN_DEEP_DARK_ID;
    }
}



void all_motors(void (*application)(my_motor_t*)){
	for(int i =0;i<=sizeof(motors);i++)
		(*application)(&motors[i]);
}

my_motor_t* find_motor_by_id(motor_can_receive_id id){
	for(int i=0;i<=sizeof(motors);i++)
	 if(motors[i].receive_id==id)
		 return &motors[i];
	return &default_motor;
}


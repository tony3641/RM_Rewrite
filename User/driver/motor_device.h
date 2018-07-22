#ifndef USER_MOTOR_DEVICE_H
#define USER_MOTOR_DEVICE_H

#include "can_device.h"
#include "pid.h"

#define chassis_lf motors[0]
#define chassis_lb motors[1]
#define chassis_rf motors[2]
#define chassis_rb motors[3]

#define new_motor (my_motor_t)

typedef enum {
    CAN_M1_ID = 0x201,
    CAN_M2_ID = 0x202,
    CAN_M3_ID = 0x203,
    CAN_M4_ID = 0x204,
    CAN_M5_ID = 0x205,
    CAN_M6_ID = 0x206,
    CAN_M7_ID = 0x207,
    CAN_M8_ID = 0x208,
		CAN_DEEP_DARK_ID=0x233
} motor_can_receive_id;

typedef enum {
    CAN_SEND_A = 0x200,
    CAN_SEND_B = 0x1ff
} motor_can_send_id;

typedef enum {
    CAN_1_CHANNEL_ID = 1,
    CAN_2_CHANNEL_ID = 2
} can_channel;

typedef enum {
    open_loop,
    speed_close_loop,
    position_close_loop
} motor_mode;

typedef struct {

    motor_can_receive_id receive_id;

			
		char model[4];
	  //motor_can_send_id send_id;
	
    //can_channel channel;
		
		int16_t current;
	
    //close loop
		motor_mode mode;
    int target_speed;
    int target_position;
    pid_t *pid_position;
    pid_t *pid_speed;

    //reference
    moto_measure_t *motor_mesure;
} my_motor_t;

void motors_can_communicateA(void);

void motors_can_communicateB(void);

//static short to_index(motor_can_receive_id id);

//static short confirm_group(my_motor_t *instance);

motor_can_receive_id get_from_receive_id(uint32_t recv_id);

void all_motors(void (*application)(my_motor_t*));

void motor_device_run(my_motor_t *instance);

void motor_device_init(my_motor_t *instance);

void motor_device_reset(my_motor_t *instance);

my_motor_t* find_motor_by_id(motor_can_receive_id id);

void motors_array_init(void);

#endif

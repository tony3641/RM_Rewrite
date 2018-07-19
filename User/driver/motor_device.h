#ifndef USER_MOTOR_DEVICE_H
#define USER_MOTOR_DEVICE_H

#include "can_device.h"
#include "pid.h"

typedef enum {
    CAN_M1_ID = 0x201,
    CAN_M2_ID = 0x202,
    CAN_M3_ID = 0x203,
    CAN_M4_ID = 0x204,
    CAN_M5_ID = 0x205,
    CAN_M6_ID = 0x206,
    CAN_M7_ID = 0x207,
    CAN_M8_ID = 0x208,
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
    motor_can_send_id send_id;

    can_channel channel;
		
		int16_t *current;
	
    //close loop
		motor_mode mode;
    int target_speed;
    int target_position;
    pid_t *pid_position;
    pid_t *pid_speed;

    //reference
    moto_measure_t *motor_mesure;
} my_motor_t;


static void motor_device_can_communicate(my_motor_t *instance, int16_t current);

static short to_index(motor_can_receive_id id);

static short confirm_group(my_motor_t *instance);

motor_can_receive_id get_from_receive_id(uint32_t recv_id);

static void all_motors(void (*application)(my_motor_t*));

void motor_device_run(my_motor_t *instance);

#endif

#include "execute_task.h"
//#include "can_device.h"
//#include "uart_device.h"
#include "cmsis_os.h"
//#include "pid.h"
#include "sys.h"

#include "motor_device.h"

//uint8_t test_key_value;
//extern uint8_t test_servo;

//uint16_t servo_angle = 1000;

extern my_motor_t *motors[];

void execute_task(const void* argu)
{
	/*
	//测试电机初始化	
   test_moto_init();

   while(1)
  {
   //测试电机控制程序
    test_moto_control();
		
		if(rc.sw2 == 3)
			{
		   test_servo=1;
			}
   
		else
		  {
			(test_servo =0);
		  }
			
    osDelay(5);
  }
	*/
	
	//motors[0]->mode=position_close_loop;
	//motors[0]->target_position=300;
	motors[0]->current=1000;

	
}

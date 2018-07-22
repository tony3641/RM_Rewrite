#include "execute_task.h"
//#include "can_device.h"
//#include "uart_device.h"
#include "cmsis_os.h"
//#include "pid.h"
#include "sys.h"
#include "motor_device.h"


extern my_motor_t *motors_p[];

int state_number;

void execute_task(const void* argu)
{
	while(1){
		switch(state_number){
			case 0:
				motors_p[0]->current=1000;
				jump_to(233);
				break;
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			default:
				osDelay(5);
				break;
		}
	}
}


void delay_us(uint32_t time)
{
  uint32_t i=8*time;
  while(i--);
}


void jump_to(int number){
	state_number=number;
}

void condition(int*f()){
	if(*f()==1)
		jump_to(state_number+1);
}




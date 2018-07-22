#include "daemon_task.h"
#include "cmsis_os.h"

void daemon_task(const void* argu)
{
	while(1){
		osDelay(5);
	}
}

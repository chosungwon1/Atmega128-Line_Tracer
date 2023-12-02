#include "motor.h"
#include "usart.h"
#include "sensor.h"

int main(void)
{
	
	usart0_init();
	usart0_printf("\033[H\033[J");
	sensor_init();
	motor_init();
	while(1)
	{
		line_tracer();
		usart0_printf("0x%x,error:%d\n",get_sensor(),get_error());
		_delay_ms(20);
	}
}

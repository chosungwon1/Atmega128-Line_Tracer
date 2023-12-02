#include "sensor.h"
void sensor_init()
{
	DDRB&=0xF0;
	PORTB|=0x0F;
}
int get_sensor()
{
	int value=0;
	
	if (PINB & 0x01) value += 1;
	if (PINB & 0x02) value += 2;
	if (PINB & 0x04) value += 4;
	if (PINB & 0x08) value += 8;
	
	return value;
	
}
int get_error()
{
	int a;
	a=get_sensor();
	
	int Sen1=0,Sen2=0,Sen3=0,Sen4=0;
	//검은색 줄 따라가므로 흰색 줄일때와 반대
	
	if (~a & 0x01) Sen4 = 3;
	if (~a & 0x02) Sen3 = 1;
	if (~a & 0x04) Sen2 = 1;
	if (~a & 0x08) Sen1 = 3;
	
	return abs(Sen4-Sen3)-abs(Sen1-Sen2);
}
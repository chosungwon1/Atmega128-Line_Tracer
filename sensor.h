#ifndef SENSOR_H_
#define SENSOR_H_
#include <avr/io.h>
void sensor_init();
int get_sensor();
int get_error();
#endif /* SENSOR_H_ */
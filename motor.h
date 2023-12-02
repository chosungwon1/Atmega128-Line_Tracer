#ifndef MOTOR_H_
#define MOTOR_H_
#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdlib.h>


ISR(TIMER0_COMP_vect);
ISR(TIMER2_COMP_vect);
void motor_init();
void motor1_pps_init(int pps1);
void motor2_pps_init(int pps2);
void line_tracer();

#endif /* MOTOR_H_ */
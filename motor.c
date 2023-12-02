#include "motor.h"
#include "usart.h"
char motor_out_data[4]={0x01,0x02,0x04, 0x08};
char motor_out_data2[4]={0x08,0x04,0x02, 0x01};
    
volatile unsigned int i=0,i2=0;
 
ISR(TIMER0_COMP_vect)
{
   PORTA &= 0xF0; //토크 해제
   PORTA |= motor_out_data2[i++ % 4];
}
ISR(TIMER2_COMP_vect)
{
   PORTA &= 0x0F;
   PORTA |= (motor_out_data[i2++ % 4]<<4);
}

 void motor_init()//motor 초기화
 {
      cli();
      DDRA|=0xFF;
      TCCR0=0x0F;
      OCR0=255;
      TCCR2=0x0D;
      OCR2=255;
      TCNT2 =0x00;
      TCNT0 =0x00;
      TIMSK &= ~(0x82);
      TIFR &= ~(0x82);
      sei();
 }
void motor1_pps_init(int pps1)
{
    if(pps1<=0)
    {
	    OCR0=0x00;
    }
    else 
    {
	    OCR0=15625/pps1-1;
	    TIMSK |=0x02;
    }
}
void motor2_pps_init(int pps2)
{
	 if(pps2<=0)
	 {
		 OCR2=0x00;
	 }
     else 
	 {
		 OCR2=15625/pps2-1;
		 TIMSK |=0x80;
	 }	
}
void line_tracer()
{
    int error;
    error=get_error();//에러 값을 받아옴
    
  if(error==0)
  {
	  motor1_pps_init(300);
	  motor2_pps_init(300);
  }
  else if(error<0)//왼쪽으로 기울어진 경우이므로 1번 모터 속도를 더 높여야함
  {
	  if(error==-1)motor1_pps_init(300-error*140);
	  else if(error==-2) motor1_pps_init(300-error*120);/*더 많이 기울여져 error값이 크니
	  Gain값 낮춤*/
	  else motor1_pps_init(300-error*100);
  }
  else 
  {
     if(error==1)motor2_pps_init(300+error*140);//기본속도 300, GAIN 100
	 else if (error==2)motor2_pps_init(300+error*120);
	 else motor2_pps_init(300+error*100);
  }
  
}
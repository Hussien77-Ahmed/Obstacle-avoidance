/*******************************************************************/
/*******************************************************************/
/*****************   Author:  shady		********************/
/*****************   Layer:	  MCAL				********************/
/*****************   SWC:     TIMER				********************/
/*****************	 Version: 1.00				********************/
/*******************************************************************/
/*******************************************************************/

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_

#define TIMER0_u8_OVF		0
#define TIMER0_u8_COMP		1
#define ICU_INT             2

#define RISING_EDGE         1
#define FALLING_EDGE        0

#define FORWARDDURATION     24
#define LEFTDURATION     8
#define RIGHTDURATION     40







void TIMER0_voidInit(void);
void TIMER2_voidInit(void);
void Timer2_voidSetTimerValue(uint8 Copy_u8Val);

void Timer0_voidSetTimerValue(uint8 Copy_u8Val);
uint8 TIMER_u8SetCallBack(uint8 Copy_u8IntType,void (*Copy_pvCallBackFunc)(void));
uint8  GTOVCOUNTER();
void  STOVCOUNTER(uint8 COPY);
void  USTRIGGERPIN();
void TIMER1_voidInit(void);
void TIRFWAIT();
void ICPWAIT();
void US_GETDIS(f64 *Distance);
void TIRF_EN();
f64 US_DIS();
void SERVO(uint16 Duration);
void PWM();
void US_CONFIG();
void TIMER1_voidSetValue(uint16 Copy_u16Val);

uint16 TIMER1_u16GetTimerReading(void);
void ICU_voidInit(void);
uint8 ICU_u8SetTrigger(uint8 Copy_u8Trigger);
uint16 ICU_u16GetCaptureReading(void);
void ICU_voidInterruptDisplay(void);


#endif

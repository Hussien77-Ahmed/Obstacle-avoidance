/*******************************************************************/
/*******************************************************************/
/*****************   Author:  shady		********************/
/*****************   Layer:	  MCAL				********************/
/*****************   SWC:     TIMER				********************/
/*****************	 Version: 1.00				********************/
/*******************************************************************/
/*******************************************************************/


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERR_TYPE.h"
#include "util/delay.h"

#include "DIO_interface.h"
#include "TIMER_reg.h"
#include "TIMER_config.h"
#include "TIMER_interface.h"
#include "TIMER_private.h"
#include "DC_interface.h"



uint8 timer0OV=0;

static void (*Timer0Ovf_pvCallBackFunc)(void)=NULL;


static void (*Timer0Comp_pvCallBackFunc)(void)=NULL;

static void (*ICU_pvCaLLBackFunc)(void)=NULL;



f64 US_DIS()
{
	f64 dis;
	USTRIGGERPIN();
	US_CONFIG();
	US_GETDIS(&dis);

	return dis;
}
void  USTRIGGERPIN()
{
	DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_PIN_HIGH);
	_delay_us(10);
	DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN0,DIO_u8_PIN_LOW);
}
void  STOVCOUNTER(uint8 COPY)
{
	timer0OV=COPY;
}
uint8  GTOVCOUNTER()
{
	return timer0OV;

}
void US_GETDIS(f64 *Distance)
{
	uint32 Local_u32_counter=0;
	Local_u32_counter=ICU_u16GetCaptureReading()+(65535*timer0OV);
	*Distance=(f64)Local_u32_counter/932.94;


}
void TIMER0_voidInit(void)
{

	/*Fast PWM Mode*/
	SET_BIT(TCCR0,TCCR0_WGM00);
	SET_BIT(TCCR0,TCCR0_WGM01);

	/*Set on top clear on compare*/
	SET_BIT(TCCR0, TCCR0_COM01);
	CLR_BIT(TCCR0, TCCR0_COM00);

	/*Prescaler: divison by 64*/
	SET_BIT(TCCR0,TCCR0_CS00);
	CLR_BIT(TCCR0,TCCR0_CS01);
	SET_BIT(TCCR0,TCCR0_CS02);




	/*Compare value = 64 for Duty cycle = 25%*/


}
void TIMER2_voidInit(void){

	/*Fast CTC Mode*/
	CLR_BIT(TCCR2,TCCR2_WGM20);
	SET_BIT(TCCR2,TCCR2_WGM21);


	/*Set on top clear on compare*/
	SET_BIT(TCCR2, TCCR2_COM21);
	CLR_BIT(TCCR2, TCCR2_COM20);

	/*Prescaler: divison by 64*/
	SET_BIT(TCCR2,TCCR2_CS20);
	CLR_BIT(TCCR2,TCCR2_CS21);
	SET_BIT(TCCR2,TCCR2_CS22);
}


void Timer0_voidSetTimerValue(uint8 Copy_u8Val)
{
	TCNT0= Copy_u8Val;
}
void TIRFWAIT()
{
	while(GET_BIT(TIFR,TIFR_TOV0)==0);


}
void TIRF_EN()
{
	SET_BIT(TIFR,TIFR_TOV0);


}
void ICPWAIT()
{
	while(GET_BIT(TIFR,TIFR_ICF1)==0);
}
void US_CONFIG()
{
	TIMER1_voidSetValue(0);
	ICU_u8SetTrigger(RISING_EDGE);
	ICPWAIT();
	TIMER1_voidSetValue(0);
	ICU_u8SetTrigger(FALLING_EDGE);
	timer0OV=0;
	ICPWAIT();
}
void Timer2_voidSetTimerValue(uint8 Copy_u8Val){
	TCNT2= Copy_u8Val;

}

void PWM(){
	TIMER2_voidInit();
	Timer2_voidSetTimerValue(0);

	//while(GET_BIT(TIFR,TIFR_OCF2)==0);
	//SET_BIT(TIFR,TIFR_OCF2);


	OCR2=30;

	//DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN1,DIO_u8_PIN_HIGH);
	//DIO_u8SetPinValue(DIO_u8_PORTA,DIO_u8_PIN2,DIO_u8_PIN_HIGH);
	//DC_EN1();

}
void SERVO(uint16 Duration)
{

	TIMER0_voidInit();
	Timer0_voidSetTimerValue(0);
	TIRFWAIT();
	TIRF_EN();
	Timer0_voidSetTimerValue(0);
	/*8*/
	OCR0 = Duration;
	_delay_ms(1000);
}
uint8 TIMER_u8SetCallBack(uint8 Copy_u8IntType,void (*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState= OK;
	if(Copy_pvCallBackFunc != NULL)
	{
		if(Copy_u8IntType == TIMER0_u8_OVF)
		{
			Timer0Ovf_pvCallBackFunc= Copy_pvCallBackFunc;
		}
		else if(Copy_u8IntType == TIMER0_u8_COMP)
		{
			Timer0Comp_pvCallBackFunc= Copy_pvCallBackFunc;
		}
		else if (Copy_u8IntType==ICU_INT)
		{
			ICU_pvCaLLBackFunc=Copy_pvCallBackFunc;
		}
		else
		{
			Local_u8ErrorState = NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NULL_POINTER;
	}
	return Local_u8ErrorState;
}

void TIMER1_voidInit(void)
{
	/*1- Normal Mode*/
	CLR_BIT(TCCR1A,TCCR1A_WGM10);
	CLR_BIT(TCCR1A,TCCR1A_WGM11);
	CLR_BIT(TCCR1B,TCCR1B_WGM12);
	CLR_BIT(TCCR1B,TCCR1B_WGM13);

	/*2- Prescaler: Division by 64*/

	TCCR1A=0;
	SET_BIT(TIMSK,TIMSK_TOIE1);

}

void TIMER1_voidSetValue(uint16 Copy_u16Val)
{
	TCNT1= Copy_u16Val;
}

uint16 TIMER1_u16GetTimerReading(void)
{
	return TCNT1;
}

/*Timer0 Overflow ISR*/
void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if(Timer0Ovf_pvCallBackFunc != NULL)
	{
		Timer0Ovf_pvCallBackFunc();
	}		
	else
	{
		/*Do nothing*/
	}
}
/*Timer1 Overflow ISR*/
void __vector_9 (void) __attribute__((signal));
void __vector_9 (void)
{
	timer0OV++;
}
/*Timer0 Compare Match ISR*/
void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if(Timer0Comp_pvCallBackFunc != NULL)
	{
		Timer0Comp_pvCallBackFunc();
	}
	else
	{
		/*Do nothing*/
	}
}
/* timer1 input capture ISR*/
void __vector_6 (void) __attribute__((signal));
void __vector_6 (void)
{
	if(ICU_pvCaLLBackFunc!= NULL)
	{
		ICU_pvCaLLBackFunc();
	}
	else
	{
		/*Do nothing*/
	}
}
void ICU_voidInit(void)
{
	/*set rising edge as trigger*/
	SET_BIT(TCCR1B,TCCR1B_ICRS1);
	/*ICR interrupt enable*/
	SET_BIT(TIMSK,TIMSK_TICIE1);


}
uint8 ICU_u8SetTrigger(uint8 Copy_u8Trigger)
{
	uint8 Local_u8ErrorState= OK;
	SET_BIT(TCCR1B, TCCR1B_CS10);
	CLR_BIT(TCCR1B, TCCR1B_CS11);
	CLR_BIT(TCCR1B, TCCR1B_CS12);
	switch(Copy_u8Trigger)
	{
	case RISING_EDGE:	SET_BIT(TCCR1B,TCCR1B_ICRS1);break;
	case FALLING_EDGE: CLR_BIT(TCCR1B,TCCR1B_ICRS1);break;
	default: Local_u8ErrorState=NOK;

	}

	SET_BIT(TIFR,TIFR_ICF1);
	SET_BIT(TIFR,TIFR_TOV1);

	return Local_u8ErrorState;
}
uint16 ICU_u16GetCaptureReading(void)
{
	return ICR1;
}
void ICU_voidInterruptDisplay(void)
{
	CLR_BIT(TIMSK,TIMSK_TICIE1);
}

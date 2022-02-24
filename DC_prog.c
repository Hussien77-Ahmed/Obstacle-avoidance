/*
 * DC_prog.c
 *
 *  Created on: Feb 22, 2022
 *      Author: shady
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ERR_TYPE.h"
#include "util/delay.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "CLCD_interface.h"
#include "DC_interface.h"

void DC(uint8 Copy_Direction){

	switch(Copy_Direction)
	{
	case FORWARD:
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN3,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN4,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN5,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN6,DIO_u8_PIN_HIGH);


		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3,DIO_u8_PIN_HIGH);




		break;
	case BACKWARD:
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN3,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN4,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN5,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN6,DIO_u8_PIN_LOW);


		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3,DIO_u8_PIN_LOW);
		break;
	case LEFT:
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN3,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN4,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN5,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN6,DIO_u8_PIN_LOW);


		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3,DIO_u8_PIN_LOW);
		break;

	case RIGHT:
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN3,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN4,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN5,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN6,DIO_u8_PIN_HIGH );

		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1,DIO_u8_PIN_HIGH);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3,DIO_u8_PIN_HIGH);
		break;
	case STOP:
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN3,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN4,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN5,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTC, DIO_u8_PIN6,DIO_u8_PIN_LOW );

		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN0,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN1,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN2,DIO_u8_PIN_LOW);
		DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN3,DIO_u8_PIN_LOW);
		break;
	default:

		break;
	}


}

void DC_EN1()
{

	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN4, DIO_u8_PIN_HIGH);
	DIO_u8SetPinValue(DIO_u8_PORTD, DIO_u8_PIN5, DIO_u8_PIN_HIGH);

}


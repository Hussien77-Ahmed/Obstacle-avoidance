/*
 * main.c
 *
 *  Created on: Feb 22, 2022
 *      Author: hussi
 */


#include "STD_TYPES.h"
#include "ERR_TYPE.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "GIE_interface.h"
#include "TIMER_interface.h"
#include "DC_interface.h"
#include "BIT_MATH.h"
#include "util/delay.h"

f64 LEFTDIS=0,RIGHTDIS=0,FORWARDDIS=0;

void main(void){




	PORT_voidInit() ;
	GIE_voidEnableGlobal();
	TIMER1_voidInit();
	DC_EN1();

	while(1)
	{


		SERVO(FORWARDDURATION);
		FORWARDDIS=US_DIS();
		if(FORWARDDIS>50)
		{
			DC(FORWARD);
		}
		else
		{
			while(1)
			{
				DC(STOP);
				SERVO(LEFTDURATION);
				LEFTDIS=US_DIS();

				SERVO(RIGHTDURATION);
				RIGHTDIS=US_DIS();
				if(RIGHTDIS>20 || LEFTDIS>20)
				{
					SERVO(FORWARDDURATION);
					DC(BACKWARD);
					_delay_ms(300);
					DC(STOP);
					if(RIGHTDIS>LEFTDIS)
					{
						DC(LEFT);
					}
					else
					{
						DC(RIGHT);
					}
					_delay_ms(500);
					DC(STOP);
					break;
				}
				else
				{
					DC(FORWARD);
					SERVO(FORWARDDURATION);
					DC(BACKWARD);
					_delay_ms(200);
	                DC(STOP);
				}


			}
		}



	}






}




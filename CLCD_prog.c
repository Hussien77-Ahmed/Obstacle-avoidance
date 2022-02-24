/************************************************/
/************ Author: hussien mohamed ***********/
/************ Date : 15/10/2021       ***********/
/************ Layer: Hal              ***********/
/************ Version : 1.00          ***********/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"

static void SetHalfDataPins(uint8 copy_u8Data)
{
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN4,GET_BIT(copy_u8Data,0));
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN5,GET_BIT(copy_u8Data,1));
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN6,GET_BIT(copy_u8Data,2));
	DIO_u8SetPinValue(CLCD_u8_DATA_PORT,CLCD_u8_PIN7,GET_BIT(copy_u8Data,3));

}
static void SendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_E_PIN,DIO_u8_PIN_HIGH);
		_delay_ms(2); //abta2 haga felLCD
		DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_E_PIN,DIO_u8_PIN_LOW);
}
void CLCD_voidSendCommand(uint8 Copy_u8Command)
{
	/*set RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RS_PIN,DIO_u8_PIN_LOW);
	/*set RW pin to low for write*/

	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RW_PIN,DIO_u8_PIN_LOW);
#if CLCD_u8_MODE==EIGHT_BIT
	/* send command*/
	DIO_u8SetPortValue(CLCD_u8_DATA_PORT,Copy_u8Command);

	/*send enable pulse*/
	SendEnablePulse();

#elif CLCD_u8_MODE==FOUR_BIT
	SetHalfDataPins(Copy_u8Command>>4);
	SendEnablePulse();
    SetHalfDataPins(Copy_u8Command);
    SendEnablePulse();


#endif
}
void CLCD_voidSendData(uint8 copy_u8Data)
{
	/*set RS pin to high for Data*/
	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RS_PIN,DIO_u8_PIN_HIGH);
	/*set RW pin to high for Read*/

	DIO_u8SetPinValue(CLCD_u8_CTRL_PORT,CLCD_u8_RW_PIN,DIO_u8_PIN_LOW);
#if CLCD_u8_MODE==EIGHT_BIT
	/* send command*/
	DIO_u8SetPortValue(CLCD_u8_DATA_PORT,copy_u8Data);

	/*send enable pulse*/
	SendEnablePulse();

#elif CLCD_u8_MODE==FOUR_BIT
	SetHalfDataPins(copy_u8Data>>4);
	SendEnablePulse();
    SetHalfDataPins(copy_u8Data);
    SendEnablePulse();


#endif
 }
void CLCD_voidInit(void)
{

	_delay_ms(30);
#if CLCD_u8_MODE==EIGHT_BIT
	/*Function set command : 2lines ,font size 5x7 */
	CLCD_voidSendCommand(0b00111000);


#elif CLCD_u8_MODE==FOUR_BIT
	SetHalfDataPins(0b0010);
	SendEnablePulse();
	SetHalfDataPins(0b0010);
	SendEnablePulse();
	SetHalfDataPins(0b1000);
	SendEnablePulse();
#endif

	/* function set command : display on, cursor off, blink off */
	CLCD_voidSendCommand(0b00001100);
	/*Clear LCD*/
	CLCD_voidSendCommand(1);

}
void CLCD_voidSendString(uint8 copy_str[])
{
	uint8 Local_u8_counter=0;

	while(copy_str[Local_u8_counter]!='\0')
	{

		CLCD_voidSendData(copy_str[Local_u8_counter]);
		Local_u8_counter++;
	}

}
void CLCD_voidSendNumber(uint32 copy_number)
{
	uint8 copy_numbertocharArr[10];
	uint32 Local_u8_counter=0;
	if (copy_number==0)
	{
		CLCD_voidSendData(copy_number+'0');
	}
	else{
 while (copy_number!=0)
 {
	 copy_numbertocharArr[Local_u8_counter]=copy_number%10;
	 Local_u8_counter++;
	 copy_number/=10;
 }
 for(uint8 Local_u8_counter2=(Local_u8_counter);Local_u8_counter2>0;(Local_u8_counter2)--)
 {
	 CLCD_voidSendData(copy_numbertocharArr[Local_u8_counter2-1]+'0');
 }
	}

}
void CLCD_voidGoToXY(uint8 copy_u8XPos,uint8 copy_u8YPos)
{
	uint8 Local_u8Add;
	/*if ( copy_u8YPos==0)
	{
		Local_u8Add=copy_u8XPos;
	}
	else if(copy_u8YPos==1)
	{
		Local_u8Add=(0x40+copy_u8XPos);
	}*/
	Local_u8Add=(copy_u8YPos*0x40 +copy_u8XPos);
	/*set bit number 7 for set ddram address command*/
	SET_BIT(Local_u8Add,7);

	/*set ddram address command*/
	CLCD_voidSendCommand(Local_u8Add);

}

void CLCD_voidSendSpecialCharacter(uint8 copy_u8pattern[],uint8 copy_u8patternNum,uint8 copy_u8XPos,uint8 copy_u8YPos)
{
	uint8 Local_u8StartAdd;
	Local_u8StartAdd=copy_u8patternNum*8;
	SET_BIT(Local_u8StartAdd,6);
	CLR_BIT(Local_u8StartAdd,7);
	CLCD_voidSendCommand(Local_u8StartAdd);
	for(uint8 Local_u8_counter=0;Local_u8_counter<8;(Local_u8_counter)++)
	 {
		 CLCD_voidSendData(copy_u8pattern[Local_u8_counter]);
	 }
	CLCD_voidGoToXY(copy_u8XPos,copy_u8YPos);

	CLCD_voidSendData(copy_u8patternNum);

}








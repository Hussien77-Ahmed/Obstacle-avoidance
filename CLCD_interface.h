/************************************************/
/************ Auther: hussien mohamed ***********/
/************ Date : 15/10/2021       ***********/
/************ Layer: Hal              ***********/
/************ Version : 1.00          ***********/
#ifndef CLCD_INTERFACE_H_
#define CLCD_INTERFACE_H_




void CLCD_voidSendCommand(uint8 Copy_u8Command);
void CLCD_voidSendData(uint8 copy_u8Data);
void CLCD_voidInit(void);
void CLCD_voidSendString(uint8 copy_str[]);
void CLCD_voidSendNumber(uint32 copy_number);
void CLCD_voidGoToXY(uint8 copy_u8XPos,uint8 copy_u8YPos);
void CLCD_voidSendSpecialCharacter(uint8 copy_u8pattern[],uint8 copy_u8patternNum,uint8 copy_u8XPos,uint8 copy_u8YPos);



#endif

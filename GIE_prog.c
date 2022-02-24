/*********************************************************************/
/*********************************************************************/
/**********************		Author: Hussien ahmed		**************/
/**********************		Date: 29/10/2021			**************/
/**********************		layer: MCAL					**************/
/**********************		Version: 1.00				**************/
/*********************************************************************/
/*********************************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "GIE_interface.h"
#include "GIE_reg.h"

void GIE_voidEnableGlobal(void)
{
	
	/*use C or assembly code to enable the global interrupts*/
	//SET_BIT(SREG,SREG_I);
	
	__asm volatile("SEI");		
}

void GIE_voidDisableGlobal(void)
{
	//CLR_BIT(SREG,SREG_I);
	
	__asm volatile("CLI");
}


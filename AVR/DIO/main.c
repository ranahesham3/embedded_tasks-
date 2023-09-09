/*
 * main.c
 *
 *  Created on: Jul 27, 2023
 *      Author: DELL
 */

#include "STDTYPES.H"
#include "ERRORSTATE.H"
#include "DIO_INIT.H"
#include <util/delay.h>

int main()
{
	DIO_enuInit();
	DIO_enuSetPortDirection(DIO_u8PORTA	,0xff);
	DIO_enuSetPortValue(DIO_u8PORTA	,0);
	while(1)
	{
		for(u8 i=0;i<=7;i++)
		{
			DIO_enuSetPinValue(DIO_u8PORTA,i,DIO_u8HIGH);
			_delay_ms(100);
		}
		for(u8 i=7;i>=0;i--)
		{
			DIO_enuSetPinValue(DIO_u8PORTA,i,DIO_u8LOW);
			_delay_ms(100);
		}
	}
	return 0;
}

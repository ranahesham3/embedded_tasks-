/*
 * main.c
 *
 *  Created on: Aug 30, 2023
 *      Author: DELL
 */
#include "stdTypes.h"
#include "errorState.h"

#include "PORT_init.h"
#include "DIO_init.h"
#include "EXTI_init.h"
#include "LCD_init.h"
#include "GIE.h"

#include "util/delay.h"

u8 volatile a=0,b=0,c=0;

void func1(void);
void func2(void);
void func3(void);

int main()
{
	PORT_enuInit();
	DIO_enuInit();
	LCD_enuInit();
	EXTI_enuInit();

	EXTI_enuCallBack(INT0,&func1);
	EXTI_enuCallBack(INT1,&func2);
	EXTI_enuCallBack(INT2,&func3);

	EnableGlobalEnterrupt();

	u8 Local_Iterator;
	while(1)
	{
		for(Local_Iterator=0;Local_Iterator<=100;Local_Iterator++)
		{
			LCD_enuGoToXY(0,0);
			LCD_enuWriteNum(Local_Iterator);
			_delay_ms(300);
			if(Local_Iterator==100)
			{
				Local_Iterator=0;
				LCD_enuClearLCD();
			}
		}
	}
}

void func1(void)
{
	DIO_enuTogPinValue(DIO_u8PORTB,DIO_u8PIN1);
	LCD_enuGoToXY(1,0);
	LCD_enuSendString("INT0->");
	a++;
	LCD_enuGoToXY(1,6);
	LCD_enuWriteNum(a);
	_delay_ms(500);
	LCD_enuGoToXY(1,0);
	LCD_enuSendString("       ");
}

void func2(void)
{
	DIO_enuTogPinValue(DIO_u8PORTB,DIO_u8PIN3);
	LCD_enuGoToXY(1,0);
	LCD_enuSendString("INT1->");
	b++;
	LCD_enuGoToXY(1,6);
	LCD_enuWriteNum(b);
	_delay_ms(500);
	LCD_enuGoToXY(1,0);
	LCD_enuSendString("       ");
}


void func3(void)
{
	DIO_enuTogPinValue(DIO_u8PORTB,DIO_u8PIN4);
	LCD_enuGoToXY(1,0);
	LCD_enuSendString("INT2->");
	c++;
	LCD_enuGoToXY(1,6);
	LCD_enuWriteNum(c);
	_delay_ms(500);
	LCD_enuGoToXY(1,0);
	LCD_enuSendString("       ");
}


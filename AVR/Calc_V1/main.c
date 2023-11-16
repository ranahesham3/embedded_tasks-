/*
 * main.c
 *
 *  Created on: Aug 25, 2023
 *      Author: DELL
 */
//#define  F_CPU 16000000

#include "stdTypes.h"
#include "errorState.h"

#include "DIO_init.h"
#include "LCD_init.h"
#include "KPD_init.h"

#include "util/delay.h"
int main()
{
	DIO_enuInit();
	LCD_enuInit();
	Keypad_enuInit();

	u8  key =NOT_PRESSED,op=0,op_pre=0,flag=0,op_flag=0;
	f64 number=0,num=0,num2=0;

	while(1)
	{
		key =NOT_PRESSED;
		while(key==NOT_PRESSED)
		{
			Keypad_enuGetPressedKey(&key);
		}
		if(flag==1)
			{
				LCD_enuClearLCD();
				num=0;	number=0;	op=0;	op_pre=0;
				flag=0;	op_flag=0;
			}
		switch(key)
			{
				case '0':
					number=number*10;	LCD_enuDisplayChar('0'); break;
				case '1':
					number=number*10+1;	LCD_enuDisplayChar('1'); break;
				case '2':
					number=number*10+2;	LCD_enuDisplayChar('2'); break;
				case '3':
					number=number*10+3;	LCD_enuDisplayChar('3'); break;
				case '4':
					number=number*10+4;	LCD_enuDisplayChar('4'); break;
				case '5':
					number=number*10+5;	LCD_enuDisplayChar('5'); break;
				case '6':
					number=number*10+6;	LCD_enuDisplayChar('6'); break;
				case '7':
					number=number*10+7;	LCD_enuDisplayChar('7'); break;
				case '8':
					number=number*10+8;	LCD_enuDisplayChar('8'); break;
				case '9':
					number=number*10+9;	LCD_enuDisplayChar('9'); break;
				case '+':
					op='+'; LCD_enuDisplayChar('+'); break;
				case '-':
					op='-'; LCD_enuDisplayChar('-'); break;
				case 'x':
					op='x'; LCD_enuDisplayChar('x'); break;
				case '/':
					op='/'; LCD_enuDisplayChar('/'); break;
				case 'c':
					LCD_enuClearLCD();	num=0;	number=0;	op=0;	op_pre=0;	op_flag=0;	break;
				case '=':
					switch(op_pre)
					{
					case '+':
						num+=number;	break;
					case '-':
						num-=number;	break;
					case 'x':
						num*=number;	break;
					case '/':
						if(number==0)
						{
							LCD_enuGoToXY(1,0);
							LCD_enuSendString("ERROR");
							flag=1;

						}
						else
							num/=number;
						break;
					default:
						num+=number;		break;
					}
					if(flag==0)
					{
					if(num-(long)num==0)
					{
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum(num);
					}
					else
					{
						num*=1000;
						num2=(s64)num%1000;
						num/=1000;
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum(num);
						LCD_enuDisplayChar('.');
						LCD_enuWriteNum(num2);
					}
					flag=1;
					break;
					}
			}
		if(key=='+'||key=='-'||key=='/'||key=='x')
		{
		switch(op_pre)
			{
			case '+':
				num+=number;
				number=0;
				op_pre=op;
				break;
			case '-':
				num-=number;
				number=0;
				op_pre=op;
				break;
			case 'x':
				num*=number;
				number=0;
				op_pre=op;
				break;
			case '/':
				if(number==0)
					{
						LCD_enuGoToXY(1,0);
						LCD_enuSendString("ERROR");
						flag=1;

					}
				else
					num/=number;
					number=0;
					op_pre=op;
				break;
			default:
				if(op!=0)
				{
				num=number;
				number=0;
				op_pre=op;
				}
			}
		}


	}

	return 0;
}




/*
 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 V2
int main()
{
	//PORT_enuInit();
	DIO_enuInit();
	LCD_enuInit();
	Keypad_enuInit();

	u8  key =NOT_PRESSED,op=0,op_pre=0,flag=0,op_flag=0;
	f64 number=0,num=0,num2=0;
	//u8 flag =65;
	while(1)
	{
		key =NOT_PRESSED;
		while(key==NOT_PRESSED)
		{
			Keypad_enuGetPressedKey(&key);
		}
		if(key!=NOT_PRESSED)

			if(flag==1)
			{
				LCD_enuClearLCD();
				num=0;	number=0;	op=0;
				flag=0;	op_flag=0;
			}
			switch(key)
			{
				case '0':
					number=number*10;	LCD_enuDisplayChar('0'); break;
				case '1':
					number=number*10+1;	LCD_enuDisplayChar('1'); break;
				case '2':
					number=number*10+2;	LCD_enuDisplayChar('2'); break;
				case '3':
					number=number*10+3;	LCD_enuDisplayChar('3'); break;
				case '4':
					number=number*10+4;	LCD_enuDisplayChar('4'); break;
				case '5':
					number=number*10+5;	LCD_enuDisplayChar('5'); break;
				case '6':
					number=number*10+6;	LCD_enuDisplayChar('6'); break;
				case '7':
					number=number*10+7;	LCD_enuDisplayChar('7'); break;
				case '8':
					number=number*10+8;	LCD_enuDisplayChar('8'); break;
				case '9':
					number=number*10+9;	LCD_enuDisplayChar('9'); break;
				case '+':
					op='+'; op_flag++;	LCD_enuDisplayChar('+'); break;
				case '-':
					op='-'; op_flag++;	LCD_enuDisplayChar('-'); break;
				case 'x':
					op='x'; op_flag++;	LCD_enuDisplayChar('x'); break;
				case '/':
					op='/'; op_flag++;	LCD_enuDisplayChar('/'); break;
				case 'c':
					LCD_enuClearLCD();	num=0;	number=0;	op=0;	op_flag=0;	break;
				case '=':
					switch(op)
					{
					case '+':
						num+=number;	break;
					case '-':
						num-=number;	break;
					case 'x':
						num*=number;	break;
					case '/':
						if(number==0)
						{
							LCD_enuGoToXY(1,0);
							LCD_enuSendString("ERROR");
							flag=1;

						}
						else
							num/=number;	break;
					default:
						num=number;		break;
					}
					if(num-(long)num==0)
					{
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum(num);
					}
					else
					{
						num*=1000;
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum((s64)num%1000);
						num/=1000;
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum(num);
					}
					flag=1;
					break;
			}
			switch(op)
			{
			case '+':
				if(op_flag>1)
				{
				num+=number;
				//number=0;
				}
				else
				{
				num=number;
				number=0;
				//op_pre=op
				}
				break;
			case '-':
				if(op_flag>1)
				{
				num-=number;
				number=0;
				}
				else
				{
				num=number;
				number=0;
				//op_pre=op
				}
				break;
			case 'x':
				if(op_flag>1)
				{
				num*=number;
				number=0;
				}
				else
				{
				num=number;
				number=0;
				//op_pre=op
				}
				break;
			case '/':
				if(op_flag>1)
				{
					if(number==0)
					{
						LCD_enuGoToXY(1,0);
						LCD_enuSendString("ERROR");
						flag=1;

					}
					else
						num/=number;
					number=0;
				}
				else
				{
				num=number;
				number=0;
				}
				break;

			}


	}

	return 0;
}










  	  	  	  	  	  	  	  	  	  	  	  	  	  	  	  V1
int main()
{
	//PORT_enuInit();
	DIO_enuInit();
	LCD_enuInit();
	Keypad_enuInit();

	u8  key =NOT_PRESSED,op=0,flag=0;
	f64 number=0,num=0;
	//u8 flag =65;
	while(1)
	{
		key =NOT_PRESSED;
		while(key==NOT_PRESSED)
		{
			Keypad_enuGetPressedKey(&key);
		}
		if(key!=NOT_PRESSED)
		{
			if(flag==1)
			{
				LCD_enuClearLCD();
				num=0;	number=0;	op=0;
			}
			switch(key)
			{
				case '0':
					number=number*10;	break;
				case '1':
					number=number*10+1;	break;
				case '2':
					number=number*10+2;	break;
				case '3':
					number=number*10+3;	break;
				case '4':
					number=number*10+4;	break;
				case '5':
					number=number*10+5;	break;
				case '6':
					number=number*10+6;	break;
				case '7':
					number=number*10+7;	break;
				case '8':
					number=number*10+8;	break;
				case '9':
					number=number*10+9;	break;
				case '+':
					op='+';		break;
				case '-':
					op='-';		break;
				case 'x':
					op='x';		break;
				case '/':
					op='/';		break;
				case 'c':
					LCD_enuClearLCD();	num=0;	number=0;	op=0;	break;
				case '=':
					switch(op)
					{
					case '+':
						num+=number;	break;
					case '-':
						num-=number;	break;
					case 'x':
						num*=number;	break;
					case '/':
						if(number==0)
						{
							LCD_enuGoToXY(1,0);
							LCD_enuSendString("ERROR");
							flag=1;

						}
						else
							num/=number;	break;
					case 0 :
						num=number;		break;
					}
					if(num-(long)num==0)
					{
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum(num);
						flag=1;
					}
					else
					{
						num*=1000;
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum((s64)num%1000);
						num/=1000;
						LCD_enuGoToXY(1,0);
						LCD_enuWriteNum(num);
					}
					break;
			}
			switch(op)
			{
			case '+':
				num+=number;	break;
			case '-':
				num-=number;	break;
			case 'x':
				num*=number;	break;
			case '/':
				num/=number;	break;
			}
		}

	}

	return 0;
}
 */

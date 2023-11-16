/*
 * ADC.prog.c
 *
 *  Created on: Sep 18, 2023
 *      Author: DELL
 */



#include "stdTypes.h"
#include "errorState.h"
#include "bit_math.h"
#include "Interrupt.h"

#include "DIO_init.h"

#include "ADC_config.h"
#include "ADC_priv.h"



static void(*ADC_PNotificationFunc)(void)=NULL;
static u16* ADC_pu8Reading=NULL;
static u8 ADC_u8BusyState=IDLE;



ES_t ADC_enuInit (void)
{
	ES_t Local_enuErrorState =ES_NOK;
	//voltage reference selection
#if (ADC_REFRENCE_SELECTION==ADC_AREF)
	CLEAR_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);
#elif(ADC_REFRENCE_SELECTION==ADC_AVCC)
	SET_BIT(ADMUX,ADMUX_REFS0);
	CLEAR_BIT(ADMUX,ADMUX_REFS1);
#elif(ADC_REFRENCE_SELECTION==ADC_INTERNL_REF)
	SET_BIT(ADMUX,ADMUX_REFS0);
	SET_BIT(ADMUX,ADMUX_REFS1);
#else
#error"Wrong selection"
#endif

	//left adjust
#if(ADC_ADJUSTMENT==ADC_LEFT_ADJUST)
	SET_BIT(ADMUX,ADMUX_ADLAR);
#elif(ADC_ADJUSTMENT==ADC_RIGHT_ADJUST)
	CLEAR_BIT(ADMUX,ADMUX_ADLAR);
#else
#error"Wrong selection"
#endif
	//prescaler Select Bits
#if(ADC_PRESCALER_SELECTION==Division_Factor_2)
	CLEAR_BITS_REG(ADCSRA,Division_Factor_128);
	SET_BITS_REG(ADCSRA,Division_Factor_2);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_4)
	CLEAR_BITS_REG(ADCSRA,Division_Factor_128);
	SET_BITS_REG(ADCSRA,Division_Factor_4);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_8)
	CLEAR_BITS_REG(ADCSRA,Division_Factor_128);
	SET_BITS_REG(ADCSRA,Division_Factor_8);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_16)
	CLEAR_BITS_REG(ADCSRA,Division_Factor_128);
	SET_BITS_REG(ADCSRA,Division_Factor_16);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_32)
	CLEAR_BITS_REG(ADCSRA,Division_Factor_128);
	SET_BITS_REG(ADCSRA,Division_Factor_32);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_64)
	CLEAR_BITS_REG(ADCSRA,Division_Factor_128);
	SET_BITS_REG(ADCSRA,Division_Factor_64);
#elif(ADC_PRESCALER_SELECTION==Division_Factor_128)
	CLEAR_BITS_REG(ADCSRA,Division_Factor_128);
	SET_BITS_REG(ADCSRA,Division_Factor_128);
#else
#error"Wrong selection"
#endif

	//ADC enable
#if(ADC_INITIAL_STATE==ADC_ENABLE)
	SET_BIT(ADCSRA,ADCSRA_ADEN);
#elif(ADC_INITIAL_STATE==ADC_DISABLE)
	CLEAR_BIT(ADCSRA,ADCSRA_ADEN);
#else
#error"Wrong selection"
#endif

#if(ADC_AUTO_TRIGGER_SOURCE==ADC_FREE_RUNNING_MODE)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_ANALOG_COMPARATOR)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_EXTERNAL_INTERRUPT_REQUIST0)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_EXTERNAL_INTERRUPT_REQUIST0);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER0_COPMPARE_MATCH)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_ADC_TIMER0_COPMPARE_MATCH);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER0_OVERFLOW)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_TIMER0_OVERFLOW);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER1_COPMPARE_MATCH_B)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_ADC_TIMER1_COPMPARE_MATCH_B);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER1_OVERFLOW)
	CLEAR_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
	SET_BITS_REG(SFIOR,ADC_TIMER1_OVERFLOW);
#elif(ADC_AUTO_TRIGGER_SOURCE==ADC_TIMER1_CAPTURE_EVENT)
	SET_BITS_REG(SFIOR,ADC_TIMER1_CAPTURE_EVENT);
#else
#error"Wrong selection"
#endif

	Local_enuErrorState =ES_OK;

	return Local_enuErrorState;
}

ES_t ADC_enuStartConversionSync (u8 Copy_u8Channel , u16* copy_pu8Value)
{
	ES_t Local_enuErrorState =ES_NOK;
	if(ADC_u8BusyState==IDLE)
	{
	u32 Local_Counter=0;
	if(copy_pu8Value !=NULL)
	{
		if(Copy_u8Channel<=GND)
		{
			ADC_u8BusyState=BUSY;
			//select channel
			CLEAR_BITS_REG(ADMUX,0X1F);
			SET_BITS_REG(ADMUX,Copy_u8Channel);

			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			//polling or busy waiting untill the conversion complete
			while((CHECK_BIT(ADCSRA,ADCSRA_ADIF)==0)&&(Local_Counter<ADC_U32TIME_OUT))
			{Local_Counter++;}

			if(Local_Counter!=ADC_U32TIME_OUT)
			{
				//clear the conversion flag
				SET_BIT(ADCSRA,ADCSRA_ADIF);

				//get value
				if(ADC_RESOLUTION==ADC_10BIT_RESOLUTION)
				{
					*copy_pu8Value=ADCH;
				}
				else
				{
					*copy_pu8Value=(u8*)ADCH;
					//*copy_pu8Value=ADCH;
				}
			}
			ADC_u8BusyState=IDLE;

			Local_enuErrorState=ES_OK;
		}
		else
		{
			Local_enuErrorState=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}
	}
	else
	{
		Local_enuErrorState=ES_BYSY_FUNC;
	}
	return Local_enuErrorState;
}

ES_t ADC_enuStartConversionAsync (u8 Copy_u8Channel , u16* copy_pu8Value,void(*PNotificationFunc)(void))
{
	ES_t Local_enuErrorState =ES_NOK;
	if(ADC_u8BusyState==IDLE)
	{
	if((copy_pu8Value !=NULL)&& (PNotificationFunc!=NULL))
	{
		if(Copy_u8Channel<=GND)
		{
			ADC_u8BusyState=BUSY;
			//select channel
			ADC_pu8Reading=copy_pu8Value;
			ADC_PNotificationFunc=PNotificationFunc;


			CLEAR_BITS_REG(ADMUX,0X1F);
			SET_BITS_REG(ADMUX,Copy_u8Channel);

			//start conversion
			SET_BIT(ADCSRA,ADCSRA_ADSC);

			//enable ADC interrupt enable
			SET_BIT(ADCSRA,ADCSRA_ADIE);

		}
		else
		{
			Local_enuErrorState=ES_OUT_OF_RANGE;
		}
	}
	else
	{
		Local_enuErrorState =ES_NULL_POINTER;
	}
	}
	else
	{
		Local_enuErrorState=ES_BYSY_FUNC;
	}
	return Local_enuErrorState;

}

ISR(VECT_ADC)
{
	if((ADC_PNotificationFunc!=NULL)&&(ADC_pu8Reading!=NULL))
	{
		if(ADC_ADJUSTMENT==ADC_LEFT_ADJUST)
		{
			*ADC_pu8Reading=ADCH;
		}
		else
		{
			*ADC_pu8Reading=(u8*)ADCH;
			//*ADC_pu8Reading=ADCH;
		}

		ADC_u8BusyState=IDLE;

		ADC_PNotificationFunc();

		//disable ADC interrupt enable
		CLEAR_BIT(ADCSRA,ADCSRA_ADIE);

	}
}

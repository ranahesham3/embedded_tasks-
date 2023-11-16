/*
 * ADC_init.h
 *
 *  Created on: Sep 18, 2023
 *      Author: DELL
 */

#ifndef ADC_INIT_H_
#define ADC_INIT_H_

#include "stdTypes.h"
#include "errorState.h"
#include "bit_math.h"
#include "Interrupt.h"

#include "DIO_init.h"

#include "ADC_config.h"
#include "ADC_priv.h"

 //Analog channel&gain selection bits
#define SingleEnded_ADC0					0
#define SingleEnded_ADC1					1
#define SingleEnded_ADC2					2
#define SingleEnded_ADC3					3
#define SingleEnded_ADC4					4
#define SingleEnded_ADC5					5
#define SingleEnded_ADC6					6
#define SingleEnded_ADC7					7

#define Differential_ADC0_ADC0_10x			8
#define Differential_ADC1_ADC0_10x			9
#define Differential_ADC0_ADC0_200x			10
#define Differential_ADC1_ADC0_200x			11
#define Differential_ADC2_ADC2_10x			12
#define Differential_ADC3_ADC2_10x			13
#define Differential_ADC2_ADC2_200x			14
#define Differential_ADC3_ADC2_200x			15
#define Differential_ADC0_ADC1_1x			16
#define Differential_ADC1_ADC1_1x			17
#define Differential_ADC2_ADC1_1x			18
#define Differential_ADC3_ADC1_1x			19
#define Differential_ADC4_ADC1_1x			20
#define Differential_ADC5_ADC1_1x			21
#define Differential_ADC6_ADC1_1x			22
#define Differential_ADC7_ADC1_1x			23
#define Differential_ADC0_ADC2_1x			24
#define Differential_ADC1_ADC2_1x			25
#define Differential_ADC2_ADC2_1x			26
#define Differential_ADC3_ADC2_1x			27
#define Differential_ADC4_ADC2_1x			28
#define Differential_ADC5_ADC2_1x			29

#define VOLTAGE_1_22						30
#define GND									31

ES_t ADC_enuInit (void);

ES_t ADC_enuStartConversionSync (u8 Copy_u8Channel , u16* copy_pu8Value);

ES_t ADC_enuStartConversionAsync (u8 Copy_u8Channel , u16* copy_pu8Value,void(*PNotificationFunc)(void));


#endif /* ADC_INIT_H_ */

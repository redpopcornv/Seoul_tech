#define F_CPU	16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "CLCD.h"
#include "UART.h"

#define ADC_PORT PORTF
#define ADC_DDR	DDRF
#define ADC_PIN	PINF0
	
void compare(void);
uint16_t AD_Conv(void);

UART myuart(0);
CLCD myclcd;
int main(void)
{
	uint16_t ADC_Value;
	
	DDRD=0xff;
	PORTD=0xff;
	
	ADC_DDR &= ~(1<<ADC_PIN);
	ADC_PORT &= ~(ADC_PIN);
	
	ADCSRA	|= (1<<ADEN) | (1<<ADPS2) | (1<<ADPS0);
	ADMUX	|= (1<<REFS0);
	
	
	char buffer[20];
    while (1) 
    {
		if (myuart.IsRxD())
		{
			compare();
		}
		
		ADC_Value=AD_Conv();
		sprintf(buffer,"%d\r\n",ADC_Value);
		myuart.TxString(buffer);
		myclcd.LCD_goto_XY(0,0);
		myclcd.LCD_write_string(buffer);
		
    }
}

void compare(void)
{
	char RxD_data[20];
	const char *num[]={"zero","one","two","three","four","five","six","seven","eight"};
	const char *num1[]={"0","1","2","3","4","5","6","7","8"};
	
	myuart.RxString(RxD_data);
	for(int i=0;i<=8;i++){
		if( !strcmp(RxD_data, num[i]) || !strcmp(RxD_data, num1[i]))
		{
			PORTD=0xff-pow(2,i-1);
		}else if(!strcmp(RxD_data, num[0]) || !strcmp(RxD_data, num1[0]))
		{
			PORTD=0xff;
		}
	}
}

uint16_t AD_Conv(void)
{
	uint16_t ADC_Result = 0;
	
	for(int i=0;i<4;i++)
	{
		ADCSRA |= (1<<ADSC);
		
		while((ADCSRA & (1<<ADSC))==0);
		ADC_Result+=ADC;
	}
	return ADC_Result/4;
}


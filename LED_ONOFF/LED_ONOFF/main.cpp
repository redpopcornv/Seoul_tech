
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	
	DDRD=0xff;
	PORTD=0xff;
    /* Replace with your application code */
    while (1) 
    {
		PORTD=0x00;
		_delay_ms(300);
		PORTD=0xff;
		_delay_ms(300);
<<<<<<< HEAD
=======
		for(int i=0;i<7;i++)
		{
			PORTD= ~(1<<i);
			_delay_ms(300);
		}
		for(int i=7;i>=0;i--)
		{
			PORTD = ~(1<<i);
			_delay_ms(300);
		}
>>>>>>> LED_shift
    }
}


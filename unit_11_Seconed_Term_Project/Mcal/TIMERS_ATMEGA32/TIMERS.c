/*
 * timer.c
 *
 * Created: 16/02/2024 12:57:30 ص
 *  Author: Ahmed
 */ 
#include "timers.h"

void Set_timers_pins(void)

{
DDRB |= (1<<3);
DDRD |= (1<<7);
}
void open_Entery_gate(void)
{
	// controlled by timer 0 
	
	// 1. select phase correct PWM for timer0
	TCCR0 |= (1<<6);
	TCCR0 &= ~(1<<3);
	
	// 2. select inverted PWM wave generation
		TCCR0 |= (0b11<<4);
    
	// 3. Edit duty cycle to generate a pulse equivalent to 90 deg. motion 
	OCR0 = 25;
	
	// 4. Enable clock for timer0 and adjust scaler = 8 
	TCCR0 |= (0b010<<0);
	
}

void close_Entery_gate(void)
{
    // 1. disable clock to allow changes
	TCCR0 &= ~(0b111<<0);
	// 2. adjust value of duty cycle to rotate servo to 0 deg.
	OCR0 = 200;
	// 3. Enable clock again
	TCCR0 |= (0b010<<0);
	//  4. delay to allow new pulse
    _delay_ms(200);
	// 5. disable clock for the timer to save power
      TCCR0 &= ~(0b111<<0);
}
void open_Exit_gate(void)
{
	// controlled by timer 2
	
	// 1. select phase correct PWM for timer0
	TCCR2 |= (1<<6);
	TCCR2 &= ~(1<<3);
	
	// 2. select inverted PWM wave generation
	TCCR2 |= (0b11<<4);
	
	// 3. Edit duty cycle to generate a pulse equivalent to 90 deg. motion
	OCR2 = 25;
	
	// 4. Enable clock for timer0 and adjust scaler = 8
	TCCR2 |= (0b010<<0);

}
void close_Exit_gate(void)
{
    // 1. disable clock to allow changes
    TCCR2 &= ~(0b111<<0);
    // 2. adjust value of duty cycle to rotate servo to 0 deg.
    OCR2 = 200;
    // 3. Enable clock again
    TCCR2 |= (0b010<<0);
    //  4. delay to allow new pulse
    _delay_ms(200);
    // 5. disable clock for the timer to save power
    TCCR2 &= ~(0b111<<0);

}

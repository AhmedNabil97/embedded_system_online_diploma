/*
 * GccApplication6.c
 *
 * Created: 26/11/2023 08:47:28 م
 * Author : lenovo
 */


#include <stdlib.h>
#include "GPIO.h"
#include "UART.h"
#include "lcd.h"
#include "keypad.h"


//global variables

unsigned char IDs [3][8];
unsigned int IDs_int[3];
unsigned char Entery_gate_ID[6];
unsigned int Entery_gate_ID_test;
unsigned char Exit_gate_ID[6];
unsigned int Exit_gate_ID_test;
unsigned int counter ;
unsigned int counter1 ;
enum En_Gate_ID_Status {ID_NOT_RECEVIED,ID_RECEIVED} Flag_Ent;
enum En_Gate_ID_Status flag_exit;
unsigned char passed;
unsigned char slots;
int init = 1;

//intilization functions

void Mcal_init(void)
{
	GPIOA_CLK_EN() ;    //Enable clock for GPIOA
	GPIOB_CLK_EN() ;   //Enable clock for GPIOB
	USART1_CLK_EN();   //Enable clock for USART1
	USART2_CLK_EN();   //Enable clock for USART2
}

void Hal_init(void)

{
	lcd_init();
	keypad_init();

	}

void set_pins(void)
{
    MCAL_UART_GPIO_Set_PINS(USART1);
    MCAL_UART_GPIO_Set_PINS(USART2);
   GPIO_CONFIG_t led_pin;
   MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin0, 1);
   MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin11, 1);
   led_pin.Pin_Number = GPIO_pin0;
   led_pin.Pin_Mode = GPIO_MODE_General_purpose_output_Open_drain;
   led_pin.Output_Pin_Speed = medium_speed_10Mhz;
   MCAL_GPIO_Init(GPIOA, & led_pin);
   led_pin.Pin_Number = GPIO_pin11;
   MCAL_GPIO_Init(GPIOA, &led_pin);
   GPIO_CONFIG_t Interrupt_pin;
   Interrupt_pin.Pin_Number = GPIO_pin4;
   Interrupt_pin.Pin_Mode = GPIO_MODE_General_purpose_output_push_pull;
   Interrupt_pin.Output_Pin_Speed = medium_speed_10Mhz;
   MCAL_GPIO_Init(GPIOA, & Interrupt_pin);
   Interrupt_pin.Pin_Number = GPIO_pin8;
   MCAL_GPIO_Init(GPIOA, & Interrupt_pin);
   GPIO_CONFIG_t response;
   response.Pin_Number = GPIO_pin7;
   response.Pin_Mode = GPIO_MODE_Floating_input;
   MCAL_GPIO_Init(GPIOA, &response);


	}

void idle_screen(void)
{
 	 lcd_send_command(lcd_clear, lcd2);
 	 lcd_display_sentence("no. of av. slots :  ", lcd2);
 	 lcd_display_char(slots+48, lcd2);
 	 lcd_send_command(lcd_begin_at_third_row, lcd2);
	 if(slots)
	 {
 	 lcd_display_sentence("Enter ur car id ", lcd2);
	 }
	 else
	 {
	   	 lcd_display_sentence("parking is full ", lcd2);
	   	 lcd_send_command(lcd_begin_at_third_row, lcd2);
	 }

	}
void waiting(void)
{
	idle_screen();
    while(1);

	}
void processing(void)
{

	int i;
	passed = 0;
	while(   (! Flag_Ent) & ( ! (USART1->USART_SR & (1<<5))));
	if(Flag_Ent == ID_RECEIVED)
	{
	  	  counter = 0;
		Entery_gate_ID_test = atoi(Entery_gate_ID);
		for(i=0; i<3; i++)
		{
			if(Entery_gate_ID_test == IDs_int[i])
			{
				passed = 1;

				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin11, 0);
				_delay_ms(250);
				_delay_ms(250);
				lcd_display_sentence("ID ---> accepted", lcd2);
				_delay_ms(250);
				_delay_ms(250);
			   	 lcd_send_command(lcd_clear, lcd2);
			   	 lcd_send_command(lcd_begin_at_seconed_row, lcd2);
				lcd_display_sentence("opening the gate", lcd2);
				_delay_ms(250);
				_delay_ms(250);
				Flag_Ent = ID_NOT_RECEVIED;
				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin11, 1);
				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin4, 1);
				slots --;
				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin4, 0);
				while(! MCAL_GPIO_Read_Pin(GPIOA, GPIO_pin7));
				idle_screen();
				break;
			}
		}
		if(! passed)
		{
			MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin0, 0);
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
			lcd_display_sentence("ID ---> rejected", lcd2);
			_delay_ms(250);
		   	 lcd_send_command(lcd_clear, lcd2);
		   	 idle_screen();
			Flag_Ent = ID_NOT_RECEVIED;
			MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin0, 1);


		}
	}

	}



void  processing_exit(void)
{

	int i;
	passed = 0;
	while(   (! flag_exit) & ( ! (USART2->USART_SR & (1<<5))));
	if(flag_exit == ID_RECEIVED)
	{
	  	  counter1 = 0;
		Exit_gate_ID_test = atoi(Exit_gate_ID);
		for(i=0; i<3; i++)
		{
			if(Exit_gate_ID_test == IDs_int[i])
			{
				passed = 1;
				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin11, 0);
				_delay_ms(250);
				_delay_ms(250);
				lcd_display_sentence("ID ---> accepted", lcd2);
				_delay_ms(250);
				_delay_ms(250);
			   	 lcd_send_command(lcd_clear, lcd2);
			   	 lcd_send_command(lcd_begin_at_seconed_row, lcd2);
				lcd_display_sentence("opening the gate", lcd2);
				_delay_ms(250);
				_delay_ms(250);
				flag_exit = ID_NOT_RECEVIED;
				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin11, 1);
				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin8, 1);
				slots ++;
				MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin8, 0);
				while(! MCAL_GPIO_Read_Pin(GPIOA, GPIO_pin7));
				idle_screen();
				break;
			}
		}
		if(! passed)
		{
			MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin0, 0);
			_delay_ms(250);
			_delay_ms(250);
			_delay_ms(250);
			lcd_display_sentence("ID ---> rejected", lcd2);
			_delay_ms(250);
		   	 lcd_send_command(lcd_clear, lcd2);
		   	 idle_screen();
			flag_exit = ID_NOT_RECEVIED;
			MCAL_GPIO_Write_Pin(GPIOA, GPIO_pin0, 1);


		}
	}

	}

//ISRS
void UART1_ISR(void)
{
	_delay_ms(50);
      Entery_gate_ID[counter] =  MCAL_UART_receive_Data(USART1, polling_disable);
      counter++;
      _delay_ms(50);
      if(Entery_gate_ID[counter-1] == '\r')
      {
    	  Flag_Ent = ID_RECEIVED;
    	  lcd_send_command(lcd_clear, lcd2);
      }
      processing();
	}
void UART2_ISR(void)
{
	_delay_ms(50);
      Exit_gate_ID[counter1] =  MCAL_UART_receive_Data(USART2, polling_disable);
      counter1++;
      _delay_ms(50);
      if(Exit_gate_ID[counter1-1] == '\r')
      {
    	  flag_exit = ID_RECEIVED;
    	  lcd_send_command(lcd_clear, lcd2);
      }
      processing_exit();
	}



int main(void)

{
	int i,j;
     slots = 3 ;
	//intilization
	 Mcal_init();
	 Hal_init();
	_delay_ms(10);

	//adjust UART configurations

	UART_CONFIG_t Entery_gate_interface;
    Entery_gate_interface.Uart_Mode = UART_RX_ENABLE;
    Entery_gate_interface.Data_Length = UART_8_BITS_DATA_LENGTH;
    Entery_gate_interface.Flow_Control = UART_FLOW_CONTROL_NONE;
    Entery_gate_interface.Parity_Bits = UART_PARITY_NONE;
    Entery_gate_interface.Stop_Bits = UART_1_STOP_BIT;
    Entery_gate_interface.Baud_Rate = UART_BAUD_RATE_115200_BPS;
    Entery_gate_interface.Irq_status = UART_INTERRUPT_RXNE_ENABLE;
    Entery_gate_interface.Uart_Isr = UART1_ISR;

	UART_CONFIG_t Exit_gate_interface;
    Exit_gate_interface.Uart_Mode = UART_RX_ENABLE;
    Exit_gate_interface.Data_Length = UART_8_BITS_DATA_LENGTH;
    Exit_gate_interface.Flow_Control = UART_FLOW_CONTROL_NONE;
    Exit_gate_interface.Parity_Bits = UART_PARITY_NONE;
    Exit_gate_interface.Stop_Bits = UART_1_STOP_BIT;
    Exit_gate_interface.Baud_Rate = UART_BAUD_RATE_115200_BPS;
    Exit_gate_interface.Irq_status = UART_INTERRUPT_RXNE_ENABLE;
    Exit_gate_interface.Uart_Isr = UART2_ISR;

    MCAL_UART_Init(USART1, & Entery_gate_interface);
    MCAL_UART_Init(USART2, & Exit_gate_interface);


    set_pins();

	//welcome message & starting for admin  dashboard
	lcd_display_sentence("welcome to admin dash board",lcd1);
	_delay_ms(100);
	lcd_send_command(lcd_clear,lcd1);
	lcd_display_sentence("Enter authorized IDs",lcd1);
	_delay_ms(100);
	lcd_send_command(lcd_clear,lcd1);


	//saving authorized Ids via system admin
	for(i=0; i<3; i++)
	{
		if(i==0)
		lcd_display_sentence("ID1 : ",lcd1);
		if(i==1)
		{
		lcd_send_command(lcd_begin_at_seconed_row,lcd1);
		lcd_display_sentence("ID2 : ",lcd1);
		}
		if(i==2)
		{
		lcd_send_command(lcd_begin_at_third_row,lcd1);
		lcd_display_sentence("ID3 : ",lcd1);
		}
	for(j=0; j<4; j++)
	{
		unsigned char button = keypad_send_char();
		_delay_ms(250);
		lcd_display_char(button,lcd1);
		IDs [i][j] = button ;
		_delay_ms(250);
	}
	}


     //converting IDs to int to facilitate the comparison
	for(i=0; i<3; i++)
	{
	IDs_int[i] = atoi(&IDs[i]);
	}


	// welcome message & starting for Driver LCD
     lcd_display_sentence("welcome to nabil smart parking ", lcd2);
	 _delay_ms(250);
   	 lcd_send_command(lcd_clear, lcd2);



    while(1)
    {


   	 waiting();

    }

}




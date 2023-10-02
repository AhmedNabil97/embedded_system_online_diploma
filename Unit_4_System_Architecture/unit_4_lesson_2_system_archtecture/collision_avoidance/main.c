#include "CA.h"
#include "Ultra_Sonic.h"
#include "Dc_Motor.h"

void setup()
{
	US_init();
	motor_init();
	}


int main()
{
	setup();
	while(1)
	{
		US_state_pointer();
		states_pointer();
		motor_state_pointer();
	}
}

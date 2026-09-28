//
// Created by Anh Huynh on 6.9.2026.
//


#include "../incl/LED.h"

#include <string>

#include "incl/vPrintString.h"

void LED::toggle_leds()
{
	last_state = !last_state;
	led1.write(last_state);
	led2.write(last_state);
	led3.write(last_state);
}

void LED::leds_off() const
{
	led1.write(false);
	led2.write(false);
	led3.write(false);
}

void LED::leds_on() const
{
	led1.write(true);
	led2.write(true);
	led3.write(true);
}


void LED::increase_freq()
{
	if (is_on)
	{
		int increment = 20;
		if (frequency + increment <= MAX_FREQ)
		{
			frequency += increment;
		}
		else
		{
			frequency = MAX_FREQ;
		}
		period = 1 * 1000 / frequency;  //convert to ms
		const std::string msg = "Increased frequency! Current frequency: " + std::to_string(frequency) + "\n";
		vPrintString(msg.c_str());
	}
}

void LED::decrease_freq()
{
	if (is_on)
	{
		int decrement = 20;
		if (frequency - decrement >= MIN_FREQ)
		{
			frequency -= decrement;
		}
		else
		{
			frequency = MIN_FREQ;
		}
		period = 1 * 1000 / frequency;  //convert to ms
		const std::string msg = "Decreased frequency! Current frequency: " + std::to_string(frequency) + "\n";
		vPrintString(msg.c_str());
	}
}

bool LED::is_enabled() const
{
	return is_on;
}

void LED::turn_on_off()
{
	is_on = !is_on;
	if (is_on)
	{
		vPrintString("Turned on!\n");
	}
	else
	{
		vPrintString("Turned off\n");
	}
}

int LED::get_period() const
{
	return period;
}






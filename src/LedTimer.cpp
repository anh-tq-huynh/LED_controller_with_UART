//
// Created by Anh Huynh on 13.9.2026.
//

#include "../incl/LedTimer.h"

void LedTimer::toggle_led_callback()
{
	TickType_t now = xTaskGetTickCount();

	//Toggle LEDs
	leds_.toggle_leds();

	//Update last toggle time
	last_toggle_time = now;
}

TickType_t LedTimer::get_last_toggle_time() const
{
	return last_toggle_time;
}

void LedTimer::change_toggle_interval(int new_period_ms)
{
	xTimerChangePeriod(led_timer,pdMS_TO_TICKS(new_period_ms),0);
}


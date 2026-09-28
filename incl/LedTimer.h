//
// Created by Anh Huynh on 13.9.2026.
//

#ifndef LAB4_LEDTIMER_H
#define LAB4_LEDTIMER_H
#include "FreeRTOS.h"
#include "timers.h"
#include <LED.h>


class LedTimer
{
	public:
		explicit LedTimer (LED &led) : leds_(led)
		{
			led_timer = xTimerCreate(
				"Toggle LED",
				pdMS_TO_TICKS(5000),
				pdTRUE,
				this,
				led_timer_callback);
			xTimerStart(led_timer, 0);
		};

		void toggle_led_callback();

		[[nodiscard]] TickType_t get_last_toggle_time() const;
		void change_toggle_interval(int new_period_ms);

	private:
		LED &leds_;
		TimerHandle_t led_timer;
		TickType_t last_toggle_time = 0;

		static void led_timer_callback(TimerHandle_t xTimer)
		{
			LedTimer* instance = static_cast<LedTimer*>(pvTimerGetTimerID(xTimer));
			instance -> toggle_led_callback();
		}
};


#endif //LAB4_LEDTIMER_H
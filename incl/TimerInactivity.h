//
// Created by Anh Huynh on 13.9.2026.
//

#ifndef LAB4_TIMERINACTIVITY_H
#define LAB4_TIMERINACTIVITY_H
#include <cstdint>
#include <sys/stat.h>

#include "FreeRTOS.h"
#include "timers.h"


class TimerInactivity
{
	public:
		TimerInactivity(uint8_t *buffer, const size_t buffer_size): buffer(buffer), buffer_size(buffer_size)
		{
			inactive_timer = xTimerCreate(
				"Inactivity Timer",
				pdMS_TO_TICKS(30000),
				pdFALSE,
				this,
				inactive_timer_callback);
			xTimerStart(inactive_timer,0);
		};
		void inactive_timeout_callback();

		void reset() const;

	private:
		uint8_t *buffer;
		size_t buffer_size;
		TimerHandle_t inactive_timer;

		static void inactive_timer_callback(TimerHandle_t xTimer)
		{
			TimerInactivity* instance = static_cast<TimerInactivity *> (pvTimerGetTimerID(xTimer));
			instance -> inactive_timeout_callback();
		}
};


#endif //LAB4_TIMERINACTIVITY_H
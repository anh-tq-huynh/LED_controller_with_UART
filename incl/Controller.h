//
// Created by Anh Huynh on 13.9.2026.
//

#ifndef LAB4_CONTROLLER_H
#define LAB4_CONTROLLER_H
#include "FreeRTOS.h"
#include "InputProcessor.h"
#include "LED.h"
#include "LedTimer.h"
#include "TimerInactivity.h"
#include "timers.h"


class Controller
{
	public:
		explicit Controller(LED &leds)
			:
		buffer(),
		leds_controller(leds),
		led_timer(leds_controller),
		inactive_timer(buffer, buffer_size),
		input_processor(buffer, buffer_size)
		{
			xTaskCreate(task_controller,"System Controller", 2048, (void*) this, tskIDLE_PRIORITY + 1, &handle);
		};
		void system_controller();
		void execute();

	private:
		size_t buffer_size = 64;
		uint8_t buffer[64];

		LED &leds_controller;
		LedTimer led_timer ;
		TimerInactivity inactive_timer;
		InputProcessor input_processor;

		bool activity_detected = false;
		int inactive_count = 0;
		int new_toggle_period = 5000;
		cmd_received new_exe = cmd_received::IDLE;
		cmd_received last_exe = cmd_received::IDLE;

		static void task_controller(void* param)
		{
			auto instance = static_cast<Controller*> (param);
			instance -> system_controller();
		}
		TaskHandle_t handle;

};


#endif //LAB4_CONTROLLER_H
//
// Created by Anh Huynh on 13.9.2026.
//

#include "../incl/Controller.h"
#include "FreeRTOS.h"
#include "timers.h"
#include "vPrintString.h"

void Controller::system_controller()
{
	while (true)
	{
		//Check input activity
		activity_detected = input_processor.get_input();
		if (activity_detected)
		{
			inactive_timer.reset();
			inactive_count = 0;
		}

		//Execute input command
		new_exe = input_processor.get_next_exe();
		if (new_exe != last_exe )
		{
			execute();
			last_exe = new_exe;
			new_exe = cmd_received::IDLE;
		}
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void Controller::execute()
{
	if (new_exe == cmd_received::HELP)
	{
		vPrintString("Type \"help\" for usage instructions\n");
		vPrintString("Type \"interval <number>\" to set new led toggle interval\n");
		vPrintString("Type \"time\" to print the time since last led toggle\n");
	}
	else if (new_exe == cmd_received::TIME)
	{
		TickType_t last_toggle_tick = led_timer.get_last_toggle_time();
		TickType_t now = xTaskGetTickCount();
		TickType_t elapse_time = now - last_toggle_tick;

		//Convert to seconds
		float elapse_second = static_cast<float>(elapse_time) / configTICK_RATE_HZ;

		char msg[64];
		snprintf(msg, sizeof(msg), "Time since last toggle: %.1f s\n", elapse_second);
		vPrintString(msg);
	}
	else if (new_exe == cmd_received::CHANGE_INTERVAL)
	{
		new_toggle_period = input_processor.get_new_period();
		led_timer.change_toggle_interval(new_toggle_period);
		std::string msg = "Update new interval into " + std::to_string(new_toggle_period) + "\n";
		vPrintString(msg.c_str());
	}
	else if (new_exe == cmd_received::ERROR)
	{
		vPrintString("Unknown command \n");
	}
}

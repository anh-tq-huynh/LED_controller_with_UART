//
// Created by Anh Huynh on 13.9.2026.
//

#ifndef LAB4_INPUTPROCESSOR_H
#define LAB4_INPUTPROCESSOR_H
#include "../Uart/PicoOsUart.h"

enum class cmd_received {HELP, CHANGE_INTERVAL, TIME, ERROR, IDLE};

class InputProcessor
{
	public:
		InputProcessor(uint8_t *buffer, const size_t buffer_size)
		: u (0,0,1,115200),
		activity_detected(),
		cmd_buffer(buffer),
		buffer_size(buffer_size),
		new_led_period()
		{};
		[[nodiscard]] int get_new_period() const;

		[[nodiscard]] cmd_received get_next_exe() const;

		bool         get_input();

	private:
		PicoOsUart u;
		bool activity_detected;
		uint8_t *cmd_buffer;
		size_t buffer_size;
		int interval = 5000;
		size_t write_index = 0;


		cmd_received check_cmd();
		int new_led_period;
		cmd_received next_exe = cmd_received::IDLE;
};


#endif //LAB4_INPUTPROCESSOR_H
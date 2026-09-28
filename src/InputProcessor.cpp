//
// Created by Anh Huynh on 13.9.2026.
//
#include "InputProcessor.h"
#include <cstring>

#include "vPrintString.h"

bool InputProcessor::get_input()
{
	uint8_t byte;
	size_t byte_read = u.read(&byte, 1);
	activity_detected = false;

	if (byte_read > 0)
	{
		activity_detected = true;
		//Iterate input, read the full 64 bytes at a time
		if ( byte == '\n' || byte == '\r') //Only check input when enter is hit
		{
			if (write_index > 0)
			{
				cmd_buffer[write_index] = '\0';
				//Check cmd
				next_exe = check_cmd();
				write_index = 0;
			}
		}
		//Backspace, only change the serial output, no action needed
		else if ((byte == '\b' || byte == 0x7F) && write_index > 0)
		{
			write_index--;
			const uint8_t erase_seq[] = {'\b', ' ', '\b'};
			u.write(erase_seq, 3);
			next_exe = cmd_received::IDLE;
		}
		//In the middle of typing
		else if (write_index < buffer_size - 1)
		{
			//u.write(&byte, 1);
			cmd_buffer[write_index] = byte;
			write_index++;
			next_exe = cmd_received::IDLE;
		}
	}
	return activity_detected;
}

cmd_received InputProcessor::check_cmd()
{
	const auto cmd(reinterpret_cast<const char*> (cmd_buffer));
	char upper_cmd[64];
	size_t i = 0;

	for (; cmd[i] != '\0' && i < sizeof(upper_cmd) - 1; ++i) {
		upper_cmd[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(cmd[i])));
	}
	upper_cmd[i] = '\0';
	if (strcmp(upper_cmd, "HELP") == 0)
	{
		return cmd_received::HELP;
	}
	if (strcmp(upper_cmd,"TIME") == 0)
	{
		return cmd_received::TIME;
	}
	//Check if the cmd starts with "INTERVAL " (space included)
	char check_interval_cmd[] = {'I', 'N', 'T', 'E', 'R', 'V', 'A','L', ' '};
	bool is_interval_cmd = true;
	for (size_t i = 0; i < 9; i++)
	{
		if (upper_cmd[i] != check_interval_cmd[i])
		{
			is_interval_cmd = false;
		}
	}

	//Try convert the number that comes after the space, if success then save
	if (is_interval_cmd)
	{
		char *pEnd;
		int number_input = strtol(&upper_cmd[9], &pEnd, 10);
		if (number_input != 0)
		{
			new_led_period = number_input;
		}
		return cmd_received::CHANGE_INTERVAL;
	}
	return cmd_received::ERROR;
}

int InputProcessor::get_new_period() const
{
	return new_led_period;
}

cmd_received InputProcessor::get_next_exe() const
{
	return next_exe;
}


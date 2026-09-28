//
// Created by Anh Huynh on 6.9.2026.
//

#ifndef LAB3_1_GPIOPIN_H
#define LAB3_1_GPIOPIN_H

#include <cstdint>


class GPIOPin
{
	public:
		explicit GPIOPin(int pin, bool input = true, bool pullup = true, bool invert = false);
		GPIOPin(const GPIOPin &) = delete;
		~GPIOPin();
		bool read() const;
		void write(bool value) const;
		explicit operator bool() const;
		int get_pin() const
		{
			return pin;
		}
	private:
		bool is_dormant;
		bool is_input;
		int pin;
		static uint32_t pins_in_use;
};



#endif //LAB3_1_GPIOPIN_H
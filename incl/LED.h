//
// Created by Anh Huynh on 6.9.2026.
//

#ifndef LAB3_1_LED_H
#define LAB3_1_LED_H

#include "GPIOPin.h"

#define MAX_FREQ 200
#define MIN_FREQ 2


class LED
{
	public:
		explicit LED(int led_pin1, int led_pin2, int led_pin3)
		: led1(led_pin1,false, false, false),
		led2(led_pin2,false, false, false),
		led3(led_pin3,false, false, false){};
		void toggle_leds();
		void leds_off() const;
		void leds_on() const;

		void increase_freq();
		void decrease_freq();
		bool is_enabled() const;
		void turn_on_off();
		int get_period() const;

	private:
		GPIOPin led1;
		GPIOPin led2;
		GPIOPin led3;
		bool is_on = false;
		bool last_state = false;
		int frequency = 2;
		int period = 5000;  //convert to ms


};



#endif //LAB3_1_LED_H
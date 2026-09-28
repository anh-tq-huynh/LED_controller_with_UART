#include <iostream>

#include "Controller.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "incl/LED.h"
#include "incl/vPrintString.h"
#include "pico/stdio.h"

#define D1 22
#define D2 21
#define D3 20

#define ROT_SW 12
#define ROT_A 10
#define ROT_B 11

// stack overflow check
extern "C" {
	void vApplicationStackOverflowHook( TaskHandle_t xTask, char * pcTaskName ) {
		if (pcTaskName != NULL) panic("Stack overflow: %s",pcTaskName);
		else panic("Stack overflow of unnamed task");
	}
}

#include "hardware/timer.h"
extern "C" {
	uint32_t read_runtime_ctr(void) {
		return timer_hw->timerawl;
	}
}


int main ()
{
	stdio_init_all();
	vPrintString("Program starts!\n");

	LED leds(D1, D2, D3);
	leds.leds_on();

	Controller controller(leds);

	vTaskStartScheduler();
	while (true)
	{
	};
}

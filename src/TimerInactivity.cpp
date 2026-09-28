//
// Created by Anh Huynh on 13.9.2026.
//

#include "../incl/TimerInactivity.h"

#include <cstring>

#include "vPrintString.h"

void TimerInactivity::inactive_timeout_callback()
{
	vPrintString("[Inactive] - Discard the input\n");
	memset(buffer, 0, buffer_size); //Clear the buffer
}

void TimerInactivity::reset() const
{
	xTimerReset(inactive_timer, 0);
}

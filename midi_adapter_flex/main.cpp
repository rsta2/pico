//
// main.cpp
//
// USB to 2xUART MIDI adapter
// Copyright (C) 2022  Rene Stange
//
// Based on the TinyUSB midi_test example, which is:
//	Copyright (c) 2019 Ha Thach (tinyusb.org)
//
// SPDX-License-Identifier: MIT
//
#include "bsp/board.h"
#include "midi_port_usb.h"
#include "midi_port_uart.h"

//--------------------------------------------------------------------+
// STATICS PROTYPES
//--------------------------------------------------------------------+

static CMIDIPortUSB USB;
static CMIDIPortUART UART0 (uart0, 0);
static CMIDIPortUART UART1 (uart1, 4);

void midi_task (void);
void led_task (void);

/*------------- MAIN -------------*/
int main(void)
{
	board_init ();

	USB.Init ();
	UART0.Init ();
	UART1.Init ();

	while (1)
	{
		led_task ();
		midi_task ();
	}

	return 0;
}

//--------------------------------------------------------------------+
// MIDI Task
//--------------------------------------------------------------------+

void midi_task(void)
{
	USB.Update ();
	UART0.Update ();
	UART1.Update ();

	CMIDIMessage Msg;

	if (USB.Read (&Msg))
	{
		UART0.Write (Msg);
		UART1.Write (Msg);
	}

	if (UART0.Read (&Msg))
	{
		USB.Write (Msg);
		UART1.Write (Msg);
	}

	if (UART1.Read (&Msg))
	{
		USB.Write (Msg);
		UART0.Write (Msg);
	}
}

//--------------------------------------------------------------------+
// LED Task
//--------------------------------------------------------------------+

void led_task(void)
{
	static uint32_t last_active_ms = 0;

	if (USB.IsActive () || UART0.IsActive () || UART1.IsActive ())
	{
		board_led_write(true);

		last_active_ms = board_millis();
	}
	else if (board_millis() - last_active_ms > 10)
	{
		board_led_write(false);
	}
}

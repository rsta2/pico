//
// spi_slave_pio.c
//
// SPI slave for the RP2040
// Copyright (C) 2021  Rene Stange
//
// SPDX-License-Identifier: BSD-3-Clause
//
#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/bootrom.h"
#include "pico/binary_info.h"
#include "hardware/pio.h"
#include "spi_slave.pio.h"

#define PIN_RX		16		// MOSI
#define PIN_CS		(PIN_RX+1)	// do not change!
#define PIN_SCK		(PIN_RX+2)	// do not change!
#define PIN_TX		19 		// MISO

#define BLOCK_SIZE	128

int main (void)
{
	stdio_init_all ();

	printf ("SPI slave sample\n");

	PIO pio = pio0;
	/*uint sm_cs =*/ spi_slave_cs_program_init (pio, PIN_CS, PIN_TX);
	uint sm = spi_slave_txrx_program_init (pio, PIN_RX, PIN_TX);

	bi_decl (bi_1pin_with_name (PIN_RX,  "SPI RX"));
	bi_decl (bi_1pin_with_name (PIN_CS,  "SPI CS"));
	bi_decl (bi_1pin_with_name (PIN_SCK, "SPI SCK"));
	bi_decl (bi_1pin_with_name (PIN_TX,  "SPI TX"));

	// run for 60 seconds and reboot
	absolute_time_t start_time = get_absolute_time ();
	while (absolute_time_diff_us (start_time, get_absolute_time ()) < 60000000)
	{
		uint8_t tx_buf[BLOCK_SIZE];
		for (unsigned i = 0; i < BLOCK_SIZE; i++)
		{
			tx_buf[i] = (uint8_t) i;
		}

		uint8_t rx_buf[BLOCK_SIZE];
		spi_slave_write_read_blocking (pio, sm, tx_buf, rx_buf, BLOCK_SIZE);

		for (unsigned i = 0; i < BLOCK_SIZE; i++)
		{
			printf ("%02X%c", (unsigned) rx_buf[i], i % 16 == 15 ? '\n' : ' ');
		}

		putchar ('\n');
	}

	printf ("Rebooting to BOOTSEL mode ...\n");
	reset_usb_boot (0, 1);

	return 0;
}

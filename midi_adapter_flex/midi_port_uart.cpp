//
// midi_port_uart.cpp
//
// Copyright (C) 2022-2023  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#include "midi_port_uart.h"
#include "hardware/gpio.h"

CMIDIPortUART::CMIDIPortUART (uart_inst_t *pUART, uint nGPIOTx)
:	m_pUART (pUART),
	m_nGPIOTx (nGPIOTx),
	m_nRxState (0),
	m_nTxState (0)
{
}

void CMIDIPortUART::Init (void)
{
	uart_init (m_pUART, 31250);

	gpio_set_function (m_nGPIOTx, GPIO_FUNC_UART);
	gpio_set_function (m_nGPIOTx+1, GPIO_FUNC_UART);
}

void CMIDIPortUART::Update (void)
{
	m_bActive = false;
	while (uart_is_readable (m_pUART))
	{
		uint8_t uchByte = uart_getc (m_pUART);
		m_bActive = true;

		switch (m_nRxState)
		{
		case 0:
			if (   !(uchByte & 0x80)
			    || uchByte == 0xF7)
			{
				break;
			}
			else if (uchByte == 0xF0)
			{
				m_nRxState = 9;
				break;
			}
			else
			{
				m_RxBuffer[0] = Status2Length (uchByte);
			}
			// fall through

		default:
			m_RxBuffer[++m_nRxState] = uchByte;
			if (m_nRxState == m_RxBuffer[0])
			{
				queue_try_add (&m_RxQueue, m_RxBuffer);
				m_nRxState = 0;
			}
			break;

		case 9:
			if (uchByte == 0xF7)
			{
				m_nRxState = 0;
			}
			break;

		}
	}

	while (uart_is_writable (m_pUART))
	{
		if (   m_nTxState == 0
		    && !queue_try_remove (&m_TxQueue, m_TxBuffer))
		{
			break;
		}

		uart_putc_raw (m_pUART, m_TxBuffer[++m_nTxState]);

		if (m_nTxState == (m_TxBuffer[0] & 0xF))
		{
			m_nTxState = 0;
		}
	}
}

uint8_t CMIDIPortUART::Status2Length (uint8_t uchStatus)
{
	if (uchStatus < 0xF0)
	{
		static const uint8_t Length[] = {3, 3, 3, 3, 2, 2, 3};

		return Length[(uchStatus >> 4) - 8];
	}
	else
	{
		static const uint8_t Length[] = {1, 2, 3, 2, 0, 0, 1, 1,
						 1, 1, 1, 1, 1, 1, 1, 1};

		return Length[uchStatus & 0xF];
	}
}

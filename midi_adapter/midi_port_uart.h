//
// midi_port_uart.h
//
// Copyright (C) 2022  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#ifndef _midi_port_uart_h
#define _midi_port_uart_h

#include "midi_port.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"

class CMIDIPortUART : public CMIDIPort
{
public:
	CMIDIPortUART (uart_inst_t *pUART, uint nGPIOTx);

	void Init (void);

	void Update (void);

private:
	static uint8_t Status2Length (uint8_t uchStatus);

private:
	uart_inst_t *m_pUART;
	uint m_nGPIOTx;

	unsigned m_nRxState;
	unsigned m_nTxState;

	uint8_t m_RxBuffer[CMIDIMessage::MaxLength];	// first byte is length
	uint8_t m_TxBuffer[CMIDIMessage::MaxLength];
};

#endif

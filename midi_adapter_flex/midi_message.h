//
// midi_message.h
//
// Copyright (C) 2022-2023  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#ifndef _midi_message_h
#define _midi_message_h

#include "pico/stdlib.h"

class CMIDIMessage
{
public:
	static const int MaxLength = 4;

public:
	CMIDIMessage (void);
	CMIDIMessage (uint8_t uchLength, uint8_t uchStatus,
		      uint8_t uchParam1 = 0, uint8_t uchParam2 = 0,
		      uint8_t uchCable = 0);

	// getter
	uint8_t Length (void) const;		// 1 .. 3
	uint8_t Status (void) const;		// first byte
	uint8_t Type (void) const;		// Status & 0xF0
	uint8_t Channel (void) const;		// Status & 0x0F
	uint8_t Param1 (void) const;		// first parameter byte
	uint8_t Param2 (void) const;		// second parameter byte
	uint8_t Cable (void) const;		// 0 .. 15

	// setter
	void Channel (uint8_t uchChannel);	// 0 .. 15
	void Param1 (uint8_t uchParam1);	// first parameter byte
	void Param2 (uint8_t uchParam2);	// second parameter byte
	void Cable (uint8_t uchCable);		// 0 .. 15

public:
	const uint8_t *GetBuffer (void) const;
	uint8_t *GetBuffer (void);

private:
	uint8_t m_Buffer[MaxLength];	// first byte is virtual cable and length
};

#endif

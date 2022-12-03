//
// midi_message.cpp
//
// Copyright (C) 2022  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#include "midi_message.h"

CMIDIMessage::CMIDIMessage (void)
{
}

CMIDIMessage::CMIDIMessage (uint8_t uchLength, uint8_t uchStatus,
			    uint8_t uchParam1, uint8_t uchParam2)
{
	m_Buffer[0] = uchLength;
	m_Buffer[1] = uchStatus;
	m_Buffer[2] = uchParam1;
	m_Buffer[3] = uchParam2;
}

uint8_t CMIDIMessage::Length (void) const
{
	return m_Buffer[0];
}

uint8_t CMIDIMessage::Status (void) const
{
	return m_Buffer[1];
}

uint8_t CMIDIMessage::Type (void) const
{
	return m_Buffer[1] & 0xF0;
}

uint8_t CMIDIMessage::Channel (void) const
{
	return m_Buffer[1] & 0x0F;
}

uint8_t CMIDIMessage::Param1 (void) const
{
	return m_Buffer[2];
}

uint8_t CMIDIMessage::Param2 (void) const
{
	return m_Buffer[3];
}

void CMIDIMessage::Channel (uint8_t uchChannel)
{
	m_Buffer[1] &= 0xF0;
	m_Buffer[1] |= uchChannel & 0x0F;
}

void CMIDIMessage::Param1 (uint8_t uchParam1)
{
	m_Buffer[2] = uchParam1;
}

void CMIDIMessage::Param2 (uint8_t uchParam2)
{
	m_Buffer[3] = uchParam2;
}

const uint8_t *CMIDIMessage::GetBuffer (void) const
{
	return m_Buffer;
}

uint8_t *CMIDIMessage::GetBuffer (void)
{
	return m_Buffer;
}

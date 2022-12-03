//
// midi_port.cpp
//
// Copyright (C) 2022  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#include "midi_port.h"

CMIDIPort::CMIDIPort (uint nQueueSize)
:	m_bActive (false)
{
	queue_init (&m_RxQueue, CMIDIMessage::MaxLength, nQueueSize);
	queue_init (&m_TxQueue, CMIDIMessage::MaxLength, nQueueSize);
}

CMIDIPort::~CMIDIPort (void)
{
	queue_free (&m_RxQueue);
	queue_free (&m_TxQueue);
}

void CMIDIPort::Write (const CMIDIMessage &rMessage)
{
	queue_try_add (&m_TxQueue, rMessage.GetBuffer ());
}

bool CMIDIPort::Read (CMIDIMessage *pMessage)
{
	return queue_try_remove (&m_RxQueue, pMessage->GetBuffer ());
}

bool CMIDIPort::IsActive (void) const
{
	return m_bActive;
}

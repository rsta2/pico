//
// midi_port.h
//
// Copyright (C) 2022  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#ifndef _midi_port_h
#define _midi_port_h

#include "midi_message.h"
#include "pico/util/queue.h"

class CMIDIPort
{
public:
	CMIDIPort (uint nQueueSize = 100);
	~CMIDIPort (void);

	void Write (const CMIDIMessage &rMsg);
	bool Read (CMIDIMessage *pMsg);

	bool IsActive (void) const;

protected:
	queue_t m_RxQueue;
	queue_t m_TxQueue;

	bool m_bActive;
};

#endif

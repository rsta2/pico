//
// midi_port_usb.h
//
// Copyright (C) 2022  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#ifndef _midi_port_usb_h
#define _midi_port_usb_h

#include "midi_port.h"

class CMIDIPortUSB : public CMIDIPort
{
public:
	CMIDIPortUSB (void);

	void Init (void);

	void Update (void);

public:
	static void Unmount (void);

private:
	static CMIDIPortUSB *s_pThis;
};

#endif

//
// midi_port_usb.cpp
//
// Copyright (C) 2022-2023  Rene Stange
//
// SPDX-License-Identifier: MIT
//
#include "midi_port_usb.h"
#include "tusb.h"
#include "pico/stdlib.h"

CMIDIPortUSB *CMIDIPortUSB::s_pThis;

CMIDIPortUSB::CMIDIPortUSB (void)
{
	s_pThis = this;
}

void CMIDIPortUSB::Init (void)
{
	tusb_init ();
}

void CMIDIPortUSB::Update (void)
{
	tud_task ();

	if (!tud_midi_mounted ())
	{
		return;
	}

	if (   !queue_is_full (&m_RxQueue)
	    && tud_midi_available ())
	{
		uint8_t Packet[4];
		tud_midi_packet_read (Packet);

		static const uint8_t CIN2Length[] = {0, 0, 2, 3, 0, 1, 0, 0,
						     3, 3, 3, 3, 2, 2, 3, 1};
		uint8_t uchCIN = Packet[0] & 0xF;
		uint8_t uchLength = CIN2Length[uchCIN];
		if (   uchLength
		    && Packet[1] != 0xF7)
		{
			Packet[0] &= 0xF0;
			Packet[0] |= uchLength;
			queue_try_add (&m_RxQueue, Packet);
		}

		m_bActive = true;
	}
	else
	{
		m_bActive = false;
	}

	uint8_t Buffer[CMIDIMessage::MaxLength];
	if (queue_try_remove (&m_TxQueue, Buffer))
	{
		tud_midi_stream_write (Buffer[0] >> 4, Buffer+1, Buffer[0] & 0xF);
	}
}

void CMIDIPortUSB::Unmount (void)
{
	s_pThis->m_bActive = false;
}

void tud_mount_cb (void)
{
}

void tud_umount_cb (void)
{
	CMIDIPortUSB::Unmount ();
}

void tud_suspend_cb (bool /* bRemoteWakeup */)
{
}

void tud_resume_cb (void)
{
}

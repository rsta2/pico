README

This program is a USB to serial MIDI adapter. It connects to an USB host via the
USB connector of the Raspberry Pi Pico on one side and to a MIDI device with
serial interface via GP0 (UART TX)/GP1 (RX) on the other side. MIDI
messages/events, received on one side, will be converted and send out on the
other side. The LED on the Raspberry Pi Pico board flashes, when MIDI data is
exchanged.

For example, this program can be used to connect MiniSynth Pi to a PC USB host
running a sequencer application, which is normally not possible, because
MiniSynth Pi provides only an USB host MIDI interface too, and two USB hosts
cannot be bound together. The Raspberry Pi computer, running MiniSynth Pi, and
the Raspberry Pi Pico, running the MIDI adapter program, have to be connected as
follows (chip numbers, not header positions):

Raspberry Pi		Raspberry Pi Pico	PC
MiniSynth Pi		MIDI adapter		Sequencer

			USB		<-->	USB

UART-TX	GPIO14	--->	GP1 UART-RX
UART-RX	GPIO15	<---	GP0 UART-TX
GND		<-->	GND

The Raspberry Pi Pico is powered via USB, the VSYS or VBUS pins must NOT be
connected!

The MIDI adapter receives USB MIDI events from all virtual MIDI cables, and it
sends USB MIDI data to the virtual MIDI cable zero.

If you enable the #define IGNORE_MIDI_CC in the file main.c, the MIDI control
change and program change events, which have be received from the USB host, will
be filtered out and ignored.

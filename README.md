Pico
====

> Raspberry Pi is a trademark of Raspberry Pi Ltd.

Overview
--------

Some small programs for the Raspberry Pi Pico.

Pico W and Pico 2 have not been tested with these programs. The LED is not
working on the Pico W with them.

Programs
--------

| Directory          | Description                                              |
|--------------------|----------------------------------------------------------|
| dummy_flash/       | to be installed in the flash for the RAM loader          |
| midi_adapter/      | USB to serial MIDI adapter (converter)                   |
| midi_adapter_flex/ | Configurable USB to serial MIDI adapter                  |
| spi_slave_pio/     | SPI slave, which is compatible with the Raspberry Pi 0-4 |

Building
--------

```
export PICO_SDK_PATH=/absolute/path/to/pico-sdk
export PICOTOOL_FETCH_FROM_GIT_PATH=/absolute/path/to/a/temp/directory
export PICO_BOARD=pico		# or pico_w, pico2
mkdir build
cd build
cmake ..
make
```

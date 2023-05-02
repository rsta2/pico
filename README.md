Pico
====

> Raspberry Pi is a trademark of Raspberry Pi Ltd.

Overview
--------

Some small programs for the Raspberry Pi Pico.

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
mkdir build
cd build
cmake ..
make
```
